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
#ifndef TIZEN_ERROR_MTP
#define TIZEN_ERROR_MTP -0x03000000
#endif

/**
 * @addtogroup CAPI_NETWORK_MTP_MANAGER_MODULE
 * @{
 */

/**
 * @brief The handle to the mtp raw device
 * @since_tizen 3.0
 */
typedef struct mtp_raw_device *mtp_raw_device_h;

/**
 * @brief The handle to the mtp device
 * @since_tizen 3.0
 */
typedef int mtp_device_h;

/**
 * @brief The handle to the mtp storage
 * @since_tizen 3.0
 */
typedef int mtp_storage_h;

/**
 * @brief The handle to the mtp object
 * @since_tizen 3.0
 */
typedef int mtp_object_h;

/**
 * @brief Error codes reported by the MTP API.
 * @since_tizen 3.0
 */
typedef enum {
	MTP_ERROR_NONE = TIZEN_ERROR_NONE, /**< Successful */
	MTP_ERROR_IO = TIZEN_ERROR_IO_ERROR, /**< I/O error */
	MTP_ERROR_INVALID_PARAMETER = TIZEN_ERROR_INVALID_PARAMETER, /**< Invalid parameter */
	MTP_ERROR_NO_DEVICE = TIZEN_ERROR_MTP | 0x01, /**< MTP have not any device */
	MTP_ERROR_ALLOC_FAIL = TIZEN_ERROR_MTP | 0x02, /**< Memory Allocation failed */
	MTP_ERROR_PLUGIN = TIZEN_ERROR_MTP | 0x03, /**< Plugin failed */
	MTP_ERROR_PERMISSION_DENIED = TIZEN_ERROR_PERMISSION_DENIED, /**< Permission denied */
	MTP_ERROR_COMM = TIZEN_ERROR_MTP | 0x04, /**< MTP communication error */
	MTP_ERROR_OPERATION_FAILED = TIZEN_ERROR_MTP | 0x05, /**< MTP operation is failed */
	MTP_ERROR_NOT_INITIALIZED = TIZEN_ERROR_MTP | 0x06, /**< MTP is not initiatlized */
	MTP_ERROR_NOT_ACTIVATED = TIZEN_ERROR_MTP | 0x07, /**< MTP is not activated */
	MTP_ERROR_NOT_SUPPORTED = TIZEN_ERROR_NOT_SUPPORTED, /**< MTP is not supported */
	MTP_ERROR_NOT_COMM_INITIALIZED = TIZEN_ERROR_MTP | 0x08 /**< MTP communication is not initiatlized */
} mtp_error_e;

/**
 * @brief Enumerations for MTP file type
 * @since_tizen 3.0
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
 */
typedef enum {
	MTP_EVENT_UNKNOWN, /**< Unknown event type */
	MTP_EVENT_STORAGE_ADDED, /**< Storage is added */
	MTP_EVENT_STORAGE_REMOVED, /**< Storage is removed */
	MTP_EVENT_OBJECT_ADDED, /**< Object is added */
	MTP_EVENT_OBJECT_REMOVED, /**< Object is removed */
	MTP_EVENT_DEVICE_ADDED, /**< Device is added */
	MTP_EVENT_DEVICE_REMOVED, /**< Device is removed */
	MTP_EVENT_TURNED_OFF /**< MTP is turned off */
} mtp_event_e;

/**
 * @brief Called after mtp_set_mtp_event_cb() has completed.
 * @since_tizen 3.0
 * @remarks Depending on the type of event, the meaning of event parameter is diffrent.
 * - If event is device event, then event_parameter means a mtp device
 * - If event is storage event, then event_parameter means a mtp storage
 * - If event is object event, then event_parameter means a object handle
 * - If event is MTP_EVENT_TURNED_OFF, then event_parameter is 0
 * @param [in] event The event
 * @param [in] event_parameter The event parameter
 * @param [in] user_data The user data passed from the callback registration function
 *
 * @see mtp_set_mtp_event_cb()
 * @see mtp_unset_mtp_event_cb()
 */
typedef void (* mtp_event_cb)(mtp_event_e event, int event_parameter, void *user_data);

/**
 * @brief Initializes for using MTP.
 * @since_tizen 3.0
 * @remarks This function must be called before proceeding any other mtp functions\n
 *
 * @return 0 on success, otherwise a negative error value.
 * @retval #MTP_ERROR_NONE Successful
 * @retval #MTP_ERROR_NOT_SUPPORTED MTP is not supported
 * @retval #MTP_ERROR_PERMISSION_DENIED Permission Denied
 * @retval #MTP_ERROR_NOT_COMM_INITIALIZED MTP communication is not initiatlized
 *
 * @see mtp_deinitialize()
 */
MTP_API int mtp_initialize(void);

/**
 * @brief Gets device list.
 * @since_tizen 3.0
 * @remarks The @a raw_devices should be freed using free().
 *
 * @return 0 on success, otherwise a negative error value.
 * @retval #MTP_ERROR_NONE Successful
 * @retval #MTP_ERROR_NOT_SUPPORTED MTP is not supported
 * @retval #MTP_ERROR_NOT_INITIALIZED MTP is not initialized
 * @retval #MTP_ERROR_NOT_ACTIVATED MTP is not activated
 * @retval #MTP_ERROR_INVALID_PARAMETER Invalid parameter
 * @retval #MTP_ERROR_NOT_COMM_INITIALIZED MTP communication is not initiatlized
 *
 * @param [out] raw_devices All current connected device list
 * @param [out] device_count The count of device
 */
MTP_API int mtp_get_raw_devices(mtp_raw_device_h *raw_devices, int *device_count);

/**
 * @brief Gets bus location from raw device
 * @since_tizen 3.0
 *
 * @return 0 on success, otherwise a negative error value.
 * @retval #MTP_ERROR_NONE Successful
 * @retval #MTP_ERROR_NOT_SUPPORTED MTP is not supported
 * @retval #MTP_ERROR_NOT_INITIALIZED MTP is not initialized
 * @retval #MTP_ERROR_INVALID_PARAMETER Invalid parameter
 *
 * @param [out] bus_location The bus location
 */
MTP_API int mtp_get_bus_location(mtp_raw_device_h raw_device, int *bus_location);

