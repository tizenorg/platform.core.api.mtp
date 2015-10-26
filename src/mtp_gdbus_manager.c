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

#include "mtp_gdbus_manager.h"
#include "mtp_gdbus_objectinfo.h"
#include "mtp_gdbus_deviceinfo.h"
#include "mtp_gdbus_storageinfo.h"

mtpgdbuslibManager *manager_proxy = NULL;
mtp_event_cb event_callback;
void *event_user_data;

static void __mtp_event_cb(mtpgdbuslibManager *object,
	gint event, gint arg1, gpointer user_data)
{
	if (event_callback)
		event_callback(event, arg1, event_user_data);
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

mtp_error_e mtp_gdbus_manager_set_event_cb(mtp_event_cb callback, void *user_data)
{
	event_callback = callback;
	event_user_data = user_data;

	return MTP_ERROR_NONE;
}

mtp_error_e mtp_gdbus_manager_unset_event_cb(void)
{
	event_callback = NULL;
	event_user_data = NULL;

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
		result = MTP_ERROR_GENERAL;

	return result;
}

mtp_error_e mtp_gdbus_manager_get_device_list(mtp_device_list **dev_list)
{
	int dev_count;
	GVariant *va = NULL;
	mtp_error_e result = MTP_ERROR_NONE;
	GError *error = NULL;

	if (manager_proxy == NULL)
		return MTP_ERROR_GENERAL;

	if (mtp_gdbuslib_manager_call_get_device_list_sync(
			manager_proxy,
			&dev_count,
			&va,
			&result,
			NULL,
			&error) == FALSE) {
		result = MTP_ERROR_IO_ERROR;

		g_error_free(error);
		return result;
	}

	if (dev_count != 0 && (g_variant_n_children(va) == dev_count)) {
		GVariantIter *iter = NULL, *iter_row = NULL;
		GVariant *key_value;
		const gchar *key;
		guint i = 0;

		*dev_list = g_new(mtp_device_list, 1);
		(*dev_list)->device_num = dev_count;
		(*dev_list)->devices = g_new(mtp_device, dev_count);

		g_variant_get(va, "aa{sv}", &iter);
		while (g_variant_iter_next(iter, "a{sv}", &iter_row)) {
			while (g_variant_iter_loop(iter_row, "{sv}", &key, &key_value)) {
				if (g_strcmp0(key, "model_name") == 0) {
					((*dev_list)->devices)[i].model_name =
						g_strdup(g_variant_get_string(key_value, NULL));
				} else if (g_strcmp0(key, "bus_location") == 0) {
					((*dev_list)->devices)[i].bus_location = g_variant_get_int32(key_value);
				}
			}
			i++;
			g_variant_iter_free(iter_row);
		}
		g_variant_iter_free(iter);
	} else {
		result = MTP_ERROR_NO_DEVICE;
	}

	g_variant_unref(va);

	return result;
}

mtp_error_e mtp_gdbus_manager_get_device_handle(int bus_location, int *device_handle)
{
	mtp_error_e result = MTP_ERROR_NONE;
	GError *error = NULL;

	if (manager_proxy == NULL)
			return MTP_ERROR_GENERAL;

	if (mtp_gdbuslib_manager_call_get_device_handle_sync(
			manager_proxy,
			bus_location,
			device_handle,
			&result,
			NULL,
			&error) == FALSE) {
		result = MTP_ERROR_IO_ERROR;

		g_error_free(error);
	}

	return result;
}

mtp_error_e mtp_gdbus_manager_get_storage_ids(int device_handle,
	int **storage_ids, int *storage_num)
{
	GVariant *va = NULL;
	mtp_error_e result = MTP_ERROR_NONE;
	GError *error = NULL;

	if (manager_proxy == NULL)
		return MTP_ERROR_GENERAL;

	if (mtp_gdbuslib_manager_call_get_storage_ids_sync(
			manager_proxy,
			device_handle,
			storage_num,
			&va,
			&result,
			NULL,
			&error) == FALSE) {
		result = MTP_ERROR_IO_ERROR;

		g_error_free(error);
		return result;
	}

	if (*storage_num != 0 && (g_variant_n_children(va) == *storage_num)) {
		GVariantIter *iter = NULL, *iter_row = NULL;
		GVariant *key_value;
		const gchar *key;
		guint i = 0;

		*storage_ids = g_new(int, *storage_num);

		g_variant_get(va, "aa{sv}", &iter);
		while (g_variant_iter_next(iter, "a{sv}", &iter_row)) {
			while (g_variant_iter_loop(iter_row, "{sv}", &key, &key_value)) {
				if (g_strcmp0(key, "storage_id") == 0)
					(*storage_ids)[i] = g_variant_get_int32(key_value);
			}
			i++;
			g_variant_iter_free(iter_row);
		}
		g_variant_iter_free(iter);
	}

	g_variant_unref(va);

	return result;
}

mtp_error_e mtp_gdbus_manager_get_object_handles(int device_handle,
	int storage_id, int format, int parent_object_handle, int **object_handles, int *object_num)
{
	GVariant *va = NULL;
	mtp_error_e result = MTP_ERROR_NONE;
	GError *error = NULL;

	if (manager_proxy == NULL)
		return MTP_ERROR_GENERAL;

	if (mtp_gdbuslib_manager_call_get_object_handles_sync(
			manager_proxy,
			device_handle,
			storage_id,
			format,
			parent_object_handle,
			object_num,
			&va,
			&result,
			NULL,
			&error) == FALSE) {
		result = MTP_ERROR_IO_ERROR;

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

mtp_error_e mtp_gdbus_manager_delete_object(int device_handle,
	int object_handle)
{
	mtp_error_e result = MTP_ERROR_NONE;
	GError *error = NULL;

	if (manager_proxy == NULL)
			return MTP_ERROR_GENERAL;

	if (mtp_gdbuslib_manager_call_delete_object_sync(
			manager_proxy,
			device_handle,
			object_handle,
			&result,
			NULL,
			&error) == FALSE) {
		result = MTP_ERROR_IO_ERROR;

		g_error_free(error);
	}

	return result;
}

mtp_error_e mtp_gdbus_manager_get_object(int device_handle,
	int object_handle, char *dest_path)
{
	mtp_error_e result = MTP_ERROR_NONE;
	GError *error = NULL;

	if (manager_proxy == NULL)
			return MTP_ERROR_GENERAL;

	if (mtp_gdbuslib_manager_call_get_object_sync(
			manager_proxy,
			device_handle,
			object_handle,
			dest_path,
			&result,
			NULL,
			&error) == FALSE) {
		result = MTP_ERROR_IO_ERROR;

		g_error_free(error);
	}

	return result;
}

mtp_error_e mtp_gdbus_manager_get_thumbnail(int device_handle,
	int object_handle, char *dest_path)
{
	mtp_error_e result = MTP_ERROR_NONE;
	GError *error = NULL;

	if (manager_proxy == NULL)
		return MTP_ERROR_GENERAL;

	if (mtp_gdbuslib_manager_call_get_thumbnail_sync(
			manager_proxy,
			device_handle,
			object_handle,
			dest_path,
			&result,
			NULL,
			&error) == FALSE) {
		result = MTP_ERROR_IO_ERROR;

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
