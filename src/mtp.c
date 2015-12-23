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

#include <dlog.h>

#include "mtp.h"
#include "mtp_internal.h"
#include "mtp_db.h"
#include "mtp_debug.h"
#include "mtp_private.h"

#include "mtp_gdbus_manager.h"
#include "mtp_gdbus_deviceinfo.h"
#include "mtp_gdbus_storageinfo.h"
#include "mtp_gdbus_objectinfo.h"

#define MTP_LOCK \
do { \
	pthread_mutex_lock(&mutex); \
} while (0);

#define MTP_UNLOCK \
do { \
	pthread_mutex_unlock(&mutex); \
} while (0);

static pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

#define CHECK_INIT() \
do { \
	MTP_LOCK; \
		{ \
			if (__is_initialized == false) { \
				MTP_UNLOCK; \
				return MTP_ERROR_NOT_INITIALIZED; \
			} \
		} \
	MTP_UNLOCK; \
} while (0);

int ref_count = 0;
bool __is_initialized = false;

static bool __is_mtp_supported()
{
	return true;
}

static bool __is_mtp_activated()
{
	return true;
}

/* Device Manager */
int mtp_initialize(void)
{
	int ret = MTP_ERROR_NONE;

	_BEGIN();

	/* precondition check start */

	CHECK_SUPPORTED();

	/* precondition check end */

	MTP_LOCK;

	if (__is_initialized == false) {
		ret = mtp_gdbus_manager_initialize();
		mtp_db_init();
		__is_initialized = true;
	}
	ref_count++;

	MTP_UNLOCK;

	_END();

	return ret;
}

int mtp_get_raw_devices(mtp_raw_device_h **raw_devices, int *device_count)
{
	int ret = MTP_ERROR_NONE;

	_BEGIN();

	/* precondition check start */

	CHECK_SUPPORTED();
	CHECK_INIT();
	CHECK_ACTIVATED();
	cond_expr_ret(device_count == NULL, MTP_ERROR_INVALID_PARAMETER);

	/* precondition check end */
	*device_count = 0;

	ret = mtp_gdbus_manager_get_raw_devices((mtp_raw_device ***)raw_devices, device_count);

	_END();

	return ret;
}

int mtp_get_bus_location(mtp_raw_device_h raw_device, int *bus_location)
{
	int ret = MTP_ERROR_NONE;

	_BEGIN();

	/* precondition check start */

	CHECK_SUPPORTED();
	CHECK_INIT();
	cond_expr_ret(raw_device == NULL, MTP_ERROR_INVALID_PARAMETER);
	cond_expr_ret(bus_location == NULL, MTP_ERROR_INVALID_PARAMETER);

	/* precondition check end */

	*bus_location = ((mtp_raw_device *)raw_device)->bus_location;

	_END();

	return ret;
}

int mtp_get_device_number(mtp_raw_device_h raw_device, int *device_number)
{
	int ret = MTP_ERROR_NONE;

	_BEGIN();

	/* precondition check start */

	CHECK_SUPPORTED();
	CHECK_INIT();
	cond_expr_ret(raw_device == NULL, MTP_ERROR_INVALID_PARAMETER);
	cond_expr_ret(device_number == NULL, MTP_ERROR_INVALID_PARAMETER);

	/* precondition check end */

	*device_number = ((mtp_raw_device *)raw_device)->device_number;

	_END();

	return ret;
}

int mtp_get_device_name(mtp_raw_device_h raw_device, char **model_name)
{
	int ret = MTP_ERROR_NONE;

	/* precondition check start */

	CHECK_SUPPORTED();
	CHECK_INIT();
	cond_expr_ret(raw_device == NULL, MTP_ERROR_INVALID_PARAMETER);
	cond_expr_ret(model_name == NULL, MTP_ERROR_INVALID_PARAMETER);

	/* precondition check end */

	*model_name = g_strdup(((mtp_raw_device *)raw_device)->model_name);

	return ret;
}

