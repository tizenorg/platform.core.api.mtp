/*
 * Copyright (c) 2012, 2013 Samsung Electronics Co., Ltd.
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#include <stdio.h>
#include <unistd.h>
#include <glib.h>
#include <gio/gio.h>
#include <stdlib.h>

#include "mtp_gdbus_manager.h"
#include "mtp_gdbus_objectinfo.h"
#include "mtp_gdbus_deviceinfo.h"
#include "mtp_gdbus_storageinfo.h"

typedef struct _event_cb_s {
	mtp_event_cb cb;
	void *user_data;
} event_cb_s;

mtpgdbuslibManager *manager_proxy = NULL;
static __thread GSList *event_cb_list = NULL;

static void __mtp_event_cb(mtpgdbuslibManager *object,
	gint event, gint arg1, gpointer user_data)
{
	GSList *l;
	event_cb_s *event_s;

	for (l = event_cb_list; l != NULL; l = l->next) {
		event_s = (event_cb_s *)l->data;
		event_s->cb(event, arg1, event_s->user_data);
	}
}

static void __manager_proxy_init(void)
{
	GError *error = NULL;

	manager_proxy = mtp_gdbuslib_manager_proxy_new_for_bus_sync(
		G_BUS_TYPE_SYSTEM,
		G_DBUS_PROXY_FLAGS_NONE,
		MTP_DBUS_SERVICE,
		MTP_DBUS_MANAGER_PATH,
		NULL,
		&error);

	g_signal_connect(manager_proxy, "mtp-event", G_CALLBACK(__mtp_event_cb), NULL);
}

static void __manager_proxy_deinit(void)
{
	manager_proxy = NULL;
}

mtp_error_e mtp_gdbus_manager_add_event_cb(mtp_event_cb callback, void *user_data)
{
	event_cb_s *event_s;

	event_s = g_try_new0(event_cb_s, 1);
	if (event_s == NULL)
		return MTP_ERROR_OUT_OF_MEMORY;

	event_s->cb = callback;
	event_s->user_data = user_data;

	event_cb_list = g_slist_prepend(event_cb_list, event_s);

	return MTP_ERROR_NONE;
}

mtp_error_e mtp_gdbus_manager_remove_event_cb(mtp_event_cb callback)
{
	GSList *l;
	event_cb_s *event_s;

	for (l = event_cb_list; l != NULL; l = l->next) {
		event_s = (event_cb_s *)l->data;
		if (callback == event_s->cb)
			event_cb_list = g_slist_delete_link(event_cb_list, l);
	}

	return MTP_ERROR_NONE;
}

mtp_error_e mtp_gdbus_manager_initialize(void)
{
	mtp_error_e result = MTP_ERROR_NONE;

	__manager_proxy_init();
	mtp_gdbus_deviceinfo_proxy_init();
	mtp_gdbus_storageinfo_proxy_init();
	mtp_gdbus_objectinfo_proxy_init();

	if (manager_proxy == NULL)
		result = MTP_ERROR_NOT_COMM_INITIALIZED;

	return result;
}

mtp_error_e mtp_gdbus_manager_get_devices(int **mtp_devices, int *device_num)
{
	GVariant *va = NULL;
	mtp_error_e result = MTP_ERROR_NONE;
	GError *error = NULL;

	if (manager_proxy == NULL)
			return MTP_ERROR_NOT_COMM_INITIALIZED;

	if (mtp_gdbuslib_manager_call_get_devices_sync(
			manager_proxy,
			device_num,
			&va,
			&result,
			NULL,
			&error) == FALSE) {
		result = MTP_ERROR_COMM_ERROR;

		g_error_free(error);
		return result;
	}

	if (*device_num != 0 && (g_variant_n_children(va) == *device_num)) {
		GVariantIter *iter = NULL, *iter_row = NULL;
		GVariant *key_value;
		const gchar *key;
		guint i = 0;

		*mtp_devices = g_new(int, *device_num);

		g_variant_get(va, "aa{sv}", &iter);
		while (g_variant_iter_next(iter, "a{sv}", &iter_row)) {
			while (g_variant_iter_loop(iter_row, "{sv}", &key, &key_value)) {
				if (g_strcmp0(key, "mtp_device") == 0)
					(*mtp_devices)[i] = g_variant_get_int32(key_value);
			}
			i++;
			g_variant_iter_free(iter_row);
		}
		g_variant_iter_free(iter);
	}

	g_variant_unref(va);

	return result;
}

mtp_error_e mtp_gdbus_manager_get_storages(int mtp_device,
	int **mtp_storages, int *storage_num)
{
	GVariant *va = NULL;
	mtp_error_e result = MTP_ERROR_NONE;
	GError *error = NULL;

	if (manager_proxy == NULL)
		return MTP_ERROR_NOT_COMM_INITIALIZED;

	if (mtp_gdbuslib_manager_call_get_storages_sync(
			manager_proxy,
			mtp_device,
			storage_num,
			&va,
			&result,
			NULL,
			&error) == FALSE) {
		result = MTP_ERROR_COMM_ERROR;

		g_error_free(error);
		return result;
	}

	if (*storage_num != 0 && (g_variant_n_children(va) == *storage_num)) {
		GVariantIter *iter = NULL, *iter_row = NULL;
		GVariant *key_value;
		const gchar *key;
		guint i = 0;

		*mtp_storages = g_new(int, *storage_num);

		g_variant_get(va, "aa{sv}", &iter);
		while (g_variant_iter_next(iter, "a{sv}", &iter_row)) {
			while (g_variant_iter_loop(iter_row, "{sv}", &key, &key_value)) {
				if (g_strcmp0(key, "mtp_storage") == 0)
					(*mtp_storages)[i] = g_variant_get_int32(key_value);
			}
			i++;
			g_variant_iter_free(iter_row);
		}
		g_variant_iter_free(iter);
	}

	g_variant_unref(va);

	return result;
}

mtp_error_e mtp_gdbus_manager_get_object_handles(int mtp_device,
	int mtp_storage, int file_type, int parent_object_handle, int **object_handles, int *object_num)
{
	GVariant *va = NULL;
	mtp_error_e result = MTP_ERROR_NONE;
	GError *error = NULL;

	if (manager_proxy == NULL)
		return MTP_ERROR_NOT_COMM_INITIALIZED;

	if (mtp_gdbuslib_manager_call_get_object_handles_sync(
			manager_proxy,
			mtp_device,
			mtp_storage,
			file_type,
			parent_object_handle,
			object_num,
			&va,
			&result,
			NULL,
			&error) == FALSE) {
		result = MTP_ERROR_COMM_ERROR;

		g_error_free(error);
		return result;
	}

	if (*object_num != 0 && (g_variant_n_children(va) == *object_num)) {
		GVariantIter *iter = NULL, *iter_row = NULL;
		GVariant *key_value;
		const gchar *key;
		guint i = 0;

		*object_handles = g_new(int, *object_num);

		g_variant_get(va, "aa{sv}", &iter);
		while (g_variant_iter_next(iter, "a{sv}", &iter_row)) {
			while (g_variant_iter_loop(iter_row, "{sv}", &key, &key_value)) {
				if (g_strcmp0(key, "object_handle") == 0)
					(*object_handles)[i] = g_variant_get_int32(key_value);
			}
			i++;
			g_variant_iter_free(iter_row);
		}
		g_variant_iter_free(iter);
	}

	g_variant_unref(va);

	return result;
}

mtp_error_e mtp_gdbus_manager_delete_object(int mtp_device,
	int object_handle)
{
	mtp_error_e result = MTP_ERROR_NONE;
	GError *error = NULL;

	if (manager_proxy == NULL)
			return MTP_ERROR_NOT_COMM_INITIALIZED;

	if (mtp_gdbuslib_manager_call_delete_object_sync(
			manager_proxy,
			mtp_device,
			object_handle,
			&result,
			NULL,
			&error) == FALSE) {
		result = MTP_ERROR_COMM_ERROR;

		g_error_free(error);
	}

	return result;
}

mtp_error_e mtp_gdbus_manager_get_object(int mtp_device,
	int object_handle, char *dest_path)
{
	mtp_error_e result = MTP_ERROR_NONE;
	GError *error = NULL;

	if (manager_proxy == NULL)
			return MTP_ERROR_NOT_COMM_INITIALIZED;

	if (mtp_gdbuslib_manager_call_get_object_sync(
			manager_proxy,
			mtp_device,
			object_handle,
			dest_path,
			&result,
			NULL,
			&error) == FALSE) {
		result = MTP_ERROR_COMM_ERROR;

		g_error_free(error);
	}

	return result;
}

mtp_error_e mtp_gdbus_manager_get_thumbnail(int mtp_device,
	int object_handle, char *dest_path)
{
	mtp_error_e result = MTP_ERROR_NONE;
	GError *error = NULL;

	if (manager_proxy == NULL)
		return MTP_ERROR_NOT_COMM_INITIALIZED;

	if (mtp_gdbuslib_manager_call_get_thumbnail_sync(
			manager_proxy,
			mtp_device,
			object_handle,
			dest_path,
			&result,
			NULL,
			&error) == FALSE) {
		result = MTP_ERROR_COMM_ERROR;

		g_error_free(error);
	}

	return result;
}

mtp_error_e mtp_gdbus_manager_deinitialize(void)
{
	mtp_error_e result = MTP_ERROR_NONE;

	__manager_proxy_deinit();
	mtp_gdbus_deviceinfo_proxy_deinit();
	mtp_gdbus_storageinfo_proxy_deinit();
	mtp_gdbus_objectinfo_proxy_deinit();

	return result;
}