/**
 * @brief Gets device number from raw device
 * @since_tizen 3.0
 *
 * @return 0 on success, otherwise a negative error value.
 * @retval #MTP_ERROR_NONE Successful
 * @retval #MTP_ERROR_NOT_SUPPORTED MTP is not supported
 * @retval #MTP_ERROR_NOT_INITIALIZED MTP is not initialized
 * @retval #MTP_ERROR_INVALID_PARAMETER Invalid parameter
 *
 * @param [out] device_number The device number
 */
MTP_API int mtp_get_device_number(mtp_raw_device_h raw_device, int *device_number);

/**
 * @brief Gets device name from raw device
 * @since_tizen 3.0
 * @remarks The @a model_name should be freed using free().
 *
 * @return 0 on success, otherwise a negative error value.
 * @retval #MTP_ERROR_NONE Successful
 * @retval #MTP_ERROR_NOT_SUPPORTED MTP is not supported
 * @retval #MTP_ERROR_NOT_INITIALIZED MTP is not initialized
 * @retval #MTP_ERROR_INVALID_PARAMETER Invalid parameter
 *
 * @param [out] model_name The model name
 */
MTP_API int mtp_get_device_name(mtp_raw_device_h raw_device, char **model_name);

/**
 * @brief Gets device handler from bus location
 * @since_tizen 3.0
 * @remarks For using this api, you should get bus location and device number from raw device.
 *
 * @return 0 on success, otherwise a negative error value.
 * @retval #MTP_ERROR_NONE Successful
 * @retval #MTP_ERROR_NOT_SUPPORTED MTP is not supported
 * @retval #MTP_ERROR_NOT_INITIALIZED MTP is not initialized
 * @retval #MTP_ERROR_NOT_ACTIVATED MTP is not activated
 * @retval #MTP_ERROR_INVALID_PARAMETER Invalid parameter
 * @retval #MTP_ERROR_NOT_COMM_INITIALIZED MTP communication is not initiatlized
 * @retval #MTP_ERROR_COMM MTP communication error
 *
 * @param [in] bus_location The bus location
 * @param [out] mtp_device The MTP device
 *
 * @pre mtp_get_bus_location(), mtp_get_device_number()
 * @see mtp_initialize()
 */
MTP_API int mtp_get_device(int bus_location, int device_number, mtp_device_h *mtp_device);

/**
 * @brief Gets storage ids from device
 * @since_tizen 3.0
 * @remarks The @a mtp_storages should be freed using free().
 *
 * @return 0 on success, otherwise a negative error value.
 * @retval #MTP_ERROR_NONE Successful
 * @retval #MTP_ERROR_NOT_SUPPORTED MTP is not supported
 * @retval #MTP_ERROR_NOT_INITIALIZED MTP is not initialized
 * @retval #MTP_ERROR_NOT_ACTIVATED MTP is not activated
 * @retval #MTP_ERROR_INVALID_PARAMETER Invalid parameter
 * @retval #MTP_ERROR_NOT_COMM_INITIALIZED MTP communication is not initiatlized
 * @retval #MTP_ERROR_COMM MTP communication error
 *
 * @param [in] mtp_device The MTP device
 * @param [out] mtp_storages Current mtp storage list
 * @param [out] storage_num Length of storage list
 *
 * @see mtp_get_device()
 */
MTP_API int mtp_get_storages(mtp_device_h mtp_device, mtp_storage_h **mtp_storages, int* storage_num);

/**
 * @brief Gets object handles from device
 * @since_tizen 3.0
 * @remarks The @a object_handles should be freed using free().
 *
 * @return 0 on success, otherwise a negative error value.
 * @retval #MTP_ERROR_NONE Successful
 * @retval #MTP_ERROR_NOT_SUPPORTED MTP is not supported
 * @retval #MTP_ERROR_NOT_INITIALIZED MTP is not initialized
 * @retval #MTP_ERROR_NOT_ACTIVATED MTP is not activated
 * @retval #MTP_ERROR_INVALID_PARAMETER Invalid parameter
 * @retval #MTP_ERROR_NOT_COMM_INITIALIZED MTP communication is not initiatlized
 * @retval #MTP_ERROR_COMM MTP communication error
 *
 * @param [in] mtp_device The MTP device
 * @param [in] mtp_storage The MTP storage
 * @param [in] format The file type what you want
 * @param [in] parent The parent object handle
 * @param [out] object_handles The object handle list
 * @param [out] object_num Length of object handle list
 *
 * @see mtp_get_device()
 * @see mtp_get_storages()
 */
MTP_API int mtp_get_object_handles(mtp_device_h mtp_device, mtp_storage_h mtp_storage, mtp_filetype_e file_type,
	mtp_object_h parent, mtp_object_h **object_handles, int* object_num);

/**
 * @brief Gets object from object handle
 * @since_tizen 3.0
 *
 * @return 0 on success, otherwise a negative error value.
 * @retval #MTP_ERROR_NONE Successful
 * @retval #MTP_ERROR_NOT_SUPPORTED MTP is not supported
 * @retval #MTP_ERROR_NOT_INITIALIZED MTP is not initialized
 * @retval #MTP_ERROR_NOT_ACTIVATED MTP is not activated
 * @retval #MTP_ERROR_INVALID_PARAMETER Invalid parameter
 * @retval #MTP_ERROR_NOT_COMM_INITIALIZED MTP communication is not initiatlized
 * @retval #MTP_ERROR_COMM MTP communication error
 *
 * @param [in] mtp_device The MTP device
 * @param [in] object_handle The object handle
 * @param [in] dest_path The dest path
 *
 * @see mtp_get_device()
 * @see mtp_get_object_handles()
 */
MTP_API int mtp_get_object(mtp_device_h mtp_device, mtp_object_h object_handle, char *dest_path);

/**
 * @brief Gets thumbnail from object handle
 * @since_tizen 3.0
 *
 * @return 0 on success, otherwise a negative error value.
 * @retval #MTP_ERROR_NONE Successful
 * @retval #MTP_ERROR_NOT_SUPPORTED MTP is not supported
 * @retval #MTP_ERROR_NOT_INITIALIZED MTP is not initialized
 * @retval #MTP_ERROR_NOT_ACTIVATED MTP is not activated
 * @retval #MTP_ERROR_INVALID_PARAMETER Invalid parameter
 * @retval #MTP_ERROR_NOT_COMM_INITIALIZED MTP communication is not initiatlized
 * @retval #MTP_ERROR_COMM MTP communication error
 *
 * @param [in] mtp_device The MTP device
 * @param [in] object_handle The object handle
 * @param [in] dest_path The dest path
 *
 * @see mtp_get_device()
 * @see mtp_get_object_handles()
 */