int mtp_destroy_raw_devices(mtp_raw_device_h *raw_devices)
{
	int i;
	int ret = MTP_ERROR_NONE;
	int dev_count;
	mtp_raw_device *first_device = (mtp_raw_device *)raw_devices[0];

	_BEGIN();

	/* precondition check start */

	CHECK_SUPPORTED();
	cond_expr_ret(raw_devices == NULL, MTP_ERROR_INVALID_PARAMETER);
	cond_expr_ret(first_device == NULL, MTP_ERROR_INVALID_PARAMETER);

	/* precondition check end */
	dev_count = first_device->dev_count;
	if (dev_count <= 0 || dev_count > 6)
		return MTP_ERROR_INVALID_PARAMETER;

	for (i = 0; i < dev_count; i++) {
		mtp_raw_device *r_device = (mtp_raw_device *)raw_devices[i];

		if (r_device != NULL && r_device->model_name != NULL) {
			free(r_device->model_name);
			free(r_device);
		}
	}

	free(raw_devices);

	_END();

	return ret;
}

int mtp_get_device(int bus_location, int device_number, int *mtp_device)
{
	int ret = MTP_ERROR_NONE;

	_BEGIN();

	/* precondition check start */

	CHECK_SUPPORTED();
	CHECK_INIT();
	CHECK_ACTIVATED();
	cond_expr_ret(bus_location == 0, MTP_ERROR_INVALID_PARAMETER);

	/* precondition check end */

	ret = mtp_gdbus_manager_get_device(bus_location, device_number, mtp_device);

	TC_PRT("mtp_device %d", *mtp_device);

	_END();

	return ret;
}

int mtp_get_storages(int mtp_device, int **mtp_storages, int* storage_num)
{
	int ret = MTP_ERROR_NONE;

	_BEGIN();

	/* precondition check start */

	CHECK_SUPPORTED();
	CHECK_INIT();
	CHECK_ACTIVATED();
	cond_expr_ret(mtp_device == 0, MTP_ERROR_INVALID_PARAMETER);

	/* precondition check end */

	ret = mtp_gdbus_manager_get_storages(mtp_device, mtp_storages, storage_num);

	TC_PRT("storage number %d", *storage_num);

	_END();

	return ret;
}

int mtp_get_object_handles(int mtp_device, int mtp_storage, mtp_filetype_e file_type,
	int parent, int **object_handles, int* object_num)
{
	int ret = MTP_ERROR_NONE;

	_BEGIN();

	/* precondition check start */

	CHECK_SUPPORTED();
	CHECK_INIT();
	CHECK_ACTIVATED();
	cond_expr_ret(mtp_device == 0, MTP_ERROR_INVALID_PARAMETER);
	cond_expr_ret(mtp_storage == 0, MTP_ERROR_INVALID_PARAMETER);

	/* precondition check end */

	ret = mtp_gdbus_manager_get_object_handles(mtp_device,
		mtp_storage, file_type, parent, object_handles, object_num);

	_END();

	return ret;
}

int mtp_delete_object(int mtp_device, int object_handle)
{
	int ret = MTP_ERROR_NONE;

	_BEGIN();

	/* precondition check start */

	CHECK_SUPPORTED();
	CHECK_INIT();
	CHECK_ACTIVATED();
	cond_expr_ret(mtp_device == 0, MTP_ERROR_INVALID_PARAMETER);
	cond_expr_ret(object_handle == 0, MTP_ERROR_INVALID_PARAMETER);

	/* precondition check end */

	ret = mtp_gdbus_manager_delete_object(mtp_device, object_handle);

	_END();

	return ret;
}

int mtp_get_object(int mtp_device, int object_handle, char *dest_path)
{
	int ret = MTP_ERROR_NONE;

	_BEGIN();

	/* precondition check start */

	CHECK_SUPPORTED();
	CHECK_INIT();
	CHECK_ACTIVATED();
	cond_expr_ret(mtp_device == 0, MTP_ERROR_INVALID_PARAMETER);
	cond_expr_ret(dest_path == NULL, MTP_ERROR_INVALID_PARAMETER);

	/* precondition check end */

	ret = mtp_gdbus_manager_get_object(mtp_device, object_handle, dest_path);

	_END();

	return ret;
}

