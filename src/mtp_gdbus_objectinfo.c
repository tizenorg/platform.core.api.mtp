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

#include "mtp_gdbus_objectinfo.h"

mtpgdbuslibObjectinfo *objectinfo_proxy = NULL;

void mtp_gdbus_objectinfo_proxy_init(void)
{
	objectinfo_proxy = mtp_gdbuslib_objectinfo_proxy_new_for_bus_sync(
		 G_BUS_TYPE_SYSTEM,
		 G_DBUS_PROXY_FLAGS_NONE,
		 MTP_DBUS_SERVICE,
		 MTP_DBUS_OBJECTINFO_PATH,
		 NULL,
		 NULL);
}

void mtp_gdbus_objectinfo_proxy_deinit(void)
{
	objectinfo_proxy = NULL;
}

int mtp_gdbus_objectinfo_get_property(int mtp_device,
	int object_handle, int property, int *property_value)
{
	mtp_error_e result = MTP_ERROR_NONE;
	GError *error = NULL;

	if (objectinfo_proxy == NULL)
			return MTP_ERROR_NOT_COMM_INITIALIZED;

	if (mtp_gdbuslib_objectinfo_call_get_property_sync(
			objectinfo_proxy,
			mtp_device,
			object_handle,
			property,
			property_value,
			&result,
			NULL,
			&error) == FALSE) {
		result = MTP_ERROR_COMM;
		g_error_free(error);
	}

	return result;
}

int mtp_gdbus_objectinfo_get_property_string(int mtp_device,
	int object_handle, int property, char **property_value)
{
	mtp_error_e result = MTP_ERROR_NONE;
	GError *error = NULL;

	if (objectinfo_proxy == NULL)
			return MTP_ERROR_NOT_COMM_INITIALIZED;

	if (mtp_gdbuslib_objectinfo_call_get_property_string_sync(
			objectinfo_proxy,
			mtp_device,
			object_handle,
			property,
			property_value,
			&result,
			NULL,
			&error) == FALSE) {
		result = MTP_ERROR_COMM;
		g_error_free(error);
	}

	return result;
}