MTP_API int mtp_get_thumbnail(mtp_device_h mtp_device, mtp_object_h object_handle, char *dest_path);

/**
 * @brief Registers a callback function for receiving MTP event.
 * @since_tizen 3.0
 *
 * @detail If device state is changed, DEVICE_ADD or DEVICE_REMOVE event is occur. \n
 *   If storage state is changed, STORAGE_ADD or STORAGE_REMOVE event is occur. \n
 *   If object state is changed, OBJECT_ADD or OBJECT_REMOVE event is occur.
 *
 * @return 0 on success, otherwise a negative error value.
 * @retval #MTP_ERROR_NONE Successful
 * @retval #MTP_ERROR_NOT_SUPPORTED MTP is not supported
 * @retval #MTP_ERROR_NOT_INITIALIZED MTP is not initialized
 * @retval #MTP_ERROR_INVALID_PARAMETER Invalid parameter
 *
 * @param [in] callback The callback
 * @param [in] user_data The user data
 *
 * @see mtp_unset_mtp_event_cb()
 */
MTP_API int mtp_set_mtp_event_cb(mtp_event_cb event_cb, void *user_data);

/**
 * @brief Unregisters the callback function.
 * @since_tizen 3.0
 *
 * @return 0 on success, otherwise a negative error value.
 * @retval #MTP_ERROR_NONE Successful
 * @retval #MTP_ERROR_NOT_SUPPORTED MTP is not supported
 * @retval #MTP_ERROR_NOT_INITIALIZED MTP is not initialized
 * @retval #MTP_ERROR_INVALID_PARAMETER Invalid parameter
 *
 * @see mtp_set_mtp_event_cb()
 */
MTP_API int mtp_unset_mtp_event_cb(void);

/**
 * @brief Deinitializes MTP operation.
 * @since_tizen 3.0
 *
 * @return 0 on success, otherwise a negative error value.
 * @retval #MTP_ERROR_NONE Successful
 * @retval #MTP_ERROR_NOT_SUPPORTED MTP is not supported
 * @retval #MTP_ERROR_PERMISSION_DENIED Permission Denied
 *
 * @see mtp_initialize()
 */
MTP_API int mtp_deinitialize(void);

/**
* @}
*/

/**
 * @addtogroup CAPI_NETWORK_MTP_DEVICEINFO_MODULE
 * @{
 */

/**
 * @brief Gets the manufacturer name of the device information.
 * @since_tizen 3.0
 * @remarks The @a manufacturer_name should be freed using free().
 *
 * @return 0 on success, otherwise a negative error value.
 * @retval #MTP_ERROR_NONE Successful
 * @retval #MTP_ERROR_NOT_SUPPORTED MTP is not supported
 * @retval #MTP_ERROR_NOT_INITIALIZED MTP is not initialized
 * @retval #MTP_ERROR_NOT_ACTIVATED MTP is not activated
 * @retval #MTP_ERROR_INVALID_PARAMETER Invalid parameter
 * @retval #MTP_ERROR_NOT_COMM_INITIALIZED MTP communication is not initiatlized
 * @retval #MTP_ERROR_COMM MTP communication error
 * @retval #MTP_ERROR_CONTROLLER MTP controller error
 * @retval #MTP_ERROR_ALLOC_FAIL Memory Allocation failed
 * @retval #MTP_ERROR_NO_DEVICE MTP have not any device
 *
 * @param [in] mtp_device The MTP device
 * @param [out] manufacturername The manufacturername of Device information
 *
 * @see mtp_get_device()
 */
MTP_API int mtp_deviceinfo_get_manufacturer_name(mtp_device_h mtp_device, char **manufacturer_name);

/**
 * @brief Gets the model name of the device information.
 * @since_tizen 3.0
 * @remarks The @a model_name should be freed using free().
 *
 * @return 0 on success, otherwise a negative error value.
 * @retval #MTP_ERROR_NONE Successful
 * @retval #MTP_ERROR_NOT_SUPPORTED MTP is not supported
 * @retval #MTP_ERROR_NOT_INITIALIZED MTP is not initialized
 * @retval #MTP_ERROR_NOT_ACTIVATED MTP is not activated
 * @retval #MTP_ERROR_INVALID_PARAMETER Invalid parameter
 * @retval #MTP_ERROR_NOT_COMM_INITIALIZED MTP communication is not initiatlized
 * @retval #MTP_ERROR_COMM MTP communication error
 * @retval #MTP_ERROR_CONTROLLER MTP controller error
 * @retval #MTP_ERROR_ALLOC_FAIL Memory Allocation failed
 * @retval #MTP_ERROR_NO_DEVICE MTP have not any device
 *
 * @param [in] mtp_device The MTP device
 * @param [out] modelname The modelname of Device information
 *
 * @see mtp_get_device()
 */
MTP_API int mtp_deviceinfo_get_model_name(mtp_device_h mtp_device, char **model_name);

/**
 * @brief Gets the serial number of the device information.
 * @since_tizen 3.0
 * @remarks The @a serial_number should be freed using free().
 *
 * @return 0 on success, otherwise a negative error value.
 * @retval #MTP_ERROR_NONE Successful
 * @retval #MTP_ERROR_NOT_SUPPORTED MTP is not supported
 * @retval #MTP_ERROR_NOT_INITIALIZED MTP is not initialized
 * @retval #MTP_ERROR_NOT_ACTIVATED MTP is not activated
 * @retval #MTP_ERROR_INVALID_PARAMETER Invalid parameter
 * @retval #MTP_ERROR_NOT_COMM_INITIALIZED MTP communication is not initiatlized
 * @retval #MTP_ERROR_COMM MTP communication error
 * @retval #MTP_ERROR_CONTROLLER MTP controller error
 * @retval #MTP_ERROR_ALLOC_FAIL Memory Allocation failed
 * @retval #MTP_ERROR_NO_DEVICE MTP have not any device
 *
 * @param [in] mtp_device The MTP device
 * @param [out] serialnumber The serialnumber of Device information
 *
 * @see mtp_get_device()
 */