int mtp_get_thumbnail(int mtp_device, int object_handle, char *dest_path)
{
	int ret = MTP_ERROR_NONE;

	_BEGIN();

	/* precondition check start */

	CHECK_SUPPORTED();
	CHECK_INIT();
	CHECK_ACTIVATED();
	cond_expr_ret(mtp_device == 0, MTP_ERROR_INVALID_PARAMETER);
	cond_expr_ret(dest_path == NULL, MTP_ERROR_INVALID_PARAMETER);

	/* precondition check end */

	ret = mtp_gdbus_manager_get_thumbnail(mtp_device, object_handle, dest_path);

	_END();

	return ret;
}

int mtp_set_mtp_event_cb(mtp_event_cb callback, void *user_data)
{
	int ret = MTP_ERROR_NONE;

	_BEGIN();

	/* precondition check start */

	CHECK_SUPPORTED();
	CHECK_INIT();
	cond_expr_ret(callback == NULL, MTP_ERROR_INVALID_PARAMETER);

	/* precondition check end */

	ret = mtp_gdbus_manager_set_event_cb(callback, user_data);

	_END();

	return ret;
}

int mtp_unset_mtp_event_cb(void)
{
	int ret = MTP_ERROR_NONE;

	_BEGIN();

	/* precondition check start */

	CHECK_SUPPORTED();
	CHECK_INIT();

	/* precondition check end */

	ret = mtp_gdbus_manager_unset_event_cb();

	_END();

	return ret;
}

int mtp_deinitialize(void)
{
	int ret = MTP_ERROR_NONE;

	_BEGIN();

	/* precondition check start */

	CHECK_SUPPORTED();

	/* precondition check end */

	MTP_LOCK;

	if (ref_count > 0)
		ref_count--;

	if (__is_initialized == true && ref_count == 0) {
		mtp_db_deinit();
		ret = mtp_gdbus_manager_deinitialize();
		__is_initialized = false;
	}

	MTP_UNLOCK;

	_END();

	return ret;
}

/* Device Info */
int mtp_deviceinfo_get_manufacturer_name(int mtp_device, char **manufacturer_name)
{
	int ret = MTP_ERROR_NONE;

	_BEGIN();

	/* precondition check start */

	CHECK_SUPPORTED();
	CHECK_INIT();
	CHECK_ACTIVATED();
	cond_expr_ret(mtp_device == 0, MTP_ERROR_INVALID_PARAMETER);

	/* precondition check end */

	ret = mtp_gdbus_deviceinfo_get_manufacturername(mtp_device, manufacturer_name);

	TC_PRT("manufacturername %s", *manufacturer_name);

	_END();

	return ret;
}

int mtp_deviceinfo_get_model_name(int mtp_device, char **model_name)
{
	int ret = MTP_ERROR_NONE;

	_BEGIN();

	/* precondition check start */

	CHECK_SUPPORTED();
	CHECK_INIT();
	CHECK_ACTIVATED();
	cond_expr_ret(mtp_device == 0, MTP_ERROR_INVALID_PARAMETER);

	/* precondition check end */

	ret = mtp_gdbus_deviceinfo_get_modelname(mtp_device, model_name);

	TC_PRT("modelname %s", *model_name);

	_END();

	return ret;
}

int mtp_deviceinfo_get_serial_number(int mtp_device, char **serial_number)
{
	int ret = MTP_ERROR_NONE;

	_BEGIN();

	/* precondition check start */

	CHECK_SUPPORTED();
	CHECK_INIT();
	CHECK_ACTIVATED();
	cond_expr_ret(mtp_device == 0, MTP_ERROR_INVALID_PARAMETER);

	/* precondition check end */

	ret = mtp_gdbus_deviceinfo_get_serialnumber(mtp_device, serial_number);

	TC_PRT("serialnumber %s", *serial_number);

	_END();

	return ret;
}

