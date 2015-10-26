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

#ifndef __MTP_H__
#define __MTP_H__

#include <tizen.h>

#ifdef __cplusplus
extern "C" {
#endif

#ifndef MTP_API
#define MTP_API
#endif

/**
 * @file mtp.h
 * @brief This file contains the MTP API
 */
#define MTP_ERROR_CLASS TIZEN_ERROR_NETWORK_CLASS /* Need define mtp error class */

/**
 * @brief Structure for mtp device
 * @since_tizen 3.0
 * @ingroup CAPI_NETWORK_MTP_MANAGER_MODULE
 */
typedef struct _mtp_device {
	int bus_location;
	char *model_name;
} mtp_device;

/**
 * @brief Structure for mtp device list
 * @since_tizen 3.0
 * @ingroup CAPI_NETWORK_MTP_MANAGER_MODULE
 */
typedef struct _mtp_device_list {
	mtp_device *devices;
	int device_num;
} mtp_device_list;

/**
 * @brief Error codes reported by the MTP API.
 * @since_tizen 3.0
 * @ingroup CAPI_NETWORK_MTP_MANAGER_MODULE
 */
typedef enum {
	MTP_ERROR_NONE = TIZEN_ERROR_NONE, /**< Successful */
	MTP_ERROR_GENERAL = MTP_ERROR_CLASS | 0x01, /**< A general error occurred */
	MTP_ERROR_IO_ERROR = TIZEN_ERROR_IO_ERROR, /**< I/O error */
	MTP_ERROR_INVALID_PARAMETER = TIZEN_ERROR_INVALID_PARAMETER, /**< Invalid parameter */
	MTP_ERROR_NO_DEVICE = MTP_ERROR_CLASS | 0x02, /**< MTP have not any device */
	MTP_ERROR_ALLOC_FAIL = MTP_ERROR_CLASS | 0x03, /**< Memory Allocation failed */
	MTP_ERROR_PLUGIN = MTP_ERROR_CLASS | 0x04, /**< Plugin failed */
	MTP_ERROR_DB = MTP_ERROR_CLASS | 0x05, /**< Plugin failed */
	MTP_ERROR_PERMISSION_DENIED = TIZEN_ERROR_PERMISSION_DENIED, /**< Permission denied */
	MTP_ERROR_NOT_INITIALIZED = MTP_ERROR_CLASS | 0x06, /**< MTP is not supported */
	MTP_ERROR_NOT_ACTIVATED = MTP_ERROR_CLASS | 0x07, /**< MTP is not activated */
	MTP_ERROR_NOT_SUPPORTED = TIZEN_ERROR_NOT_SUPPORTED, /**< MTP is not supported */
} mtp_error_e;

/**
 * @brief Enumerations for MTP file type
 * @since_tizen 3.0
 * @ingroup CAPI_NETWORK_MTP_MANAGER_MODULE
 */
typedef enum {
	MTP_FILETYPE_FOLDER, /**< FOLDER file type */
	MTP_FILETYPE_WAV, /**< WAV file type */
	MTP_FILETYPE_MP3, /**< MP3 file type */
	MTP_FILETYPE_WMA, /**< WMA file type */
	MTP_FILETYPE_OGG, /**< OGG file type */
	MTP_FILETYPE_AUDIBLE, /**< AUDIBLE file type */
	MTP_FILETYPE_MP4, /**< MP4 file type */
	MTP_FILETYPE_UNDEF_AUDIO, /**< UNDEF_AUDIO file type */
	MTP_FILETYPE_WMV, /**< WMV file type */
	MTP_FILETYPE_AVI, /**< AVI file type */
	MTP_FILETYPE_MPEG, /**< MPEG file type */
	MTP_FILETYPE_ASF, /**< ASF file type */
	MTP_FILETYPE_QT, /**< QT file type */
	MTP_FILETYPE_UNDEF_VIDEO, /**< UNDEF_VIDEO file type */
	MTP_FILETYPE_JPEG, /**< JPEG file type */
	MTP_FILETYPE_JFIF, /**< JFIF file type */
	MTP_FILETYPE_TIFF, /**< TIFF file type */
	MTP_FILETYPE_BMP, /**< BMP file type */
	MTP_FILETYPE_GIF, /**< GIF file type */
	MTP_FILETYPE_PICT, /**< PICT file type */
	MTP_FILETYPE_PNG, /**< PNG file type */
	MTP_FILETYPE_VCALENDAR1, /**< VCALENDAR1 file type */
	MTP_FILETYPE_VCALENDAR2, /**< VCALENDAR2 file type */
	MTP_FILETYPE_VCARD2, /**< VCARD2 file type */
	MTP_FILETYPE_VCARD3, /**< VCARD3 file type */
	MTP_FILETYPE_WINDOWSIMAGEFORMAT, /**< WINDOWSIMAGEFORMAT file type */
	MTP_FILETYPE_WINEXEC, /**< WINEXEC file type */
	MTP_FILETYPE_TEXT, /**< TEXT file type */
	MTP_FILETYPE_HTML, /**< HTML file type */
	MTP_FILETYPE_FIRMWARE, /**< FIRMWARE file type */
	MTP_FILETYPE_AAC, /**< AAC file type */
	MTP_FILETYPE_MEDIACARD, /**< MEDIACARD file type */
	MTP_FILETYPE_FLAC, /**< FLAC file type */
	MTP_FILETYPE_MP2, /**< MP2 file type */
	MTP_FILETYPE_M4A, /**< M4A file type */
	MTP_FILETYPE_DOC, /**< DOC file type */
	MTP_FILETYPE_XML, /**< XML file type */
	MTP_FILETYPE_XLS, /**< XLS file type */
	MTP_FILETYPE_PPT, /**< PPT file type */
	MTP_FILETYPE_MHT, /**< MHT file type */
	MTP_FILETYPE_JP2, /**< JP2 file type */
	MTP_FILETYPE_JPX, /**< JPX file type */
	MTP_FILETYPE_ALBUM, /**< ALBUM file type */
	MTP_FILETYPE_PLAYLIST, /**< PLAYLIST file type */
	MTP_FILETYPE_UNKNOWN, /**< Unknown file type */

	MTP_FILETYPE_ALL, /**< helper enum value for certain function */
	MTP_FILETYPE_ALL_IMAGE /**< helper enum value for certain function */
} mtp_filetype_e;

/**
 * @brief Enumerations for MTP event type
 * @since_tizen 3.0
 * @ingroup CAPI_NETWORK_MTP_MANAGER_MODULE
 */
typedef enum {
	MTP_EVENT_UNKNOWN, /**< Unknown event type */
	MTP_EVENT_STORAGE_ADDED, /**< Storage is added */
	MTP_EVENT_STORAGE_REMOVED, /**< Storage is removed */
	MTP_EVENT_OBJECT_ADDED, /**< Object is added */
	MTP_EVENT_OBJECT_REMOVED, /**< Object is removed */
	MTP_EVENT_DEVICE_ADDED, /**< Device is added */
	MTP_EVENT_DEVICE_REMOVED /**< Device is removed */
} mtp_event_e;

/**
 * @brief Called after mtp_set_mtp_event_cb() has completed.
 * @since_tizen 3.0
 * @ingroup CAPI_NETWORK_MTP_MANAGER_MODULE
 *
 * @param [in] event The event
 * @param [in] arg The argument
 * @param [in] user_data The user data passed from the callback registration function
 *
 * @see mtp_set_mtp_event_cb()
 * @see mtp_unset_mtp_event_cb()
 */
typedef void (* mtp_event_cb)(mtp_event_e event, int arg, void *user_data);

/**
 * @brief Initializes for using MTP.
 * @since_tizen 3.0
 * @ingroup CAPI_NETWORK_MTP_MANAGER_MODULE
 * @remarks This function must be called before proceeding any other mtp functions\n
 *
 * @return 0 on success, otherwise a negative error value.
 * @retval #MTP_ERROR_NONE Successful
 *
 * @see mtp_deinitialize()
 */
MTP_API int mtp_initialize(void);

/**
 * @brief Get device list.
 * @since_tizen 3.0
 * @ingroup CAPI_NETWORK_MTP_MANAGER_MODULE
 *
 * @return 0 on success, otherwise a negative error value.
 * @retval #MTP_ERROR_NONE Successful
 *
 * @param [out] dev_list All current device list
 */
MTP_API int mtp_get_device_list(mtp_device_list **dev_list);

/**
 * @brief Get device handler from bus location
 * @since_tizen 3.0
 * @ingroup CAPI_NETWORK_MTP_MANAGER_MODULE
 *
 * @return 0 on success, otherwise a negative error value.
 * @retval #MTP_ERROR_NONE Successful
 *
 * @param [in] bus_location The bus location
 * @param [out] device_handle The device handle
 *
 * @see mtp_initialize()
 */
MTP_API int mtp_get_device_handle(int bus_location, int* device_handle);

/**
 * @brief Get storage ids from device
 * @since_tizen 3.0
 * @ingroup CAPI_NETWORK_MTP_MANAGER_MODULE
 *
 * @return 0 on success, otherwise a negative error value.
 * @retval #MTP_ERROR_NONE Successful
 *
 * @param [in] device_handle The device handle
 * @param [out] storage_id Current storage id list
 * @param [out] storage_num Length of storage id list
 *
 * @see mtp_get_device_handle()
 */
MTP_API int mtp_get_storage_ids(int device_handle, int **storage_id, int* storage_num);

/**
 * @brief Get object handles from device
 * @since_tizen 3.0
 * @ingroup CAPI_NETWORK_MTP_MANAGER_MODULE
 *
 * @return 0 on success, otherwise a negative error value.
 * @retval #MTP_ERROR_NONE Successful
 *
 * @param [in] device_handle The device handle
 * @param [in] storage_id The storage id
 * @param [in] format The file type what you want
 * @param [in] parent_object_handle The parent object handle
 * @param [out] object_handles The object handle list
 * @param [out] object_num Length of object handle list
 *
 * @see mtp_get_device_handle()
 * @see mtp_get_storage_ids()
 */
MTP_API int mtp_get_object_handles(int device_handle, int storage_id, int format,
	int parent_object_handle, int **object_handles, int* object_num);

/**
 * @brief Delete object from device
 * @since_tizen 3.0
 * @ingroup CAPI_NETWORK_MTP_MANAGER_MODULE
 *
 * @return 0 on success, otherwise a negative error value.
 * @retval #MTP_ERROR_NONE Successful
 *
 * @param [in] device_handle The device handle
 * @param [in] object_handle The object handle
 *
 * @see mtp_get_device_handle()
 * @see mtp_get_object_handles()
 */
MTP_API int mtp_delete_object(int device_handle, int object_handle);

/**
 * @brief Get object from object handle
 * @since_tizen 3.0
 * @ingroup CAPI_NETWORK_MTP_MANAGER_MODULE
 *
 * @return 0 on success, otherwise a negative error value.
 * @retval #MTP_ERROR_NONE Successful
 *
 * @param [in] device_handle The device handle
 * @param [in] object_handle The object handle
 * @param [in] dest_path The dest path
 *
 * @see mtp_get_device_handle()
 * @see mtp_get_object_handles()
 */
MTP_API int mtp_get_object(int device_handle, int object_handle, char *dest_path);

/**
 * @brief Get thumbnail from object handle
 * @since_tizen 3.0
 * @ingroup CAPI_NETWORK_MTP_MANAGER_MODULE
 *
 * @return 0 on success, otherwise a negative error value.
 * @retval #MTP_ERROR_NONE Successful
 *
 * @param [in] device_handle The device handle
 * @param [in] object_handle The object handle
 * @param [in] dest_path The dest path
 *
 * @see mtp_get_device_handle()
 * @see mtp_get_object_handles()
 */
MTP_API int mtp_get_thumbnail(int device_handle, int object_handle, char *dest_path);

/**
 * @brief Registers a callback function for receiving MTP event.
 * @since_tizen 3.0
 * @ingroup CAPI_NETWORK_MTP_MANAGER_MODULE
 *
 * @detail If device state is changed, DEVICE_ADD or DEVICE_REMOVE event is occur. \n
 *   If storage state is changed, STORAGE_ADD or STORAGE_REMOVE event is occur. \n
 *   If object state is changed, OBJECT_ADD or OBJECT_REMOVE event is occur.
 *
 * @return 0 on success, otherwise a negative error value.
 * @retval #MTP_ERROR_NONE Successful
 *
 * @param [in] callback The callback
 * @param [in] user_data The user data
 *
 * @see mtp_unset_mtp_event_cb()
 */
MTP_API int mtp_set_mtp_event_cb(mtp_event_cb callback, void *user_data);

/**
 * @brief Unregisters the callback function.
 * @since_tizen 3.0
 * @ingroup CAPI_NETWORK_MTP_MANAGER_MODULE
 *
 * @return 0 on success, otherwise a negative error value.
 * @retval #MTP_ERROR_NONE Successful
 *
 * @see mtp_set_mtp_event_cb()
 */
MTP_API int mtp_unset_mtp_event_cb(void);

/**
 * @brief Deinitializes MTP operation.
 * @since_tizen 3.0
 * @ingroup CAPI_NETWORK_MTP_MANAGER_MODULE
 *
 * @return 0 on success, otherwise a negative error value.
 * @retval #MTP_ERROR_NONE Successful
 *
 * @see mtp_initialize()
 */
MTP_API int mtp_deinitialize(void);

/**
 * @brief Get the manufacturer name of the device information.
 * @since_tizen 3.0
 * @ingroup CAPI_NETWORK_MTP_DEVICEINFO_MODULE
 *
 * @return 0 on success, otherwise a negative error value.
 * @retval #MTP_ERROR_NONE Successful
 *
 * @param [in] device_handle The device handle
 * @param [out] manufacturername The manufacturername of Device information
 *
 * @see mtp_get_device_handle()
 */
MTP_API int mtp_deviceinfo_get_manufacturername(int device_handle, char **manufacturername);

/**
 * @brief Get the model name of the device information.
 * @since_tizen 3.0
 * @ingroup CAPI_NETWORK_MTP_DEVICEINFO_MODULE
 *
 * @return 0 on success, otherwise a negative error value.
 * @retval #MTP_ERROR_NONE Successful
 *
 * @param [in] device_handle The device handle
 * @param [out] modelname The modelname of Device information
 *
 * @see mtp_get_device_handle()
 */
MTP_API int mtp_deviceinfo_get_modelname(int device_handle, char **modelname);

/**
 * @brief Get the serial number of the device information.
 * @since_tizen 3.0
 * @ingroup CAPI_NETWORK_MTP_DEVICEINFO_MODULE
 *
 * @return 0 on success, otherwise a negative error value.
 * @retval #MTP_ERROR_NONE Successful
 *
 * @param [in] device_handle The device handle
 * @param [out] serialnumber The serialnumber of Device information
 *
 * @see mtp_get_device_handle()
 */
MTP_API int mtp_deviceinfo_get_serialnumber(int device_handle, char **serialnumber);

/**
 * @brief Get the device version of the device information.
 * @since_tizen 3.0
 * @ingroup CAPI_NETWORK_MTP_DEVICEINFO_MODULE
 *
 * @return 0 on success, otherwise a negative error value.
 * @retval #MTP_ERROR_NONE Successful
 *
 * @param [in] device_handle The device handle
 * @param [out] serialnumber The deviceversion of Device information
 *
 * @see mtp_get_device_handle()
 */
MTP_API int mtp_deviceinfo_get_deviceversion(int device_handle, char **deviceversion);

/**
 * @brief Get the description of the storage information.
 * @since_tizen 3.0
 * @ingroup CAPI_NETWORK_MTP_STORAGEINFO_MODULE
 *
 * @return 0 on success, otherwise a negative error value.
 * @retval #MTP_ERROR_NONE Successful
 *
 * @param [in] device_handle The device handle
 * @param [in] storage_id The storage id
 * @param [out] description The description of Storage information
 *
 * @see mtp_get_storage_ids()
 */
MTP_API int mtp_storageinfo_get_description(int device_handle, int storage_id, char **description);

/**
 * @brief Get the freespace of the storage information.
 * @since_tizen 3.0
 * @ingroup CAPI_NETWORK_MTP_STORAGEINFO_MODULE
 *
 * @return 0 on success, otherwise a negative error value.
 * @retval #MTP_ERROR_NONE Successful
 *
 * @param [in] device_handle The device handle
 * @param [in] storage_id The storage id
 * @param [out] freespace The freespace of Storage information
 *
 * @see mtp_get_storage_ids()
 */
MTP_API int mtp_storageinfo_get_freespace(int device_handle, int storage_id, guint64 *freespace);

/**
 * @brief Get the max capacity of the storage information.
 * @since_tizen 3.0
 * @ingroup CAPI_NETWORK_MTP_STORAGEINFO_MODULE
 *
 * @return 0 on success, otherwise a negative error value.
 * @retval #MTP_ERROR_NONE Successful
 *
 * @param [in] device_handle The device handle
 * @param [in] storage_id The storage id
 * @param [out] maxcapacity The maxcapacity of Storage information
 *
 * @see mtp_get_storage_ids()
 */
MTP_API int mtp_storageinfo_get_maxcapacity(int device_handle, int storage_id, guint64 *maxcapacity);

/**
 * @brief Get the storage type of the storage information.
 * @since_tizen 3.0
 * @ingroup CAPI_NETWORK_MTP_STORAGEINFO_MODULE
 *
 * @return 0 on success, otherwise a negative error value.
 * @retval #MTP_ERROR_NONE Successful
 *
 * @param [in] device_handle The device handle
 * @param [in] storage_id The storage id
 * @param [out] storagetype The storagetype of Storage information
 *
 * @see mtp_get_storage_ids()
 */
MTP_API int mtp_storageinfo_get_storagetype(int device_handle, int storage_id, int *storagetype);

/**
 * @brief Get the volumeidentifier of the storage information.
 * @since_tizen 3.0
 * @ingroup CAPI_NETWORK_MTP_STORAGEINFO_MODULE
 *
 * @return 0 on success, otherwise a negative error value.
 * @retval #MTP_ERROR_NONE Successful
 *
 * @param [in] device_handle The device handle
 * @param [in] storage_id The storage id
 * @param [out] volumeidentifier The volumeidentifier of Storage information
 *
 * @see mtp_get_object_handles()
 */
MTP_API int mtp_storageinfo_get_volumeidentifier(int device_handle, int storage_id, char **volumeidentifier);

/**
 * @brief Get the filename of the object information.
 * @since_tizen 3.0
 * @ingroup CAPI_NETWORK_MTP_OBJECTINFO_MODULE
 *
 * @return 0 on success, otherwise a negative error value.
 * @retval #MTP_ERROR_NONE Successful
 *
 * @param [in] device_handle The device handle
 * @param [in] object_handle The object handle
 * @param [out] filename The filename of Object information
 *
 * @see mtp_get_object_handles()
 */
MTP_API int mtp_objectinfo_get_filename(int device_handle, int object_handle, char **filename);

/**
 * @brief Get the keywords of the object information.
 * @since_tizen 3.0
 * @ingroup CAPI_NETWORK_MTP_OBJECTINFO_MODULE
 *
 * @return 0 on success, otherwise a negative error value.
 * @retval #MTP_ERROR_NONE Successful
 *
 * @param [in] device_handle The device handle
 * @param [in] object_handle The object handle
 * @param [out] keywords The keywords of Object information
 *
 * @see mtp_get_object_handles()
 */
MTP_API int mtp_objectinfo_get_keywords(int device_handle, int object_handle, char **keywords);

/**
 * @brief Get the association desc of the object information.
 * @since_tizen 3.0
 * @ingroup CAPI_NETWORK_MTP_OBJECTINFO_MODULE
 *
 * @return 0 on success, otherwise a negative error value.
 * @retval #MTP_ERROR_NONE Successful
 *
 * @param [in] device_handle The device handle
 * @param [in] object_handle The object handle
 * @param [out] asso_desc The association description of Object information
 *
 * @see mtp_get_object_handles()
 */
MTP_API int mtp_objectinfo_get_association_desc(int device_handle, int object_handle, int *asso_desc);

/**
 * @brief Get the association type of the object information.
 * @since_tizen 3.0
 * @ingroup CAPI_NETWORK_MTP_OBJECTINFO_MODULE
 *
 * @return 0 on success, otherwise a negative error value.
 * @retval #MTP_ERROR_NONE Successful
 *
 * @param [in] device_handle The device handle
 * @param [in] object_handle The object handle
 * @param [out] asso_type The association type of Object information
 *
 * @see mtp_get_object_handles()
 */
MTP_API int mtp_objectinfo_get_association_type(int device_handle, int object_handle, int *asso_type);

/**
 * @brief Get the size of the object information.
 * @since_tizen 3.0
 * @ingroup CAPI_NETWORK_MTP_OBJECTINFO_MODULE
 *
 * @return 0 on success, otherwise a negative error value.
 * @retval #MTP_ERROR_NONE Successful
 *
 * @param [in] device_handle The device handle
 * @param [in] object_handle The object handle
 * @param [out] size The size of Object information
 *
 * @see mtp_get_object_handles()
 */
MTP_API int mtp_objectinfo_get_size(int device_handle, int object_handle, int *size);

/**
 * @brief Get the parent object handle of the object information.
 * @since_tizen 3.0
 * @ingroup CAPI_NETWORK_MTP_OBJECTINFO_MODULE
 *
 * @return 0 on success, otherwise a negative error value.
 * @retval #MTP_ERROR_NONE Successful
 *
 * @param [in] device_handle The device handle
 * @param [in] object_handle The object handle
 * @param [out] parent_object_handle The parent of Object information
 *
 * @see mtp_get_object_handles()
 */
MTP_API int mtp_objectinfo_get_parent_object_handle(int device_handle, int object_handle, int *parent_object_handle);

/**
 * @brief Get the storage id of the object information.
 * @since_tizen 3.0
 * @ingroup CAPI_NETWORK_MTP_OBJECTINFO_MODULE
 *
 * @return 0 on success, otherwise a negative error value.
 * @retval #MTP_ERROR_NONE Successful
 *
 * @param [in] device_handle The device handle
 * @param [in] object_handle The object handle
 * @param [out] storage_id The storage id of Object information
 *
 * @see mtp_get_object_handles()
 */
MTP_API int mtp_objectinfo_get_storage_id(int device_handle, int object_handle, int *storage_id);

/**
 * @brief Get the data created time of the object information.
 * @since_tizen 3.0
 * @ingroup CAPI_NETWORK_MTP_OBJECTINFO_MODULE
 *
 * @return 0 on success, otherwise a negative error value.
 * @retval #MTP_ERROR_NONE Successful
 *
 * @param [in] device_handle The device handle
 * @param [in] object_handle The object handle
 * @param [out] data_created The data created time of Object information
 *
 * @see mtp_get_object_handles()
 */
MTP_API int mtp_objectinfo_get_data_created(int device_handle, int object_handle, int *data_created);

/**
 * @brief Get the data modified time of the object information.
 * @since_tizen 3.0
 * @ingroup CAPI_NETWORK_MTP_OBJECTINFO_MODULE
 *
 * @return 0 on success, otherwise a negative error value.
 * @retval #MTP_ERROR_NONE Successful
 *
 * @param [in] device_handle The device handle
 * @param [in] object_handle The object handle
 * @param [out] data_modified The data modified time of Object information
 *
 * @see mtp_get_object_handles()
 */
MTP_API int mtp_objectinfo_get_data_modified(int device_handle, int object_handle, int *data_modified);

/**
 * @brief Get the format of the object information.
 * @since_tizen 3.0
 * @ingroup CAPI_NETWORK_MTP_OBJECTINFO_MODULE
 *
 * @return 0 on success, otherwise a negative error value.
 * @retval #MTP_ERROR_NONE Successful
 *
 * @param [in] device_handle The device handle
 * @param [in] object_handle The object handle
 * @param [out] format The image format of Object information
 *
 * @see mtp_get_object_handles()
 */
MTP_API int mtp_objectinfo_get_format(int device_handle, int object_handle, int *format);

/**
 * @brief Get the image pix depth of the object information.
 * @since_tizen 3.0
 * @ingroup CAPI_NETWORK_MTP_OBJECTINFO_MODULE
 *
 * @return 0 on success, otherwise a negative error value.
 * @retval #MTP_ERROR_NONE Successful
 *
 * @param [in] device_handle The device handle
 * @param [in] object_handle The object handle
 * @param [out] depth The image pixel depth of Object information
 *
 * @see mtp_get_object_handles()
 */
MTP_API int mtp_objectinfo_get_image_pix_depth(int device_handle, int object_handle, int *depth);

/**
 * @brief Get the image pix width of the object information.
 * @since_tizen 3.0
 * @ingroup CAPI_NETWORK_MTP_OBJECTINFO_MODULE
 *
 * @return 0 on success, otherwise a negative error value.
 * @retval #MTP_ERROR_NONE Successful
 *
 * @param [in] device_handle The device handle
 * @param [in] object_handle The object handle
 * @param [out] width The image pixel width of Object information
 *
 * @see mtp_get_object_handles()
 */
MTP_API int mtp_objectinfo_get_image_pix_width(int device_handle, int object_handle, int *width);

/**
 * @brief Get the image pix height of the object information.
 * @since_tizen 3.0
 * @ingroup CAPI_NETWORK_MTP_OBJECTINFO_MODULE
 *
 * @return 0 on success, otherwise a negative error value.
 * @retval #MTP_ERROR_NONE Successful
 *
 * @param [in] device_handle The device handle
 * @param [in] object_handle The object handle
 * @param [out] height The image pixel height of Object information
 *
 * @see mtp_get_object_handles()
 */
MTP_API int mtp_objectinfo_get_image_pix_height(int device_handle, int object_handle, int *height);

/**
 * @brief Get the thumbnail size of the object information.
 * @since_tizen 3.0
 * @ingroup CAPI_NETWORK_MTP_OBJECTINFO_MODULE
 *
 * @return 0 on success, otherwise a negative error value.
 * @retval #MTP_ERROR_NONE Successful
 *
 * @param [in] device_handle The device handle
 * @param [in] object_handle The object handle
 * @param [out] size The thumbnail size of Object information
 *
 * @see mtp_get_object_handles()
 */
MTP_API int mtp_objectinfo_get_thumbnail_size(int device_handle, int object_handle, int *size);

/**
 * @brief Get the thumbnail format of the object information.
 * @since_tizen 3.0
 * @ingroup CAPI_NETWORK_MTP_OBJECTINFO_MODULE
 *
 * @return 0 on success, otherwise a negative error value.
 * @retval #MTP_ERROR_NONE Successful
 *
 * @param [in] device_handle The device handle
 * @param [in] object_handle The object handle
 * @param [out] format The thumbnail format of Object information
 *
 * @see mtp_get_object_handles()
 */
MTP_API int mtp_objectinfo_get_thumbnail_format(int device_handle, int object_handle, int *format);

/**
 * @brief Get the thumbnail pix height of the object information.
 * @since_tizen 3.0
 * @ingroup CAPI_NETWORK_MTP_OBJECTINFO_MODULE
 *
 * @return 0 on success, otherwise a negative error value.
 * @retval #MTP_ERROR_NONE Successful
 *
 * @param [in] device_handle The device handle
 * @param [in] object_handle The object handle
 * @param [out] height The thumbnail pixel height of Object information
 *
 * @see mtp_get_object_handles()
 */
MTP_API int mtp_objectinfo_get_thumbnail_pix_height(int device_handle, int object_handle, int *height);

/**
 * @brief Get the thumbnail pix width of the object information.
 * @since_tizen 3.0
 * @ingroup CAPI_NETWORK_MTP_OBJECTINFO_MODULE
 *
 * @return 0 on success, otherwise a negative error value.
 * @retval #MTP_ERROR_NONE Successful
 *
 * @param [in] device_handle The device handle
 * @param [in] object_handle The object handle
 * @param [out] width The thumbnail pixel width of Object information
 *
 * @see mtp_get_object_handles()
 */
MTP_API int mtp_objectinfo_get_thumbnail_pix_width(int device_handle, int object_handle, int *width);

#ifdef __cplusplus
}
#endif

#endif
