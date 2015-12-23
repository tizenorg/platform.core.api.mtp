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

#include "mtp_gdbus_storageinfo.h"

mtpgdbuslibStorageinfo *storageinfo_proxy = NULL;

void mtp_gdbus_storageinfo_proxy_init(void)
{
	storageinfo_proxy = mtp_gdbuslib_storageinfo_proxy_new_for_bus_sync(
		G_BUS_TYPE_SYSTEM,
		G_DBUS_PROXY_FLAGS_NONE,
		MTP_DBUS_SERVICE,
		MTP_DBUS_STORAGEINFO_PATH,
		NULL,
		NULL);
}

void mtp_gdbus_storageinfo_proxy_deinit(void)
{
	storageinfo_proxy = NULL;
}

mtp_error_e mtp_gdbus_storageinfo_get_description(int device_handle,
	int storage_id, char **description)
{
	mtp_error_e result = MTP_ERROR_NONE;
	GError *error = NULL;

	if (storageinfo_proxy == NULL)
			return MTP_ERROR_NOT_COMM_INITIALIZED;

	if (mtp_gdbuslib_storageinfo_call_get_description_sync(
			storageinfo_proxy,
			device_handle,
			storage_id,
			description,
			&result,
			NULL,
			&error) == FALSE) {
		result = MTP_ERROR_COMM;
		g_error_free(error);
	}

	return result;
}

mtp_error_e mtp_gdbus_storageinfo_get_freespace(int device_handle,
	int storage_id, guint64 *freespace)
{
	mtp_error_e result = MTP_ERROR_NONE;
	GError *error = NULL;

	if (storageinfo_proxy == NULL)
			return MTP_ERROR_NOT_COMM_INITIALIZED;

	if (mtp_gdbuslib_storageinfo_call_get_free_space_sync(
			storageinfo_proxy,
			device_handle,
			storage_id,
			freespace,
			&result,
			NULL,
			&error) == FALSE) {
		result = MTP_ERROR_COMM;
		g_error_free(error);
	}

	return result;
}

mtp_error_e mtp_gdbus_storageinfo_get_maxcapacity(int device_handle,
	int storage_id, guint64 *maxcapacity)
{
	mtp_error_e result = MTP_ERROR_NONE;
	GError *error = NULL;

	if (storageinfo_proxy == NULL)
			return MTP_ERROR_NOT_COMM_INITIALIZED;

	if (mtp_gdbuslib_storageinfo_call_get_max_capacity_sync(
			storageinfo_proxy,
			device_handle,
			storage_id,
			maxcapacity,
			&result,
			NULL,
			&error) == FALSE) {
		result = MTP_ERROR_COMM;
		g_error_free(error);
	}

	return result;
}

mtp_error_e mtp_gdbus_storageinfo_get_storagetype(int device_handle,
	int storage_id, int *storagetype)
{
	mtp_error_e result = MTP_ERROR_NONE;
	GError *error = NULL;

	if (storageinfo_proxy == NULL)
			return MTP_ERROR_NOT_COMM_INITIALIZED;

	if (mtp_gdbuslib_storageinfo_call_get_storage_type_sync(
			storageinfo_proxy,
			device_handle,
			storage_id,
			storagetype,
			&result,
			NULL,
			&error) == FALSE) {
		result = MTP_ERROR_COMM;
		g_error_free(error);
	}

	return result;
}

mtp_error_e mtp_gdbus_storageinfo_get_volumeidentifier(int device_handle,
	int storage_id, char **volumeidentifier)
{
	mtp_error_e result = MTP_ERROR_NONE;
	GError *error = NULL;

	if (storageinfo_proxy == NULL)
		return MTP_ERROR_NOT_COMM_INITIALIZED;

	if (mtp_gdbuslib_storageinfo_call_get_volume_identifier_sync(
			storageinfo_proxy,
			device_handle,
			storage_id,
			volumeidentifier,
			&result,
			NULL,
			&error) == FALSE) {
		result = MTP_ERROR_COMM;
		g_error_free(error);
	}

	return result;
}