int mtp_deviceinfo_get_device_version(int mtp_device, char **device_version)
{
	int ret = MTP_ERROR_NONE;

	_BEGIN();

	/* precondition check start */

	CHECK_SUPPORTED();
	CHECK_INIT();
	CHECK_ACTIVATED();
	cond_expr_ret(mtp_device == 0, MTP_ERROR_INVALID_PARAMETER);

	/* precondition check end */

	ret = mtp_gdbus_deviceinfo_get_deviceversion(mtp_device, device_version);

	TC_PRT("deviceversion %s", *device_version);

	_END();

	return ret;
}

/* Storage Info */
int mtp_storageinfo_get_description(int mtp_device, int mtp_storage, char **description)
{
	int ret = MTP_ERROR_NONE;

	_BEGIN();

	/* precondition check start */

	CHECK_SUPPORTED();
	CHECK_INIT();
	CHECK_ACTIVATED();
	cond_expr_ret(mtp_device == 0, MTP_ERROR_INVALID_PARAMETER);
	cond_expr_ret(mtp_storage == 0, MTP_ERROR_INVALID_PARAMETER);

	/* precondition check end */

	ret = mtp_gdbus_storageinfo_get_description(mtp_device, mtp_storage, description);

	TC_PRT("description %s", *description);

	_END();

	return ret;
}

int mtp_storageinfo_get_free_space(int mtp_device, int mtp_storage, unsigned long long *free_space)
{
	int ret = MTP_ERROR_NONE;

	_BEGIN();

	/* precondition check start */

	CHECK_SUPPORTED();
	CHECK_INIT();
	CHECK_ACTIVATED();
	cond_expr_ret(mtp_device == 0, MTP_ERROR_INVALID_PARAMETER);
	cond_expr_ret(mtp_storage == 0, MTP_ERROR_INVALID_PARAMETER);

	/* precondition check end */

	ret = mtp_gdbus_storageinfo_get_freespace(mtp_device, mtp_storage, (guint64 *)free_space);

	TC_PRT("freespace %llu", *free_space);

	_END();

	return ret;
}

int mtp_storageinfo_get_max_capacity(int mtp_device, int mtp_storage, unsigned long long *max_capacity)
{
	int ret = MTP_ERROR_NONE;

	_BEGIN();

	/* precondition check start */

	CHECK_SUPPORTED();
	CHECK_INIT();
	CHECK_ACTIVATED();
	cond_expr_ret(mtp_device == 0, MTP_ERROR_INVALID_PARAMETER);
	cond_expr_ret(mtp_storage == 0, MTP_ERROR_INVALID_PARAMETER);

	/* precondition check end */

	ret = mtp_gdbus_storageinfo_get_maxcapacity(mtp_device, mtp_storage, (guint64 *)max_capacity);

	TC_PRT("maxcapacity %llu", *max_capacity);

	_END();

	return ret;
}

int mtp_storageinfo_get_storage_type(int mtp_device, int mtp_storage, int *storage_type)
{
	int ret = MTP_ERROR_NONE;

	_BEGIN();

	/* precondition check start */

	CHECK_SUPPORTED();
	CHECK_INIT();
	CHECK_ACTIVATED();
	cond_expr_ret(mtp_device == 0, MTP_ERROR_INVALID_PARAMETER);
	cond_expr_ret(mtp_storage == 0, MTP_ERROR_INVALID_PARAMETER);

	/* precondition check end */

	ret = mtp_gdbus_storageinfo_get_storagetype(mtp_device, mtp_storage, storage_type);

	TC_PRT("storagetype %d", *storage_type);

	_END();

	return ret;
}

