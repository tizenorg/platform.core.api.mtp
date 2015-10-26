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

#ifndef __MTP_GDBUS_DEVICEINFO_H__
#define __MTP_GDBUS_DEVICEINFO_H__

#include "mtp_gdbus.h"

void mtp_gdbus_deviceinfo_proxy_init(void);
void mtp_gdbus_deviceinfo_proxy_deinit(void);

mtp_error_e mtp_gdbus_deviceinfo_get_manufacturername(int mtp_handle, char **manufacturername);
mtp_error_e mtp_gdbus_deviceinfo_get_modelname(int mtp_handle, char **modelname);
mtp_error_e mtp_gdbus_deviceinfo_get_serialnumber(int mtp_handle, char **serialnumber);
mtp_error_e mtp_gdbus_deviceinfo_get_deviceversion(int mtp_handle, char **deviceversion);

#endif
