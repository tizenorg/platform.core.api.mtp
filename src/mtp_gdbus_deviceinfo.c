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

mtp_error_e mtp_gdbus_deviceinfo_get_manufacturername(int mtp_device, char **manufacturername)
{
	mtp_error_e result = MTP_ERROR_NONE;
	GError *error = NULL;

	if (deviceinfo_proxy == NULL)
			return MTP_ERROR_NOT_COMM_INITIALIZED;

	if (mtp_gdbuslib_deviceinfo_call_get_manufacturername_sync(
			deviceinfo_proxy,
			mtp_device,
			manufacturername,
			&result,
			NULL,
			&error) == FALSE) {
		result = MTP_ERROR_COMM_ERROR;
		g_error_free(error);
	}

	return result;
}

mtp_error_e mtp_gdbus_deviceinfo_get_modelname(int mtp_device, char **modelname)
{
	mtp_error_e result = MTP_ERROR_NONE;
	GError *error = NULL;

	if (deviceinfo_proxy == NULL)
			return MTP_ERROR_NOT_COMM_INITIALIZED;

	if (mtp_gdbuslib_deviceinfo_call_get_modelname_sync(
			deviceinfo_proxy,
			mtp_device,
			modelname,
			&result,
			NULL,
			&error) == FALSE) {
		result = MTP_ERROR_COMM_ERROR;
		g_error_free(error);
	}

	return result;
}

mtp_error_e mtp_gdbus_deviceinfo_get_serialnumber(int mtp_device, char **serialnumber)
{
	mtp_error_e result = MTP_ERROR_NONE;
	GError *error = NULL;

	if (deviceinfo_proxy == NULL)
			return MTP_ERROR_NOT_COMM_INITIALIZED;

	if (mtp_gdbuslib_deviceinfo_call_get_serialnumber_sync(
			deviceinfo_proxy,
			mtp_device,
			serialnumber,
			&result,
			NULL,
			&error) == FALSE) {
		result = MTP_ERROR_COMM_ERROR;
		g_error_free(error);
	}

	return result;
}

mtp_error_e mtp_gdbus_deviceinfo_get_deviceversion(int mtp_device, char **deviceversion)
{
	mtp_error_e result = MTP_ERROR_NONE;
	GError *error = NULL;

	if (deviceinfo_proxy == NULL)
			return MTP_ERROR_NOT_COMM_INITIALIZED;

	if (mtp_gdbuslib_deviceinfo_call_get_deviceversion_sync(
			deviceinfo_proxy,
			mtp_device,
			deviceversion,
			&result,
			NULL,
			&error) == FALSE) {
		result = MTP_ERROR_COMM_ERROR;
		g_error_free(error);
	}

	return result;
}