int mtp_storageinfo_get_volume_identifier(int mtp_device, int mtp_storage, char **volume_identifier)
{
	int ret = MTP_ERROR_NONE;

	_BEGIN();

	/* precondition check start */

	CHECK_SUPPORTED();
	CHECK_INIT();
	CHECK_ACTIVATED();
	cond_expr_ret(mtp_device == 0, MTP_ERROR_INVALID_PARAMETER);
	cond_expr_ret(mtp_storage == 0, MTP_ERROR_INVALID_PARAMETER);

	/* precondition check end */

	ret = mtp_gdbus_storageinfo_get_volumeidentifier(mtp_device, mtp_storage, volume_identifier);

	TC_PRT("volumeidentifier %s", *volume_identifier);

	_END();

	return ret;
}

/* Object Info */
int mtp_objectinfo_get_parent_object_handle(int mtp_device, int object_handle,
	int *parent_object_handle)
{
	int ret = MTP_ERROR_NONE;

	_BEGIN();

	/* precondition check start */

	CHECK_SUPPORTED();
	CHECK_INIT();
	CHECK_ACTIVATED();
	cond_expr_ret(mtp_device == 0, MTP_ERROR_INVALID_PARAMETER);

	/* precondition check end */

	ret = mtp_gdbus_objectinfo_get_property(mtp_device,
		object_handle, MTP_PROPERTY_PARENT_OBJECT_HANDLE, parent_object_handle);

	TC_PRT("parent object id %d", *parent_object_handle);

	_END();

	return ret;
}

int mtp_objectinfo_get_storage(int mtp_device, int object_handle,
	int *mtp_storage)
{
	int ret = MTP_ERROR_NONE;

	_BEGIN();

	/* precondition check start */

	CHECK_SUPPORTED();
	CHECK_INIT();
	CHECK_ACTIVATED();
	cond_expr_ret(mtp_device == 0, MTP_ERROR_INVALID_PARAMETER);

	/* precondition check end */

	ret = mtp_gdbus_objectinfo_get_property(mtp_device,
		object_handle, MTP_PROPERTY_STORAGE, mtp_storage);

	_END();

	return ret;
}

int mtp_objectinfo_get_association_desc(int mtp_device,
	int object_handle, int *asso_desc)
{
	int ret = MTP_ERROR_NONE;

	_BEGIN();

	/* precondition check start */

	CHECK_SUPPORTED();
	CHECK_INIT();
	CHECK_ACTIVATED();
	cond_expr_ret(mtp_device == 0, MTP_ERROR_INVALID_PARAMETER);

	/* precondition check end */

	ret = mtp_gdbus_objectinfo_get_property(mtp_device,
		object_handle, MTP_PROPERTY_ASSOCIATION_DESC, asso_desc);

	_END();

	return ret;
}

int mtp_objectinfo_get_association_type(int mtp_device,
	int object_handle, int *asso_type)
{
	int ret = MTP_ERROR_NONE;

	_BEGIN();

	/* precondition check start */

	CHECK_SUPPORTED();
	CHECK_INIT();
	CHECK_ACTIVATED();
	cond_expr_ret(mtp_device == 0, MTP_ERROR_INVALID_PARAMETER);

	/* precondition check end */

	ret = mtp_gdbus_objectinfo_get_property(mtp_device,
		object_handle, MTP_PROPERTY_ASSOCIATION_TYPE, asso_type);

	_END();

	return ret;
}

int mtp_objectinfo_get_size(int mtp_device, int object_handle, int *size)
{
	int ret = MTP_ERROR_NONE;

	_BEGIN();

	/* precondition check start */

	CHECK_SUPPORTED();
	CHECK_INIT();
	CHECK_ACTIVATED();
	cond_expr_ret(mtp_device == 0, MTP_ERROR_INVALID_PARAMETER);

	/* precondition check end */

	ret = mtp_gdbus_objectinfo_get_property(mtp_device,
		object_handle, MTP_PROPERTY_SIZE, size);

	_END();

	return ret;
}

