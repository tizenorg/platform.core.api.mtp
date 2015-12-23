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

#include "mtp_gdbus_manager.h"
#include "mtp_gdbus_deviceinfo.h"
#include "mtp_gdbus_storageinfo.h"
#include "mtp_gdbus_objectinfo.h"

typedef struct _mtp_raw_device {
	int bus_location;
	int device_number;
	char *model_name;
} mtp_device;

int ref_count = 0;
bool __is_initialized = false;

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

#define CHECK_SUPPORTED() \
do { \
		{ \
			if (__is_mtp_supported() == false) { \
				return MTP_ERROR_NOT_SUPPORTED; \
		} \
	} \
} while (0);

#define CHECK_ACTIVATED() \
do { \
		{ \
			if (__is_mtp_activated() == false) { \
				return MTP_ERROR_NOT_ACTIVATED; \
		} \
	} \
} while (0);

typedef enum {
	MTP_PROPERTY_ASSOCIATION_DESC = 1,
	MTP_PROPERTY_ASSOCIATION_TYPE,
	MTP_PROPERTY_SIZE,
	MTP_PROPERTY_DATA_CREATED,
	MTP_PROPERTY_DATA_MODIFIED,
	MTP_PROPERTY_FORMAT,
	MTP_PROPERTY_IMAGE_FIX_DEPTH,
	MTP_PROPERTY_IMAGE_FIX_WIDTH,
	MTP_PROPERTY_IMAGE_FIX_HEIGHT,
	MTP_PROPERTY_PARENT_OBJECT_HANDLE,
	MTP_PROPERTY_STORAGE_ID,
	MTP_PROPERTY_THUMBNAIL_SIZE,
	MTP_PROPERTY_THUMBNAIL_FORMAT,
	MTP_PROPERTY_THUMBNAIL_WIDTH,
	MTP_PROPERTY_THUMBNAIL_HEIGHT,
	MTP_PROPERTY_FILENAME,
	MTP_PROPERTY_KEYWORDS
} mtp_property_e;

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

int mtp_get_device_list(mtp_device_list **dev_list)
{
	int ret = MTP_ERROR_NONE;

	_BEGIN();

	/* precondition check start */

	CHECK_SUPPORTED();
	CHECK_INIT();
	CHECK_ACTIVATED();

	/* precondition check end */

	ret = mtp_gdbus_manager_get_device_list(dev_list);

	_END();

	return ret;
}

int mtp_get_device_handle(int bus_location, int *device_handle)
{
	int ret = MTP_ERROR_NONE;

	_BEGIN();

	/* precondition check start */

	CHECK_SUPPORTED();
	CHECK_INIT();
	CHECK_ACTIVATED();
	cond_expr_ret(bus_location == 0, MTP_ERROR_INVALID_PARAMETER);

	/* precondition check end */

	ret = mtp_gdbus_manager_get_device_handle(bus_location, device_handle);

	TC_PRT("mtp_handle %d", *device_handle);

	_END();

	return ret;
}

int mtp_get_storage_ids(int device_handle, int **storage_ids, int *storage_num)
{
	int ret = MTP_ERROR_NONE;

	_BEGIN();

	/* precondition check start */

	CHECK_SUPPORTED();
	CHECK_INIT();
	CHECK_ACTIVATED();
	cond_expr_ret(device_handle == 0, MTP_ERROR_INVALID_PARAMETER);

	/* precondition check end */

	ret = mtp_gdbus_manager_get_storage_ids(device_handle, storage_ids, storage_num);

	TC_PRT("storage number %d", *storage_num);

	_END();

	return ret;
}

