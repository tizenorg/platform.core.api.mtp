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

mtp_error_e mtp_gdbus_storageinfo_get_description(int mtp_device,
	int mtp_storage, char **description)
{
	mtp_error_e result = MTP_ERROR_NONE;
	GError *error = NULL;

	if (storageinfo_proxy == NULL)
			return MTP_ERROR_NOT_COMM_INITIALIZED;

	if (mtp_gdbuslib_storageinfo_call_get_description_sync(
			storageinfo_proxy,
			mtp_device,
			mtp_storage,
			description,
			&result,
			NULL,
			&error) == FALSE) {
		result = MTP_ERROR_COMM_ERROR;
		g_error_free(error);
	}

	return result;
}

mtp_error_e mtp_gdbus_storageinfo_get_free_space(int mtp_device,
	int mtp_storage, guint64 *free_space)
{
	mtp_error_e result = MTP_ERROR_NONE;
	GError *error = NULL;

	if (storageinfo_proxy == NULL)
			return MTP_ERROR_NOT_COMM_INITIALIZED;

	if (mtp_gdbuslib_storageinfo_call_get_free_space_sync(
			storageinfo_proxy,
			mtp_device,
			mtp_storage,
			free_space,
			&result,
			NULL,
			&error) == FALSE) {
		result = MTP_ERROR_COMM_ERROR;
		g_error_free(error);
	}

	return result;
}

mtp_error_e mtp_gdbus_storageinfo_get_max_capacity(int mtp_device,
	int mtp_storage, guint64 *max_capacity)
{
	mtp_error_e result = MTP_ERROR_NONE;
	GError *error = NULL;

	if (storageinfo_proxy == NULL)
			return MTP_ERROR_NOT_COMM_INITIALIZED;

	if (mtp_gdbuslib_storageinfo_call_get_max_capacity_sync(
			storageinfo_proxy,
			mtp_device,
			mtp_storage,
			max_capacity,
			&result,
			NULL,
			&error) == FALSE) {
		result = MTP_ERROR_COMM_ERROR;
		g_error_free(error);
	}

	return result;
}

mtp_error_e mtp_gdbus_storageinfo_get_storage_type(int mtp_device,
	int mtp_storage, int *storage_type)
{
	mtp_error_e result = MTP_ERROR_NONE;
	GError *error = NULL;

	if (storageinfo_proxy == NULL)
			return MTP_ERROR_NOT_COMM_INITIALIZED;

	if (mtp_gdbuslib_storageinfo_call_get_storage_type_sync(
			storageinfo_proxy,
			mtp_device,
			mtp_storage,
			storage_type,
			&result,
			NULL,
			&error) == FALSE) {
		result = MTP_ERROR_COMM_ERROR;
		g_error_free(error);
	}

	return result;
}

mtp_error_e mtp_gdbus_storageinfo_get_volume_identifier(int mtp_device,
	int mtp_storage, char **volume_identifier)
{
	mtp_error_e result = MTP_ERROR_NONE;
	GError *error = NULL;

	if (storageinfo_proxy == NULL)
		return MTP_ERROR_NOT_COMM_INITIALIZED;

	if (mtp_gdbuslib_storageinfo_call_get_volume_identifier_sync(
			storageinfo_proxy,
			mtp_device,
			mtp_storage,
			volume_identifier,
			&result,
			NULL,
			&error) == FALSE) {
		result = MTP_ERROR_COMM_ERROR;
		g_error_free(error);
	}

	return result;
}