int mtp_objectinfo_get_data_created(int mtp_device,
	int object_handle, int *data_created)
{
	int ret = MTP_ERROR_NONE;

	_BEGIN();

	/* precondition check start */

	CHECK_SUPPORTED();
	CHECK_INIT();
	CHECK_ACTIVATED();
	cond_expr_ret(mtp_device == 0, MTP_ERROR_INVALID_PARAMETER);

	/* precondition check end */

	ret = mtp_gdbus_objectinfo_get_property(mtp_device,
		object_handle, MTP_PROPERTY_DATA_CREATED, data_created);

	_END();

	return ret;
}

int mtp_objectinfo_get_data_modified(int mtp_device,
	int object_handle, int *data_modified)
{
	int ret = MTP_ERROR_NONE;

	_BEGIN();

	/* precondition check start */

	CHECK_SUPPORTED();
	CHECK_INIT();
	CHECK_ACTIVATED();
	cond_expr_ret(mtp_device == 0, MTP_ERROR_INVALID_PARAMETER);

	/* precondition check end */

	ret = mtp_gdbus_objectinfo_get_property(mtp_device,
		object_handle, MTP_PROPERTY_DATA_MODIFIED, data_modified);

	_END();

	return ret;
}

int mtp_objectinfo_get_file_type(int mtp_device, int object_handle, mtp_filetype_e *file_type)
{
	int ret = MTP_ERROR_NONE;

	_BEGIN();

	/* precondition check start */

	CHECK_SUPPORTED();
	CHECK_INIT();
	CHECK_ACTIVATED();
	cond_expr_ret(mtp_device == 0, MTP_ERROR_INVALID_PARAMETER);

	/* precondition check end */

	ret = mtp_gdbus_objectinfo_get_property(mtp_device,
		object_handle, MTP_PROPERTY_FORMAT, (int*)file_type);

	_END();

	return ret;
}

int mtp_objectinfo_get_image_bit_depth(int mtp_device,
	int object_handle, int *depth)
{
	int ret = MTP_ERROR_NONE;

	_BEGIN();

	/* precondition check start */

	CHECK_SUPPORTED();
	CHECK_INIT();
	CHECK_ACTIVATED();
	cond_expr_ret(mtp_device == 0, MTP_ERROR_INVALID_PARAMETER);

	/* precondition check end */

	ret = mtp_gdbus_objectinfo_get_property(mtp_device,
		object_handle, MTP_PROPERTY_IMAGE_BIT_DEPTH, depth);

	_END();

	return ret;
}

int mtp_objectinfo_get_image_pix_width(int mtp_device,
	int object_handle, int *width)
{
	int ret = MTP_ERROR_NONE;

	_BEGIN();

	/* precondition check start */

	CHECK_SUPPORTED();
	CHECK_INIT();
	CHECK_ACTIVATED();
	cond_expr_ret(mtp_device == 0, MTP_ERROR_INVALID_PARAMETER);

	/* precondition check end */

	ret = mtp_gdbus_objectinfo_get_property(mtp_device,
		object_handle, MTP_PROPERTY_IMAGE_FIX_WIDTH, width);

	_END();

	return ret;
}

int mtp_objectinfo_get_image_pix_height(int mtp_device,
	int object_handle, int *height)
{
	int ret = MTP_ERROR_NONE;

	_BEGIN();

	/* precondition check start */

	CHECK_SUPPORTED();
	CHECK_INIT();
	CHECK_ACTIVATED();
	cond_expr_ret(mtp_device == 0, MTP_ERROR_INVALID_PARAMETER);

	/* precondition check end */

	ret = mtp_gdbus_objectinfo_get_property(mtp_device,
		object_handle, MTP_PROPERTY_IMAGE_FIX_HEIGHT, height);

	_END();

	return ret;
}

int mtp_objectinfo_get_thumbnail_size(int mtp_device,
	int object_handle, int *size)
{
	int ret = MTP_ERROR_NONE;

	_BEGIN();

	/* precondition check start */

	CHECK_SUPPORTED();
	CHECK_INIT();
	CHECK_ACTIVATED();
	cond_expr_ret(mtp_device == 0, MTP_ERROR_INVALID_PARAMETER);

	/* precondition check end */

	ret = mtp_gdbus_objectinfo_get_property(mtp_device,
		object_handle, MTP_PROPERTY_THUMBNAIL_SIZE, size);

	_END();

	return ret;
}