int mtp_get_object_handles(int device_handle, int storage_id, int format,
	int parent_object_handle, int **object_handles, int *object_num)
{
	int ret = MTP_ERROR_NONE;

	_BEGIN();

	/* precondition check start */

	CHECK_SUPPORTED();
	CHECK_INIT();
	CHECK_ACTIVATED();
	cond_expr_ret(device_handle == 0, MTP_ERROR_INVALID_PARAMETER);
	cond_expr_ret(storage_id == 0, MTP_ERROR_INVALID_PARAMETER);

	/* precondition check end */

	ret = mtp_gdbus_manager_get_object_handles(device_handle,
		storage_id, format, parent_object_handle, object_handles, object_num);

	_END();

	return ret;
}

int mtp_delete_object(int device_handle, int object_handle)
{
	int ret = MTP_ERROR_NONE;

	_BEGIN();

	/* precondition check start */

	CHECK_SUPPORTED();
	CHECK_INIT();
	CHECK_ACTIVATED();
	cond_expr_ret(device_handle == 0, MTP_ERROR_INVALID_PARAMETER);
	cond_expr_ret(object_handle == 0, MTP_ERROR_INVALID_PARAMETER);

	/* precondition check end */

	ret = mtp_gdbus_manager_delete_object(device_handle, object_handle);

	_END();

	return ret;
}

int mtp_get_object(int device_handle, int object_handle, char *dest_path)
{
	int ret = MTP_ERROR_NONE;

	_BEGIN();

	/* precondition check start */

	CHECK_SUPPORTED();
	CHECK_INIT();
	CHECK_ACTIVATED();
	cond_expr_ret(device_handle == 0, MTP_ERROR_INVALID_PARAMETER);
	cond_expr_ret(dest_path == NULL, MTP_ERROR_INVALID_PARAMETER);

	/* precondition check end */

	ret = mtp_gdbus_manager_get_object(device_handle, object_handle, dest_path);

	_END();

	return ret;
}