MTP_API int mtp_deviceinfo_get_serial_number(mtp_device_h mtp_device, char **serial_number);

/**
 * @brief Gets the device version of the device information.
 * @since_tizen 3.0
 * @remarks The @a device_version should be freed using free().
 *
 * @return 0 on success, otherwise a negative error value.
 * @retval #MTP_ERROR_NONE Successful
 * @retval #MTP_ERROR_NOT_SUPPORTED MTP is not supported
 * @retval #MTP_ERROR_NOT_INITIALIZED MTP is not initialized
 * @retval #MTP_ERROR_NOT_ACTIVATED MTP is not activated
 * @retval #MTP_ERROR_INVALID_PARAMETER Invalid parameter
 * @retval #MTP_ERROR_NOT_COMM_INITIALIZED MTP communication is not initiatlized
 * @retval #MTP_ERROR_COMM MTP communication error
 * @retval #MTP_ERROR_CONTROLLER MTP controller error
 * @retval #MTP_ERROR_ALLOC_FAIL Memory Allocation failed
 * @retval #MTP_ERROR_NO_DEVICE MTP have not any device
 *
 * @param [in] mtp_device The MTP device
 * @param [out] device_version The device version of Device information
 *
 * @see mtp_get_device()
 */
MTP_API int mtp_deviceinfo_get_device_version(mtp_device_h mtp_device, char **device_version);

/**
* @}
*/

/**
 * @addtogroup CAPI_NETWORK_MTP_STORAGEINFO_MODULE
 * @{
 */

/**
 * @brief Gets the description of the storage information.
 * @since_tizen 3.0
 * @remarks The @a description should be freed using free().
 *
 * @return 0 on success, otherwise a negative error value.
 * @retval #MTP_ERROR_NONE Successful
 * @retval #MTP_ERROR_NOT_SUPPORTED MTP is not supported
 * @retval #MTP_ERROR_NOT_INITIALIZED MTP is not initialized
 * @retval #MTP_ERROR_NOT_ACTIVATED MTP is not activated
 * @retval #MTP_ERROR_INVALID_PARAMETER Invalid parameter
 * @retval #MTP_ERROR_NOT_COMM_INITIALIZED MTP communication is not initiatlized
 * @retval #MTP_ERROR_COMM MTP communication error
 * @retval #MTP_ERROR_CONTROLLER MTP controller error
 * @retval #MTP_ERROR_ALLOC_FAIL Memory Allocation failed
 * @retval #MTP_ERROR_NO_DEVICE MTP have not any device
 *
 * @param [in] mtp_device The MTP device
 * @param [in] mtp_storage The MTP storage
 * @param [out] description The description of Storage information
 *
 * @see mtp_get_storages()
 */
MTP_API int mtp_storageinfo_get_description(mtp_device_h mtp_device, mtp_storage_h mtp_storage, char **description);

/**
 * @brief Gets the freespace of the storage information.
 * @since_tizen 3.0
 *
 * @return 0 on success, otherwise a negative error value.
 * @retval #MTP_ERROR_NONE Successful
 * @retval #MTP_ERROR_NOT_SUPPORTED MTP is not supported
 * @retval #MTP_ERROR_NOT_INITIALIZED MTP is not initialized
 * @retval #MTP_ERROR_NOT_ACTIVATED MTP is not activated
 * @retval #MTP_ERROR_INVALID_PARAMETER Invalid parameter
 * @retval #MTP_ERROR_NOT_COMM_INITIALIZED MTP communication is not initiatlized
 * @retval #MTP_ERROR_COMM MTP communication error
 * @retval #MTP_ERROR_CONTROLLER MTP controller error
 * @retval #MTP_ERROR_ALLOC_FAIL Memory Allocation failed
 * @retval #MTP_ERROR_NO_DEVICE MTP have not any device
 *
 * @param [in] mtp_device The MTP device
 * @param [in] mtp_storage The MTP storage
 * @param [out] free_space The free space of Storage information
 *
 * @see mtp_get_storages()
 */
MTP_API int mtp_storageinfo_get_free_space(mtp_device_h mtp_device, mtp_storage_h mtp_storage, unsigned long long *free_space);

/**
 * @brief Gets the max capacity of the storage information.
 * @since_tizen 3.0
 *
 * @return 0 on success, otherwise a negative error value.
 * @retval #MTP_ERROR_NONE Successful
 * @retval #MTP_ERROR_NOT_SUPPORTED MTP is not supported
 * @retval #MTP_ERROR_NOT_INITIALIZED MTP is not initialized
 * @retval #MTP_ERROR_NOT_ACTIVATED MTP is not activated
 * @retval #MTP_ERROR_INVALID_PARAMETER Invalid parameter
 * @retval #MTP_ERROR_NOT_COMM_INITIALIZED MTP communication is not initiatlized
 * @retval #MTP_ERROR_COMM MTP communication error
 * @retval #MTP_ERROR_CONTROLLER MTP controller error
 * @retval #MTP_ERROR_ALLOC_FAIL Memory Allocation failed
 * @retval #MTP_ERROR_NO_DEVICE MTP have not any device
 *
 * @param [in] mtp_device The MTP device
 * @param [in] mtp_storage The MTP storage
 * @param [out] max_capacity The max capacity of Storage information
 *
 * @see mtp_get_storages()
 */
MTP_API int mtp_storageinfo_get_max_capacity(mtp_device_h mtp_device, mtp_storage_h mtp_storage, unsigned long long *max_capacity);

/**
 * @brief Gets the storage type of the storage information.
 * @since_tizen 3.0
 *
 * @return 0 on success, otherwise a negative error value.
 * @retval #MTP_ERROR_NONE Successful
 * @retval #MTP_ERROR_NOT_SUPPORTED MTP is not supported
 * @retval #MTP_ERROR_NOT_INITIALIZED MTP is not initialized
 * @retval #MTP_ERROR_NOT_ACTIVATED MTP is not activated
 * @retval #MTP_ERROR_INVALID_PARAMETER Invalid parameter
 * @retval #MTP_ERROR_NOT_COMM_INITIALIZED MTP communication is not initiatlized
 * @retval #MTP_ERROR_COMM MTP communication error
 * @retval #MTP_ERROR_CONTROLLER MTP controller error
 * @retval #MTP_ERROR_ALLOC_FAIL Memory Allocation failed
 * @retval #MTP_ERROR_NO_DEVICE MTP have not any device
 *
 * @param [in] mtp_device The MTP device
 * @param [in] mtp_storage The MTP storage
 * @param [out] storage_type The storage type of Storage information
 *
 * @see mtp_get_storages()
 */
