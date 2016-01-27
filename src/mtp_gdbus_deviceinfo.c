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

#include "mtp_gdbus_deviceinfo.h"

mtpgdbuslibDeviceinfo *deviceinfo_proxy = NULL;

void mtp_gdbus_deviceinfo_proxy_init(void)
{
	deviceinfo_proxy = mtp_gdbuslib_deviceinfo_proxy_new_for_bus_sync(
		G_BUS_TYPE_SYSTEM,
		G_DBUS_PROXY_FLAGS_NONE,
		MTP_DBUS_SERVICE,
		MTP_DBUS_DEVICEINFO_PATH,
		NULL,
		NULL);
}

void mtp_gdbus_deviceinfo_proxy_deinit(void)
{
	deviceinfo_proxy = NULL;
}

mtp_error_e mtp_gdbus_deviceinfo_get_manufacturer_name(int mtp_device, char **manufacturer_name)
{
	mtp_error_e result = MTP_ERROR_NONE;
	GError *error = NULL;

	if (deviceinfo_proxy == NULL)
			return MTP_ERROR_NOT_COMM_INITIALIZED;

	if (mtp_gdbuslib_deviceinfo_call_get_manufacturer_name_sync(
			deviceinfo_proxy,
			mtp_device,
			manufacturer_name,
			&result,
			NULL,
			&error) == FALSE) {
		result = MTP_ERROR_COMM_ERROR;
		g_error_free(error);
	}

	return result;
}

mtp_error_e mtp_gdbus_deviceinfo_get_model_name(int mtp_device, char **model_name)
{
	mtp_error_e result = MTP_ERROR_NONE;
	GError *error = NULL;

	if (deviceinfo_proxy == NULL)
			return MTP_ERROR_NOT_COMM_INITIALIZED;

	if (mtp_gdbuslib_deviceinfo_call_get_model_name_sync(
			deviceinfo_proxy,
			mtp_device,
			model_name,
			&result,
			NULL,
			&error) == FALSE) {
		result = MTP_ERROR_COMM_ERROR;
		g_error_free(error);
	}

	return result;
}

mtp_error_e mtp_gdbus_deviceinfo_get_serial_number(int mtp_device, char **serial_number)
{
	mtp_error_e result = MTP_ERROR_NONE;
	GError *error = NULL;

	if (deviceinfo_proxy == NULL)
			return MTP_ERROR_NOT_COMM_INITIALIZED;

	if (mtp_gdbuslib_deviceinfo_call_get_serial_number_sync(
			deviceinfo_proxy,
			mtp_device,
			serial_number,
			&result,
			NULL,
			&error) == FALSE) {
		result = MTP_ERROR_COMM_ERROR;
		g_error_free(error);
	}

	return result;
}

mtp_error_e mtp_gdbus_deviceinfo_get_device_version(int mtp_device, char **device_version)
{
	mtp_error_e result = MTP_ERROR_NONE;
	GError *error = NULL;

	if (deviceinfo_proxy == NULL)
			return MTP_ERROR_NOT_COMM_INITIALIZED;

	if (mtp_gdbuslib_deviceinfo_call_get_device_version_sync(
			deviceinfo_proxy,
			mtp_device,
			device_version,
			&result,
			NULL,
			&error) == FALSE) {
		result = MTP_ERROR_COMM_ERROR;
		g_error_free(error);
	}

	return result;
}

mtp_error_e mtp_gdbus_deviceinfo_get_bus_location(int mtp_device, int *bus_location)
{
	mtp_error_e result = MTP_ERROR_NONE;
	GError *error = NULL;

	if (deviceinfo_proxy == NULL)
			return MTP_ERROR_NOT_COMM_INITIALIZED;

	if (mtp_gdbuslib_deviceinfo_call_get_bus_location_sync(
			deviceinfo_proxy,
			mtp_device,
			bus_location,
			&result,
			NULL,
			&error) == FALSE) {
		result = MTP_ERROR_COMM_ERROR;
		g_error_free(error);
	}

	return result;
}

mtp_error_e mtp_gdbus_deviceinfo_get_device_number(int mtp_device, int *device_number)
{
	mtp_error_e result = MTP_ERROR_NONE;
	GError *error = NULL;

	if (deviceinfo_proxy == NULL)
			return MTP_ERROR_NOT_COMM_INITIALIZED;

	if (mtp_gdbuslib_deviceinfo_call_get_device_number_sync(
			deviceinfo_proxy,
			mtp_device,
			device_number,
			&result,
			NULL,
			&error) == FALSE) {
		result = MTP_ERROR_COMM_ERROR;
		g_error_free(error);
	}

	return result;
}

