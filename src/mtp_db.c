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

#include "mtp_db.h"

#define  MTP_DB_LOCK				\
	do {							\
		pthread_mutex_lock(&mutex);	\
	} while (0);

#define  MTP_DB_UNLOCK					\
	do {								\
		pthread_mutex_unlock(&mutex);	\
	} while (0);

static pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
static sqlite3 *db;
int ref_count;

mtp_error_e mtp_db_init()
{
	int ret = MTP_ERROR_NONE;
	int sql_ret;

	MTP_DB_LOCK;

	if (ref_count > 0) {
		ref_count++;
	} else if (db == NULL) {
		sql_ret = sqlite3_open_v2(MTP_DB_FILE, &db,
			SQLITE_OPEN_NOMUTEX | SQLITE_OPEN_READWRITE | SQLITE_OPEN_CREATE, NULL);

		if (sql_ret == SQLITE_OK)
			ref_count++;
		else
			ret = MTP_ERROR_DB;
	}

	MTP_DB_UNLOCK;

	return ret;
}

mtp_error_e mtp_db_get_object_info(int device_handle, int object_handle, mtp_object_info** object_info)
{
	int ret = MTP_ERROR_NONE;
	int sql_ret;
	char *sql = NULL;
	sqlite3_stmt *stmt = NULL;

	MTP_DB_LOCK;

	if (db == NULL) {
		MTP_DB_UNLOCK;
		return MTP_ERROR_DB;
	}

	*object_info = (mtp_object_info *)malloc(sizeof(mtp_object_info));

	sql = sqlite3_mprintf("SELECT * FROM %s WHERE device_handle=%d and object_handle=%d;",
		MTP_DB_TABLE, device_handle, object_handle);

	if (sql != NULL && (*object_info) != NULL) {
		sql_ret = sqlite3_prepare_v2(db, sql, strlen(sql), &stmt, NULL);
		if (stmt != NULL) {
			sql_ret = sqlite3_step(stmt);
			if (sql_ret == SQLITE_ROW) {
				(*object_info)->StorageID = sqlite3_column_int(stmt, 2);
				(*object_info)->ObjectFormat = sqlite3_column_int(stmt, 4);
				(*object_info)->ProtectionStatus = sqlite3_column_int(stmt, 5);
				(*object_info)->ObjectCompressedSize = sqlite3_column_int(stmt, 6);
				(*object_info)->ThumbFormat = sqlite3_column_int(stmt, 7);
				(*object_info)->ThumbCompressedSize = sqlite3_column_int(stmt, 8);
				(*object_info)->ThumbPixWidth = sqlite3_column_int(stmt, 9);
				(*object_info)->ThumbPixHeight = sqlite3_column_int(stmt, 10);
				(*object_info)->ImagePixWidth = sqlite3_column_int(stmt, 11);
				(*object_info)->ImagePixHeight = sqlite3_column_int(stmt, 12);
				(*object_info)->ImageBitDepth = sqlite3_column_int(stmt, 13);
				(*object_info)->ParentObject = sqlite3_column_int(stmt, 14);
				(*object_info)->AssociationType = sqlite3_column_int(stmt, 15);
				(*object_info)->AssociationDesc = sqlite3_column_int(stmt, 16);
				(*object_info)->SequenceNumber = sqlite3_column_int(stmt, 17);
				(*object_info)->Filename = g_strdup((const char*)sqlite3_column_text(stmt, 18));
				(*object_info)->CaptureDate = sqlite3_column_int(stmt, 19);
				(*object_info)->ModificationDate = sqlite3_column_int(stmt, 20);
				(*object_info)->Keywords = NULL;
			} else {
				ret = MTP_ERROR_DB;
			}
		} else {
			ret = MTP_ERROR_DB;
		}
	} else {
		ret = MTP_ERROR_DB;
	}

	if (stmt != NULL)
		sqlite3_finalize(stmt);

	if (sql != NULL)
		sqlite3_free(sql);

	MTP_DB_UNLOCK;

	return ret;
}

mtp_error_e mtp_db_deinit()
{
	int ret = MTP_ERROR_NONE;
	int sql_ret;

	MTP_DB_LOCK;

	if (ref_count > 0)
		ref_count--;

	if (db != NULL && ref_count == 0) {
		sql_ret = sqlite3_close(db);

		if (sql_ret != SQLITE_OK)
			ret = MTP_ERROR_DB;

		db = NULL;
	}

	MTP_DB_UNLOCK;

	return ret;
}