MTP_API int mtp_storageinfo_get_storage_type(mtp_device_h mtp_device, mtp_storage_h mtp_storage, int *storage_type);

/**
 * @brief Gets the volumeidentifier of the storage information.
 * @since_tizen 3.0
 * @remarks The @a volume_identifier should be freed using free().
 *
 * @return 0 on success, otherwise a negative error value.
 * @retval #MTP_ERROR_NONE Successful
 * @retval #MTP_ERROR_NOT_SUPPORTED MTP is not supported
 * @retval #MTP_ERROR_NOT_INITIALIZED MTP is not initialized
 * @retval #MTP_ERROR_NOT_ACTIVATED MTP is not activated
 * @retval #MTP_ERROR_INVALID_PARAMETER Invalid parameter
 * @retval #MTP_ERROR_NOT_COMM_INITIALIZED MTP communication is not initiatlized
 * @retval #MTP_ERROR_COMM MTP communication error
 * @retval #MTP_ERROR_CONTROLLER MTP controller error
 * @retval #MTP_ERROR_ALLOC_FAIL Memory Allocation failed
 * @retval #MTP_ERROR_NO_DEVICE MTP have not any device
 *
 * @param [in] mtp_device The MTP device
 * @param [in] mtp_storage The MTP storage
 * @param [out] volume_identifier The volume identifier of Storage information
 *
 * @see mtp_get_object_handles()
 */
MTP_API int mtp_storageinfo_get_volume_identifier(mtp_device_h mtp_device, mtp_storage_h mtp_storage, char **volume_identifier);

/**
* @}
*/

/**
 * @addtogroup CAPI_NETWORK_MTP_OBJECTINFO_MODULE
 * @{
 */

/**
 * @brief Gets the filename of the object information.
 * @since_tizen 3.0
 * @remarks The @a file_name should be freed using free().
 *
 * @return 0 on success, otherwise a negative error value.
 * @retval #MTP_ERROR_NONE Successful
 * @retval #MTP_ERROR_NOT_SUPPORTED MTP is not supported
 * @retval #MTP_ERROR_NOT_INITIALIZED MTP is not initialized
 * @retval #MTP_ERROR_NOT_ACTIVATED MTP is not activated
 * @retval #MTP_ERROR_INVALID_PARAMETER Invalid parameter
 * @retval #MTP_ERROR_NOT_COMM_INITIALIZED MTP communication is not initiatlized
 * @retval #MTP_ERROR_COMM MTP communication error
 * @retval #MTP_ERROR_CONTROLLER MTP controller error
 * @retval #MTP_ERROR_ALLOC_FAIL Memory Allocation failed
 * @retval #MTP_ERROR_NO_DEVICE MTP have not any device
 * @retval #MTP_ERROR_PLUGIN Plugin failed
 *
 * @param [in] mtp_device The MTP device
 * @param [in] object_handle The object handle
 * @param [out] filename The filename of Object information
 *
 * @see mtp_get_object_handles()
 */
MTP_API int mtp_objectinfo_get_file_name(mtp_device_h mtp_device, mtp_object_h object_handle, char **file_name);

/**
 * @brief Gets the keywords of the object information.
 * @since_tizen 3.0
 * @remarks The @a keywords should be freed using free().
 *
 * @return 0 on success, otherwise a negative error value.
 * @retval #MTP_ERROR_NONE Successful
 * @retval #MTP_ERROR_NOT_SUPPORTED MTP is not supported
 * @retval #MTP_ERROR_NOT_INITIALIZED MTP is not initialized
 * @retval #MTP_ERROR_NOT_ACTIVATED MTP is not activated
 * @retval #MTP_ERROR_INVALID_PARAMETER Invalid parameter
 * @retval #MTP_ERROR_NOT_COMM_INITIALIZED MTP communication is not initiatlized
 * @retval #MTP_ERROR_COMM MTP communication error
 * @retval #MTP_ERROR_CONTROLLER MTP controller error
 * @retval #MTP_ERROR_ALLOC_FAIL Memory Allocation failed
 * @retval #MTP_ERROR_NO_DEVICE MTP have not any device
 * @retval #MTP_ERROR_PLUGIN Plugin failed
 *
 * @param [in] mtp_device The MTP device
 * @param [in] object_handle The object handle
 * @param [out] keywords The keywords of Object information
 *
 * @see mtp_get_object_handles()
 */
MTP_API int mtp_objectinfo_get_keywords(mtp_device_h mtp_device, mtp_object_h object_handle, char **keywords);

/**
 * @brief Gets the association desc of the object information.
 * @since_tizen 3.0
 *
 * @return 0 on success, otherwise a negative error value.
 * @retval #MTP_ERROR_NONE Successful
 * @retval #MTP_ERROR_NOT_SUPPORTED MTP is not supported
 * @retval #MTP_ERROR_NOT_INITIALIZED MTP is not initialized
 * @retval #MTP_ERROR_NOT_ACTIVATED MTP is not activated
 * @retval #MTP_ERROR_INVALID_PARAMETER Invalid parameter
 * @retval #MTP_ERROR_NOT_COMM_INITIALIZED MTP communication is not initiatlized
 * @retval #MTP_ERROR_COMM MTP communication error
 * @retval #MTP_ERROR_CONTROLLER MTP controller error
 * @retval #MTP_ERROR_ALLOC_FAIL Memory Allocation failed
 * @retval #MTP_ERROR_NO_DEVICE MTP have not any device
 * @retval #MTP_ERROR_PLUGIN Plugin failed
 *
 * @param [in] mtp_device The MTP device
 * @param [in] object_handle The object handle
 * @param [out] asso_desc The association description of Object information
 *
 * @see mtp_get_object_handles()
 */
MTP_API int mtp_objectinfo_get_association_desc(mtp_device_h mtp_device, mtp_object_h object_handle, int *asso_desc);

