/*
 * Copyright (c) 2014 Samsung Electronics Co., Ltd.
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

/**
 * @defgroup	CAPI_NETWORK_MTP_MODULE MTP
 * @brief	The MTP API provides functions for support PTP(Picture Transfer Protocol) subset of MTP(Media Transfer Protocol).
 * @ingroup	CAPI_NETWORK_FRAMEWORK
 * @section	CAPI_NETWORK_MTP_MODULE_OVERVIEW Overview
 * <table>
 *	<tr>
 *		<th> API </th>
 *		<th> Description </th>
 *	</tr>
 *	<tr>
 *		<td> @ref CAPI_NETWORK_MTP_MANAGER_MODULE</td>
 *		<td> Provide functions to establish connection to access MTP responder device, and to Get/Delete files</td>
 *	</tr>
 *	<tr>
 *		<td> @ref CAPI_NETWORK_MTP_DEVICE_INFO_MODULE</td>
 *		<td> Provide functions to gets the device information of MTP responder device</td>
 *	</tr>
 *	<tr>
 *		<td> @ref CAPI_NETWORK_MTP_STORAGE_INFO_MODULE</td>
 *		<td> Provide functions to gets the storage information of MTP responder storage</td>
 *	</tr>
 *	<tr>
 *		<td> @ref CAPI_NETWORK_MTP_OBJECT_INFO_MODULE</td>
 *		<td> Provide functions to gets the object information of certain file in MTP responder</td>
 *	</tr>
 * </table>
 **/

/**
 * @ingroup	CAPI_NETWORK_MTP_MODULE
 * @defgroup	CAPI_NETWORK_MTP_MANAGER_MODULE MTP Manager
 * @brief	The MTP Manager API provides functions for establish connection to access MTP responder device, and to Get/Delete files.
 * @section	CAPI_NETWORK_MTP_MANAGER_MODULE_HEADER Required Header
 *	\#include <mtp.h>
 * @section	CAPI_NETWORK_MTP_MANAGER_MODULE_OVERVIEW Overview
 * The MTP manager api provides following functions :\n
 * - Create / destroy connection to access MTP responder device\n
 * - Get Device list\n
 * - Get Storage list\n
 * - Get Object handles\n
 * - Get thumbnail\n
 * - Get Object\n
 * - Delete Object\n
 * @section	CAPI_NETWORK_MTP_MANAGER_MODULE_FEATURE Related Features
 * This API is related with the following features:\n
 * - http://tizen.org/feature/network.mtp\n
 **/

/* 
 * @ingroup	CAPI_NETWORK_MTP_MODULE
 * @defgroup	CAPI_NETWORK_MTP_DEVICE_INFO_MODULE MTP Device Information
 * @brief	The MTP Device Information API provides functions for gets the device information of MTP responder device.
 * @section	CAPI_NETWORK_MTP_DEVICE_INFO_MODULE_HEADER Required Header
 * \#include <mtp.h>
 * @section	CAPI_NETWORK_MTP_DEVICE_INFO_MODULE_OVERVIEW Overview
 * The MTP Device Information api provides following functions :\n
 * - Get device manufacturer name
 * - Get device model name
 * - Get device serial number
 * - Get dievce version
 * @section	CAPI_NETWORK_MTP_DEVICE_INFO_MODULE_FEATURE Related Features
 * This API is related with the following features:\n
 * - http://tizen.org/feature/network.mtp\n
 **/

/*
 * @ingroup	CAPI_NETWORK_MTP_MODULE
 * @defgroup	CAPI_NETWORK_MTP_STORAGE_INFO_MODULE MTP Storage Information
 * @brief	The MTP Storage Information API provides functions for gets the storage information of MTP responder storage.
 * @section	CAPI_NETWORK_MTP_STORAGE_INFO_MODULE_HEADER Required Header
 * \#include <mtp.h>
 * @section	CAPI_NETWORK_MTP_STORAGE_INFO_MODULE_OVERVIEW Overview
 * The MTP Storage Information api provides following functions :\n
 * - Get storage freespace
 * - Get storage description
 * - Get storage type
 * - and, more storage information
 * @section	CAPI_NETWORK_MTP_STORAGE_INFO_MODULE_FEATURE Related Features
 * This API is related with the following features:\n
 * - http://tizen.org/feature/network.mtp\n
 **/

/*
 * @ingroup	CAPI_NETWORK_MTP_MODULE
 * @defgroup	CAPI_NETWORK_MTP_OBJECT_INFO_MODULE MTP Object Information
 * @brief	The MTP Manager API provides functions for gets the object information of certain file in MTP responder.
 * @section	CAPI_NETWORK_MTP_OBJECT_INFO_MODULE_HEADER Required Header
 * \#include <mtp.h>
 * @section	CAPI_NETWORK_MTP_OBJECT_INFO_MODULE_OVERVIEW Overview
 * The MTP Object Information api provides following functions :\n
 * - Get object format
 * - Get object name
 * - Get object size
 * - and, more object information
 * @section	CAPI_NETWORK_MTP_OBJECT_INFO_MODULE_FEATURE Related Features
 * This API is related with the following features:\n
 * - http://tizen.org/feature/network.mtp\n
 **/