int mtp_get_thumbnail(int device_handle, int object_handle, char *dest_path)
{
	int ret = MTP_ERROR_NONE;

	_BEGIN();

	/* precondition check start */

	CHECK_SUPPORTED();
	CHECK_INIT();
	CHECK_ACTIVATED();
	cond_expr_ret(device_handle == 0, MTP_ERROR_INVALID_PARAMETER);
	cond_expr_ret(dest_path == NULL, MTP_ERROR_INVALID_PARAMETER);

	/* precondition check end */

	ret = mtp_gdbus_manager_get_thumbnail(device_handle, object_handle, dest_path);

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
int mtp_deviceinfo_get_manufacturername(int device_handle, char **manufacturername)
{
	int ret = MTP_ERROR_NONE;

	_BEGIN();

	/* precondition check start */

	CHECK_SUPPORTED();
	CHECK_INIT();
	CHECK_ACTIVATED();
	cond_expr_ret(device_handle == 0, MTP_ERROR_INVALID_PARAMETER);

	/* precondition check end */

	ret = mtp_gdbus_deviceinfo_get_manufacturername(device_handle, manufacturername);

	TC_PRT("manufacturername %s", *manufacturername);

	_END();

	return ret;
}

int mtp_deviceinfo_get_modelname(int device_handle, char **modelname)
{
	int ret = MTP_ERROR_NONE;

	_BEGIN();

	/* precondition check start */

	CHECK_SUPPORTED();
	CHECK_INIT();
	CHECK_ACTIVATED();
	cond_expr_ret(device_handle == 0, MTP_ERROR_INVALID_PARAMETER);

	/* precondition check end */

	ret = mtp_gdbus_deviceinfo_get_modelname(device_handle, modelname);

	TC_PRT("modelname %s", *modelname);

	_END();

	return ret;
}

int mtp_deviceinfo_get_serialnumber(int device_handle, char **serialnumber)
{
	int ret = MTP_ERROR_NONE;

	_BEGIN();

	/* precondition check start */

	CHECK_SUPPORTED();
	CHECK_INIT();
	CHECK_ACTIVATED();
	cond_expr_ret(device_handle == 0, MTP_ERROR_INVALID_PARAMETER);

	/* precondition check end */

	ret = mtp_gdbus_deviceinfo_get_serialnumber(device_handle, serialnumber);

	TC_PRT("serialnumber %s", *serialnumber);

	_END();

	return ret;
}

int mtp_deviceinfo_get_deviceversion(int device_handle, char **deviceversion)
{
	int ret = MTP_ERROR_NONE;

	_BEGIN();

	/* precondition check start */

	CHECK_SUPPORTED();
	CHECK_INIT();
	CHECK_ACTIVATED();
	cond_expr_ret(device_handle == 0, MTP_ERROR_INVALID_PARAMETER);

	/* precondition check end */

	ret = mtp_gdbus_deviceinfo_get_deviceversion(device_handle, deviceversion);

	TC_PRT("deviceversion %s", *deviceversion);

	_END();

	return ret;
}

/* Storage Info */
int mtp_storageinfo_get_description(int device_handle, int storage_id, char **description)
{
	int ret = MTP_ERROR_NONE;

	_BEGIN();

	/* precondition check start */

	CHECK_SUPPORTED();
	CHECK_INIT();
	CHECK_ACTIVATED();
	cond_expr_ret(device_handle == 0, MTP_ERROR_INVALID_PARAMETER);
	cond_expr_ret(storage_id == 0, MTP_ERROR_INVALID_PARAMETER);

	/* precondition check end */

	ret = mtp_gdbus_storageinfo_get_description(device_handle, storage_id, description);

	TC_PRT("description %s", *description);

	_END();

	return ret;
}

int mtp_storageinfo_get_freespace(int device_handle, int storage_id, unsigned long long *freespace)
{
	int ret = MTP_ERROR_NONE;

	_BEGIN();

	/* precondition check start */

	CHECK_SUPPORTED();
	CHECK_INIT();
	CHECK_ACTIVATED();
	cond_expr_ret(device_handle == 0, MTP_ERROR_INVALID_PARAMETER);
	cond_expr_ret(storage_id == 0, MTP_ERROR_INVALID_PARAMETER);

	/* precondition check end */

	ret = mtp_gdbus_storageinfo_get_freespace(device_handle, storage_id, (guint64 *)freespace);

	TC_PRT("freespace %llu", *freespace);

	_END();

	return ret;
}

int mtp_storageinfo_get_maxcapacity(int device_handle, int storage_id, unsigned long long *maxcapacity)
{
	int ret = MTP_ERROR_NONE;

	_BEGIN();

	/* precondition check start */

	CHECK_SUPPORTED();
	CHECK_INIT();
	CHECK_ACTIVATED();
	cond_expr_ret(device_handle == 0, MTP_ERROR_INVALID_PARAMETER);
	cond_expr_ret(storage_id == 0, MTP_ERROR_INVALID_PARAMETER);

	/* precondition check end */

	ret = mtp_gdbus_storageinfo_get_maxcapacity(device_handle, storage_id, (guint64 *)maxcapacity);

	TC_PRT("maxcapacity %llu", *maxcapacity);

	_END();

	return ret;
}

int mtp_storageinfo_get_storagetype(int device_handle, int storage_id, int *storagetype)
{
	int ret = MTP_ERROR_NONE;

	_BEGIN();

	/* precondition check start */

	CHECK_SUPPORTED();
	CHECK_INIT();
	CHECK_ACTIVATED();
	cond_expr_ret(device_handle == 0, MTP_ERROR_INVALID_PARAMETER);
	cond_expr_ret(storage_id == 0, MTP_ERROR_INVALID_PARAMETER);

	/* precondition check end */

	ret = mtp_gdbus_storageinfo_get_storagetype(device_handle, storage_id, storagetype);

	TC_PRT("storagetype %d", *storagetype);

	_END();

	return ret;
}

int mtp_storageinfo_get_volumeidentifier(int device_handle, int storage_id, char **volumeidentifier)
{
	int ret = MTP_ERROR_NONE;

	_BEGIN();

	/* precondition check start */

	CHECK_SUPPORTED();
	CHECK_INIT();
	CHECK_ACTIVATED();
	cond_expr_ret(device_handle == 0, MTP_ERROR_INVALID_PARAMETER);
	cond_expr_ret(storage_id == 0, MTP_ERROR_INVALID_PARAMETER);

	/* precondition check end */

	ret = mtp_gdbus_storageinfo_get_volumeidentifier(device_handle, storage_id, volumeidentifier);

	TC_PRT("volumeidentifier %s", *volumeidentifier);

	_END();

	return ret;
}

/* Object Info */
int mtp_objectinfo_get_parent_object_handle(int device_handle, int object_handle,
	int *parent_object_handle)
{
	int ret = MTP_ERROR_NONE;

	_BEGIN();

	/* precondition check start */

	CHECK_SUPPORTED();
	CHECK_INIT();
	CHECK_ACTIVATED();
	cond_expr_ret(device_handle == 0, MTP_ERROR_INVALID_PARAMETER);

	/* precondition check end */

	ret = mtp_gdbus_objectinfo_get_property(device_handle,
		object_handle, MTP_PROPERTY_PARENT_OBJECT_HANDLE, parent_object_handle);

	TC_PRT("parent object id %d", *parent_object_handle);

	_END();

	return ret;
}

int mtp_objectinfo_get_storage_id(int device_handle, int object_handle,
	int *storage_id)
{
	int ret = MTP_ERROR_NONE;

	_BEGIN();

	/* precondition check start */

	CHECK_SUPPORTED();
	CHECK_INIT();
	CHECK_ACTIVATED();
	cond_expr_ret(device_handle == 0, MTP_ERROR_INVALID_PARAMETER);

	/* precondition check end */

	ret = mtp_gdbus_objectinfo_get_property(device_handle,
		object_handle, MTP_PROPERTY_STORAGE_ID, storage_id);

	_END();

	return ret;
}

int mtp_objectinfo_get_association_desc(int device_handle,
	int object_handle, int *asso_desc)
{
	int ret = MTP_ERROR_NONE;

	_BEGIN();

	/* precondition check start */

	CHECK_SUPPORTED();
	CHECK_INIT();
	CHECK_ACTIVATED();
	cond_expr_ret(device_handle == 0, MTP_ERROR_INVALID_PARAMETER);

	/* precondition check end */

	ret = mtp_gdbus_objectinfo_get_property(device_handle,
		object_handle, MTP_PROPERTY_ASSOCIATION_DESC, asso_desc);

	_END();

	return ret;
}

int mtp_objectinfo_get_association_type(int device_handle,
	int object_handle, int *asso_type)
{
	int ret = MTP_ERROR_NONE;

	_BEGIN();

	/* precondition check start */

	CHECK_SUPPORTED();
	CHECK_INIT();
	CHECK_ACTIVATED();
	cond_expr_ret(device_handle == 0, MTP_ERROR_INVALID_PARAMETER);

	/* precondition check end */

	ret = mtp_gdbus_objectinfo_get_property(device_handle,
		object_handle, MTP_PROPERTY_ASSOCIATION_TYPE, asso_type);

	_END();

	return ret;
}

int mtp_objectinfo_get_size(int device_handle, int object_handle, int *size)
{
	int ret = MTP_ERROR_NONE;

	_BEGIN();

	/* precondition check start */

	CHECK_SUPPORTED();
	CHECK_INIT();
	CHECK_ACTIVATED();
	cond_expr_ret(device_handle == 0, MTP_ERROR_INVALID_PARAMETER);

	/* precondition check end */

	ret = mtp_gdbus_objectinfo_get_property(device_handle,
		object_handle, MTP_PROPERTY_SIZE, size);

	_END();

	return ret;
}

int mtp_objectinfo_get_data_created(int device_handle,
	int object_handle, int *data_created)
{
	int ret = MTP_ERROR_NONE;

	_BEGIN();

	/* precondition check start */

	CHECK_SUPPORTED();
	CHECK_INIT();
	CHECK_ACTIVATED();
	cond_expr_ret(device_handle == 0, MTP_ERROR_INVALID_PARAMETER);

	/* precondition check end */

	ret = mtp_gdbus_objectinfo_get_property(device_handle,
		object_handle, MTP_PROPERTY_DATA_CREATED, data_created);

	_END();

	return ret;
}

int mtp_objectinfo_get_data_modified(int device_handle,
	int object_handle, int *data_modified)
{
	int ret = MTP_ERROR_NONE;

	_BEGIN();

	/* precondition check start */

	CHECK_SUPPORTED();
	CHECK_INIT();
	CHECK_ACTIVATED();
	cond_expr_ret(device_handle == 0, MTP_ERROR_INVALID_PARAMETER);

	/* precondition check end */

	ret = mtp_gdbus_objectinfo_get_property(device_handle,
		object_handle, MTP_PROPERTY_DATA_MODIFIED, data_modified);

	_END();

	return ret;
}

int mtp_objectinfo_get_format(int device_handle, int object_handle, int *format)
{
	int ret = MTP_ERROR_NONE;

	_BEGIN();

	/* precondition check start */

	CHECK_SUPPORTED();
	CHECK_INIT();
	CHECK_ACTIVATED();
	cond_expr_ret(device_handle == 0, MTP_ERROR_INVALID_PARAMETER);

	/* precondition check end */

	ret = mtp_gdbus_objectinfo_get_property(device_handle,
		object_handle, MTP_PROPERTY_FORMAT, format);

	_END();

	return ret;
}

int mtp_objectinfo_get_image_pix_depth(int device_handle,
	int object_handle, int *depth)
{
	int ret = MTP_ERROR_NONE;

	_BEGIN();

	/* precondition check start */

	CHECK_SUPPORTED();
	CHECK_INIT();
	CHECK_ACTIVATED();
	cond_expr_ret(device_handle == 0, MTP_ERROR_INVALID_PARAMETER);

	/* precondition check end */

	ret = mtp_gdbus_objectinfo_get_property(device_handle,
		object_handle, MTP_PROPERTY_IMAGE_FIX_DEPTH, depth);

	_END();

	return ret;
}

int mtp_objectinfo_get_image_pix_width(int device_handle,
	int object_handle, int *width)
{
	int ret = MTP_ERROR_NONE;

	_BEGIN();

	/* precondition check start */

	CHECK_SUPPORTED();
	CHECK_INIT();
	CHECK_ACTIVATED();
	cond_expr_ret(device_handle == 0, MTP_ERROR_INVALID_PARAMETER);

	/* precondition check end */

	ret = mtp_gdbus_objectinfo_get_property(device_handle,
		object_handle, MTP_PROPERTY_IMAGE_FIX_WIDTH, width);

	_END();

	return ret;
}

int mtp_objectinfo_get_image_pix_height(int device_handle,
	int object_handle, int *height)
{
	int ret = MTP_ERROR_NONE;

	_BEGIN();

	/* precondition check start */

	CHECK_SUPPORTED();
	CHECK_INIT();
	CHECK_ACTIVATED();
	cond_expr_ret(device_handle == 0, MTP_ERROR_INVALID_PARAMETER);

	/* precondition check end */

	ret = mtp_gdbus_objectinfo_get_property(device_handle,
		object_handle, MTP_PROPERTY_IMAGE_FIX_HEIGHT, height);

	_END();

	return ret;
}

int mtp_objectinfo_get_thumbnail_size(int device_handle,
	int object_handle, int *size)
{
	int ret = MTP_ERROR_NONE;

	_BEGIN();

	/* precondition check start */

	CHECK_SUPPORTED();
	CHECK_INIT();
	CHECK_ACTIVATED();
	cond_expr_ret(device_handle == 0, MTP_ERROR_INVALID_PARAMETER);

	/* precondition check end */

	ret = mtp_gdbus_objectinfo_get_property(device_handle,
		object_handle, MTP_PROPERTY_THUMBNAIL_SIZE, size);

	_END();

	return ret;
}

int mtp_objectinfo_get_thumbnail_format(int device_handle,
	int object_handle, int *format)
{
	int ret = MTP_ERROR_NONE;

	_BEGIN();

	/* precondition check start */

	CHECK_SUPPORTED();
	CHECK_INIT();
	CHECK_ACTIVATED();
	cond_expr_ret(device_handle == 0, MTP_ERROR_INVALID_PARAMETER);

	/* precondition check end */

	ret = mtp_gdbus_objectinfo_get_property(device_handle,
		object_handle, MTP_PROPERTY_THUMBNAIL_FORMAT, format);

	_END();

	return ret;
}

int mtp_objectinfo_get_thumbnail_pix_height(int device_handle,
	int object_handle, int *height)
{
	int ret = MTP_ERROR_NONE;

	_BEGIN();

	/* precondition check start */

	CHECK_SUPPORTED();
	CHECK_INIT();
	CHECK_ACTIVATED();
	cond_expr_ret(device_handle == 0, MTP_ERROR_INVALID_PARAMETER);

	/* precondition check end */

	ret = mtp_gdbus_objectinfo_get_property(device_handle,
		object_handle, MTP_PROPERTY_THUMBNAIL_HEIGHT, height);

	_END();

	return ret;
}

int mtp_objectinfo_get_thumbnail_pix_width(int device_handle,
	int object_handle, int *width)
{
	int ret = MTP_ERROR_NONE;

	_BEGIN();

	/* precondition check start */

	CHECK_SUPPORTED();
	CHECK_INIT();
	CHECK_ACTIVATED();
	cond_expr_ret(device_handle == 0, MTP_ERROR_INVALID_PARAMETER);

	/* precondition check end */

	ret = mtp_gdbus_objectinfo_get_property(device_handle,
		object_handle, MTP_PROPERTY_THUMBNAIL_WIDTH, width);

	_END();

	return ret;
}

int mtp_objectinfo_get_filename(int device_handle,
	int object_handle, char **filename)
{
	int ret = MTP_ERROR_NONE;

	_BEGIN();

	/* precondition check start */

	CHECK_SUPPORTED();
	CHECK_INIT();
	CHECK_ACTIVATED();
	cond_expr_ret(device_handle == 0, MTP_ERROR_INVALID_PARAMETER);

	/* precondition check end */

	ret = mtp_gdbus_objectinfo_get_property_string(device_handle,
		object_handle, MTP_PROPERTY_FILENAME, filename);

	_END();

	return ret;
}

int mtp_objectinfo_get_keywords(int device_handle,
	int object_handle, char **keywords)
{
	int ret = MTP_ERROR_NONE;

	_BEGIN();

	/* precondition check start */

	CHECK_SUPPORTED();
	CHECK_INIT();
	CHECK_ACTIVATED();
	cond_expr_ret(device_handle == 0, MTP_ERROR_INVALID_PARAMETER);

	/* precondition check end */

	ret = mtp_gdbus_objectinfo_get_property_string(device_handle,
		object_handle, MTP_PROPERTY_KEYWORDS, keywords);

	_END();

	return ret;
}

int mtp_objectinfo_get_object_info(int device_handle,
	int object_handle, mtp_object_info **object_info)
{
	int ret = MTP_ERROR_NONE;

	_BEGIN();

	/* precondition check start */

	CHECK_SUPPORTED();
	CHECK_INIT();
	CHECK_ACTIVATED();
	cond_expr_ret(device_handle == 0, MTP_ERROR_INVALID_PARAMETER);

	/* precondition check end */

	ret = mtp_db_get_object_info(device_handle, object_handle, object_info);

	_END();

	return ret;
}