/**
 * @brief Gets the association type of the object information.
 * @since_tizen 3.0
 *
 * @return 0 on success, otherwise a negative error value.
 * @retval #MTP_ERROR_NONE Successful
 * @retval #MTP_ERROR_NOT_SUPPORTED MTP is not supported
 * @retval #MTP_ERROR_NOT_INITIALIZED MTP is not initialized
 * @retval #MTP_ERROR_NOT_ACTIVATED MTP is not activated
 * @retval #MTP_ERROR_INVALID_PARAMETER Invalid parameter
 * @retval #MTP_ERROR_NOT_COMM_INITIALIZED MTP communication is not initiatlized
 * @retval #MTP_ERROR_COMM MTP communication error
 * @retval #MTP_ERROR_CONTROLLER MTP controller error
 * @retval #MTP_ERROR_ALLOC_FAIL Memory Allocation failed
 * @retval #MTP_ERROR_NO_DEVICE MTP have not any device
 * @retval #MTP_ERROR_PLUGIN Plugin failed
 *
 * @param [in] mtp_device The MTP device
 * @param [in] object_handle The object handle
 * @param [out] asso_type The association type of Object information
 *
 * @see mtp_get_object_handles()
 */
MTP_API int mtp_objectinfo_get_association_type(mtp_device_h mtp_device, mtp_object_h object_handle, int *asso_type);

/**
 * @brief Gets the size of the object information.
 * @since_tizen 3.0
 *
 * @return 0 on success, otherwise a negative error value.
 * @retval #MTP_ERROR_NONE Successful
 * @retval #MTP_ERROR_NOT_SUPPORTED MTP is not supported
 * @retval #MTP_ERROR_NOT_INITIALIZED MTP is not initialized
 * @retval #MTP_ERROR_NOT_ACTIVATED MTP is not activated
 * @retval #MTP_ERROR_INVALID_PARAMETER Invalid parameter
 * @retval #MTP_ERROR_NOT_COMM_INITIALIZED MTP communication is not initiatlized
 * @retval #MTP_ERROR_COMM MTP communication error
 * @retval #MTP_ERROR_CONTROLLER MTP controller error
 * @retval #MTP_ERROR_ALLOC_FAIL Memory Allocation failed
 * @retval #MTP_ERROR_NO_DEVICE MTP have not any device
 * @retval #MTP_ERROR_PLUGIN Plugin failed
 *
 * @param [in] mtp_device The MTP device
 * @param [in] object_handle The object handle
 * @param [out] size The size of Object information
 *
 * @see mtp_get_object_handles()
 */
MTP_API int mtp_objectinfo_get_size(mtp_device_h mtp_device, mtp_object_h object_handle, int *size);

/**
 * @brief Gets the parent object handle of the object information.
 * @since_tizen 3.0
 *
 * @return 0 on success, otherwise a negative error value.
 * @retval #MTP_ERROR_NONE Successful
 * @retval #MTP_ERROR_NOT_SUPPORTED MTP is not supported
 * @retval #MTP_ERROR_NOT_INITIALIZED MTP is not initialized
 * @retval #MTP_ERROR_NOT_ACTIVATED MTP is not activated
 * @retval #MTP_ERROR_INVALID_PARAMETER Invalid parameter
 * @retval #MTP_ERROR_NOT_COMM_INITIALIZED MTP communication is not initiatlized
 * @retval #MTP_ERROR_COMM MTP communication error
 * @retval #MTP_ERROR_CONTROLLER MTP controller error
 * @retval #MTP_ERROR_ALLOC_FAIL Memory Allocation failed
 * @retval #MTP_ERROR_NO_DEVICE MTP have not any device
 * @retval #MTP_ERROR_PLUGIN Plugin failed
 *
 * @param [in] mtp_device The MTP device
 * @param [in] object_handle The object handle
 * @param [out] parent_object_handle The parent of Object information
 *
 * @see mtp_get_object_handles()
 */
MTP_API int mtp_objectinfo_get_parent_object_handle(mtp_device_h mtp_device, mtp_object_h object_handle, mtp_object_h *parent_object_handle);

/**
 * @brief Gets the storage id of the object information.
 * @since_tizen 3.0
 *
 * @return 0 on success, otherwise a negative error value.
 * @retval #MTP_ERROR_NONE Successful
 * @retval #MTP_ERROR_NOT_SUPPORTED MTP is not supported
 * @retval #MTP_ERROR_NOT_INITIALIZED MTP is not initialized
 * @retval #MTP_ERROR_NOT_ACTIVATED MTP is not activated
 * @retval #MTP_ERROR_INVALID_PARAMETER Invalid parameter
 * @retval #MTP_ERROR_NOT_COMM_INITIALIZED MTP communication is not initiatlized
 * @retval #MTP_ERROR_COMM MTP communication error
 * @retval #MTP_ERROR_CONTROLLER MTP controller error
 * @retval #MTP_ERROR_ALLOC_FAIL Memory Allocation failed
 * @retval #MTP_ERROR_NO_DEVICE MTP have not any device
 * @retval #MTP_ERROR_PLUGIN Plugin failed
 *
 * @param [in] mtp_device The MTP device
 * @param [in] object_handle The object handle
 * @param [out] mtp_storage The MTP storage of Object information
 *
 * @see mtp_get_object_handles()
 */
MTP_API int mtp_objectinfo_get_storage(mtp_device_h mtp_device, mtp_object_h object_handle, mtp_storage_h* mtp_storage);

/**
 * @brief Gets the data created time of the object information.
 * @since_tizen 3.0
 *
 * @return 0 on success, otherwise a negative error value.
 * @retval #MTP_ERROR_NONE Successful
 * @retval #MTP_ERROR_NOT_SUPPORTED MTP is not supported
 * @retval #MTP_ERROR_NOT_INITIALIZED MTP is not initialized
 * @retval #MTP_ERROR_NOT_ACTIVATED MTP is not activated
 * @retval #MTP_ERROR_INVALID_PARAMETER Invalid parameter
 * @retval #MTP_ERROR_NOT_COMM_INITIALIZED MTP communication is not initiatlized
 * @retval #MTP_ERROR_COMM MTP communication error
 * @retval #MTP_ERROR_CONTROLLER MTP controller error
 * @retval #MTP_ERROR_ALLOC_FAIL Memory Allocation failed
 * @retval #MTP_ERROR_NO_DEVICE MTP have not any device
 * @retval #MTP_ERROR_PLUGIN Plugin failed
 *
 * @param [in] mtp_device The MTP device
 * @param [in] object_handle The object handle
 * @param [out] data_created The data created time of Object information
 *
 * @see mtp_get_object_handles()
 */
