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

#ifndef __MTP_GDBUS_MANAGER_H__
#define __MTP_GDBUS_MANAGER_H__

#include "mtp_gdbus.h"

mtp_error_e mtp_gdbus_manager_initialize(void);
mtp_error_e mtp_gdbus_manager_get_device_list(mtp_device_list **dev_list);
mtp_error_e mtp_gdbus_manager_get_device_handle(int bus_location,
	int *device_handle);
mtp_error_e mtp_gdbus_manager_get_storage_ids(int device_handle,
	int **storage_ids, int *storage_num);
mtp_error_e mtp_gdbus_manager_get_object_handles(int device_handle,
	int storage_id, int format, int parent_object_handle, int **object_handles, int *object_num);
mtp_error_e mtp_gdbus_manager_delete_object(int device_handle, int object_handle);
mtp_error_e mtp_gdbus_manager_get_object(int device_handle,
	int object_handle, char *dest_path);
mtp_error_e mtp_gdbus_manager_get_thumbnail(int device_handle,
	int object_handle, char *dest_path);
mtp_error_e mtp_gdbus_manager_set_event_cb(mtp_event_cb callback, void *user_data);
mtp_error_e mtp_gdbus_manager_unset_event_cb();
mtp_error_e mtp_gdbus_manager_deinitialize(void);

#endif