int mtp_objectinfo_get_thumbnail_file_type(int mtp_device,
	int object_handle, mtp_filetype_e *file_type)
{
	int ret = MTP_ERROR_NONE;

	_BEGIN();

	/* precondition check start */

	CHECK_SUPPORTED();
	CHECK_INIT();
	CHECK_ACTIVATED();
	cond_expr_ret(mtp_device == 0, MTP_ERROR_INVALID_PARAMETER);

	/* precondition check end */

	ret = mtp_gdbus_objectinfo_get_property(mtp_device,
		object_handle, MTP_PROPERTY_THUMBNAIL_FORMAT, (int*)file_type);

	_END();

	return ret;
}

int mtp_objectinfo_get_thumbnail_pix_height(int mtp_device,
	int object_handle, int *height)
{
	int ret = MTP_ERROR_NONE;

	_BEGIN();

	/* precondition check start */

	CHECK_SUPPORTED();
	CHECK_INIT();
	CHECK_ACTIVATED();
	cond_expr_ret(mtp_device == 0, MTP_ERROR_INVALID_PARAMETER);

	/* precondition check end */

	ret = mtp_gdbus_objectinfo_get_property(mtp_device,
		object_handle, MTP_PROPERTY_THUMBNAIL_HEIGHT, height);

	_END();

	return ret;
}

int mtp_objectinfo_get_thumbnail_pix_width(int mtp_device,
	int object_handle, int *width)
{
	int ret = MTP_ERROR_NONE;

	_BEGIN();

	/* precondition check start */

	CHECK_SUPPORTED();
	CHECK_INIT();
	CHECK_ACTIVATED();
	cond_expr_ret(mtp_device == 0, MTP_ERROR_INVALID_PARAMETER);

	/* precondition check end */

	ret = mtp_gdbus_objectinfo_get_property(mtp_device,
		object_handle, MTP_PROPERTY_THUMBNAIL_WIDTH, width);

	_END();

	return ret;
}

int mtp_objectinfo_get_file_name(int mtp_device,
	int object_handle, char **filename)
{
	int ret = MTP_ERROR_NONE;

	_BEGIN();

	/* precondition check start */

	CHECK_SUPPORTED();
	CHECK_INIT();
	CHECK_ACTIVATED();
	cond_expr_ret(mtp_device == 0, MTP_ERROR_INVALID_PARAMETER);

	/* precondition check end */

	ret = mtp_gdbus_objectinfo_get_property_string(mtp_device,
		object_handle, MTP_PROPERTY_FILENAME, filename);

	_END();

	return ret;
}

int mtp_objectinfo_get_keywords(int mtp_device,
	int object_handle, char **keywords)
{
	int ret = MTP_ERROR_NONE;

	_BEGIN();

	/* precondition check start */

	CHECK_SUPPORTED();
	CHECK_INIT();
	CHECK_ACTIVATED();
	cond_expr_ret(mtp_device == 0, MTP_ERROR_INVALID_PARAMETER);

	/* precondition check end */

	ret = mtp_gdbus_objectinfo_get_property_string(mtp_device,
		object_handle, MTP_PROPERTY_KEYWORDS, keywords);

	_END();

	return ret;
}

int mtp_objectinfo_get_object_info(int mtp_device,
	int object_handle, mtp_object_info **object_info)
{
	int ret = MTP_ERROR_NONE;

	_BEGIN();

	/* precondition check start */

	CHECK_SUPPORTED();
	CHECK_INIT();
	CHECK_ACTIVATED();
	cond_expr_ret(mtp_device == 0, MTP_ERROR_INVALID_PARAMETER);

	/* precondition check end */

	ret = mtp_db_get_object_info(mtp_device, object_handle, object_info);

	_END();

	return ret;
}