MTP_API int mtp_objectinfo_get_data_created(mtp_device_h mtp_device, mtp_object_h object_handle, int *data_created);

/**
 * @brief Gets the data modified time of the object information.
 * @since_tizen 3.0
 *
 * @return 0 on success, otherwise a negative error value.
 * @retval #MTP_ERROR_NONE Successful
 * @retval #MTP_ERROR_NOT_SUPPORTED MTP is not supported
 * @retval #MTP_ERROR_NOT_INITIALIZED MTP is not initialized
 * @retval #MTP_ERROR_NOT_ACTIVATED MTP is not activated
 * @retval #MTP_ERROR_INVALID_PARAMETER Invalid parameter
 * @retval #MTP_ERROR_NOT_COMM_INITIALIZED MTP communication is not initiatlized
 * @retval #MTP_ERROR_COMM MTP communication error
 * @retval #MTP_ERROR_CONTROLLER MTP controller error
 * @retval #MTP_ERROR_ALLOC_FAIL Memory Allocation failed
 * @retval #MTP_ERROR_NO_DEVICE MTP have not any device
 * @retval #MTP_ERROR_PLUGIN Plugin failed
 *
 * @param [in] mtp_device The MTP device
 * @param [in] object_handle The object handle
 * @param [out] data_modified The data modified time of Object information
 *
 * @see mtp_get_object_handles()
 */
MTP_API int mtp_objectinfo_get_data_modified(mtp_device_h mtp_device, mtp_object_h object_handle, int *data_modified);

/**
 * @brief Gets the format of the object information.
 * @since_tizen 3.0
 *
 * @return 0 on success, otherwise a negative error value.
 * @retval #MTP_ERROR_NONE Successful
 * @retval #MTP_ERROR_NOT_SUPPORTED MTP is not supported
 * @retval #MTP_ERROR_NOT_INITIALIZED MTP is not initialized
 * @retval #MTP_ERROR_NOT_ACTIVATED MTP is not activated
 * @retval #MTP_ERROR_INVALID_PARAMETER Invalid parameter
 * @retval #MTP_ERROR_NOT_COMM_INITIALIZED MTP communication is not initiatlized
 * @retval #MTP_ERROR_COMM MTP communication error
 * @retval #MTP_ERROR_CONTROLLER MTP controller error
 * @retval #MTP_ERROR_ALLOC_FAIL Memory Allocation failed
 * @retval #MTP_ERROR_NO_DEVICE MTP have not any device
 * @retval #MTP_ERROR_PLUGIN Plugin failed
 *
 * @param [in] mtp_device The MTP device
 * @param [in] object_handle The object handle
 * @param [out] format The image format of Object information
 *
 * @see mtp_get_object_handles()
 */
MTP_API int mtp_objectinfo_get_format(mtp_device_h mtp_device, mtp_object_h object_handle, int *format);

/**
 * @brief Gets the image pix depth of the object information.
 * @since_tizen 3.0
 *
 * @return 0 on success, otherwise a negative error value.
 * @retval #MTP_ERROR_NONE Successful
 * @retval #MTP_ERROR_NOT_SUPPORTED MTP is not supported
 * @retval #MTP_ERROR_NOT_INITIALIZED MTP is not initialized
 * @retval #MTP_ERROR_NOT_ACTIVATED MTP is not activated
 * @retval #MTP_ERROR_INVALID_PARAMETER Invalid parameter
 * @retval #MTP_ERROR_NOT_COMM_INITIALIZED MTP communication is not initiatlized
 * @retval #MTP_ERROR_COMM MTP communication error
 * @retval #MTP_ERROR_CONTROLLER MTP controller error
 * @retval #MTP_ERROR_ALLOC_FAIL Memory Allocation failed
 * @retval #MTP_ERROR_NO_DEVICE MTP have not any device
 * @retval #MTP_ERROR_PLUGIN Plugin failed
 *
 * @param [in] mtp_device The MTP device
 * @param [in] object_handle The object handle
 * @param [out] depth The image pixel depth of Object information
 *
 * @see mtp_get_object_handles()
 */
MTP_API int mtp_objectinfo_get_image_pix_depth(mtp_device_h mtp_device, mtp_object_h object_handle, int *depth);

/**
 * @brief Gets the image pix width of the object information.
 * @since_tizen 3.0
 *
 * @return 0 on success, otherwise a negative error value.
 * @retval #MTP_ERROR_NONE Successful
 * @retval #MTP_ERROR_NOT_SUPPORTED MTP is not supported
 * @retval #MTP_ERROR_NOT_INITIALIZED MTP is not initialized
 * @retval #MTP_ERROR_NOT_ACTIVATED MTP is not activated
 * @retval #MTP_ERROR_INVALID_PARAMETER Invalid parameter
 * @retval #MTP_ERROR_NOT_COMM_INITIALIZED MTP communication is not initiatlized
 * @retval #MTP_ERROR_COMM MTP communication error
 * @retval #MTP_ERROR_CONTROLLER MTP controller error
 * @retval #MTP_ERROR_ALLOC_FAIL Memory Allocation failed
 * @retval #MTP_ERROR_NO_DEVICE MTP have not any device
 * @retval #MTP_ERROR_PLUGIN Plugin failed
 *
 * @param [in] mtp_device The MTP device
 * @param [in] object_handle The object handle
 * @param [out] width The image pixel width of Object information
 *
 * @see mtp_get_object_handles()
 */
MTP_API int mtp_objectinfo_get_image_pix_width(mtp_device_h mtp_device, mtp_object_h object_handle, int *width);

