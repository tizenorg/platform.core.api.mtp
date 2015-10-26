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

#ifndef __MTP_GDBUS_STORAGEINFO_H__
#define __MTP_GDBUS_STORAGEINFO_H__

#include "mtp_gdbus.h"

void mtp_gdbus_storageinfo_proxy_init(void);
void mtp_gdbus_storageinfo_proxy_deinit(void);

mtp_error_e mtp_gdbus_storageinfo_get_description(int device_handle,
	int storage_id, char **description);
mtp_error_e mtp_gdbus_storageinfo_get_freespace(int device_handle,
	int storage_id, guint64 *freespace);
mtp_error_e mtp_gdbus_storageinfo_get_maxcapacity(int device_handle,
	int storage_id, guint64 *maxcapacity);
mtp_error_e mtp_gdbus_storageinfo_get_storagetype(int device_handle,
	int storage_id, int *storagetype);
mtp_error_e mtp_gdbus_storageinfo_get_volumeidentifier(int device_handle,
	int storage_id, char **volumeidentifier);

#endif