/**
 * @brief Gets the image pix height of the object information.
 * @since_tizen 3.0
 *
 * @return 0 on success, otherwise a negative error value.
 * @retval #MTP_ERROR_NONE Successful
 * @retval #MTP_ERROR_NOT_SUPPORTED MTP is not supported
 * @retval #MTP_ERROR_NOT_INITIALIZED MTP is not initialized
 * @retval #MTP_ERROR_NOT_ACTIVATED MTP is not activated
 * @retval #MTP_ERROR_INVALID_PARAMETER Invalid parameter
 * @retval #MTP_ERROR_NOT_COMM_INITIALIZED MTP communication is not initiatlized
 * @retval #MTP_ERROR_COMM MTP communication error
 * @retval #MTP_ERROR_CONTROLLER MTP controller error
 * @retval #MTP_ERROR_ALLOC_FAIL Memory Allocation failed
 * @retval #MTP_ERROR_NO_DEVICE MTP have not any device
 * @retval #MTP_ERROR_PLUGIN Plugin failed
 *
 * @param [in] mtp_device The MTP device
 * @param [in] object_handle The object handle
 * @param [out] height The image pixel height of Object information
 *
 * @see mtp_get_object_handles()
 */
MTP_API int mtp_objectinfo_get_image_pix_height(mtp_device_h mtp_device, mtp_object_h object_handle, int *height);

/**
 * @brief Gets the thumbnail size of the object information.
 * @since_tizen 3.0
 *
 * @return 0 on success, otherwise a negative error value.
 * @retval #MTP_ERROR_NONE Successful
 * @retval #MTP_ERROR_NOT_SUPPORTED MTP is not supported
 * @retval #MTP_ERROR_NOT_INITIALIZED MTP is not initialized
 * @retval #MTP_ERROR_NOT_ACTIVATED MTP is not activated
 * @retval #MTP_ERROR_INVALID_PARAMETER Invalid parameter
 * @retval #MTP_ERROR_NOT_COMM_INITIALIZED MTP communication is not initiatlized
 * @retval #MTP_ERROR_COMM MTP communication error
 * @retval #MTP_ERROR_CONTROLLER MTP controller error
 * @retval #MTP_ERROR_ALLOC_FAIL Memory Allocation failed
 * @retval #MTP_ERROR_NO_DEVICE MTP have not any device
 * @retval #MTP_ERROR_PLUGIN Plugin failed
 *
 * @param [in] mtp_device The MTP device
 * @param [in] object_handle The object handle
 * @param [out] size The thumbnail size of Object information
 *
 * @see mtp_get_object_handles()
 */
MTP_API int mtp_objectinfo_get_thumbnail_size(mtp_device_h mtp_device, mtp_object_h object_handle, int *size);

/**
 * @brief Gets the thumbnail format of the object information.
 * @since_tizen 3.0
 *
 * @return 0 on success, otherwise a negative error value.
 * @retval #MTP_ERROR_NONE Successful
 * @retval #MTP_ERROR_NOT_SUPPORTED MTP is not supported
 * @retval #MTP_ERROR_NOT_INITIALIZED MTP is not initialized
 * @retval #MTP_ERROR_NOT_ACTIVATED MTP is not activated
 * @retval #MTP_ERROR_INVALID_PARAMETER Invalid parameter
 * @retval #MTP_ERROR_NOT_COMM_INITIALIZED MTP communication is not initiatlized
 * @retval #MTP_ERROR_COMM MTP communication error
 * @retval #MTP_ERROR_CONTROLLER MTP controller error
 * @retval #MTP_ERROR_ALLOC_FAIL Memory Allocation failed
 * @retval #MTP_ERROR_NO_DEVICE MTP have not any device
 * @retval #MTP_ERROR_PLUGIN Plugin failed
 *
 * @param [in] mtp_device The MTP device
 * @param [in] object_handle The object handle
 * @param [out] format The thumbnail format of Object information
 *
 * @see mtp_get_object_handles()
 */
MTP_API int mtp_objectinfo_get_thumbnail_format(mtp_device_h mtp_device, mtp_object_h object_handle, int *format);

/**
 * @brief Gets the thumbnail pix height of the object information.
 * @since_tizen 3.0
 *
 * @return 0 on success, otherwise a negative error value.
 * @retval #MTP_ERROR_NONE Successful
 * @retval #MTP_ERROR_NOT_SUPPORTED MTP is not supported
 * @retval #MTP_ERROR_NOT_INITIALIZED MTP is not initialized
 * @retval #MTP_ERROR_NOT_ACTIVATED MTP is not activated
 * @retval #MTP_ERROR_INVALID_PARAMETER Invalid parameter
 * @retval #MTP_ERROR_NOT_COMM_INITIALIZED MTP communication is not initiatlized
 * @retval #MTP_ERROR_COMM MTP communication error
 * @retval #MTP_ERROR_CONTROLLER MTP controller error
 * @retval #MTP_ERROR_ALLOC_FAIL Memory Allocation failed
 * @retval #MTP_ERROR_NO_DEVICE MTP have not any device
 * @retval #MTP_ERROR_PLUGIN Plugin failed
 *
 * @param [in] mtp_device The MTP device
 * @param [in] object_handle The object handle
 * @param [out] height The thumbnail pixel height of Object information
 *
 * @see mtp_get_object_handles()
 */
MTP_API int mtp_objectinfo_get_thumbnail_pix_height(mtp_device_h mtp_device, mtp_object_h object_handle, int *height);

/**
 * @brief Gets the thumbnail pix width of the object information.
 * @since_tizen 3.0
 *
 * @return 0 on success, otherwise a negative error value.
 * @retval #MTP_ERROR_NONE Successful
 * @retval #MTP_ERROR_NOT_SUPPORTED MTP is not supported
 * @retval #MTP_ERROR_NOT_INITIALIZED MTP is not initialized
 * @retval #MTP_ERROR_NOT_ACTIVATED MTP is not activated
 * @retval #MTP_ERROR_INVALID_PARAMETER Invalid parameter
 * @retval #MTP_ERROR_NOT_COMM_INITIALIZED MTP communication is not initiatlized
 * @retval #MTP_ERROR_COMM MTP communication error
 * @retval #MTP_ERROR_CONTROLLER MTP controller error
 * @retval #MTP_ERROR_ALLOC_FAIL Memory Allocation failed
 * @retval #MTP_ERROR_NO_DEVICE MTP have not any device
 * @retval #MTP_ERROR_PLUGIN Plugin failed
 *
 * @param [in] mtp_device The MTP device
 * @param [in] object_handle The object handle
 * @param [out] width The thumbnail pixel width of Object information
 *
 * @see mtp_get_object_handles()
 */
MTP_API int mtp_objectinfo_get_thumbnail_pix_width(mtp_device_h mtp_device, mtp_object_h object_handle, int *width);

/**
* @}
*/

#ifdef __cplusplus
}
#endif

#endif
