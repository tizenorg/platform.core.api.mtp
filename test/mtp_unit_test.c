#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <glib.h>
#include <sys/time.h>

#include <mtp.h>
#include <mtp_internal.h>

#define BUFFER_LEN 100
#define TEST_CASE_MAX 39
#define TEST_LIST_MAX 20

#define PRT(format, args...) printf("%s:%d() "format, __FUNCTION__, __LINE__, ##args)
#define TC_PRT(format, args...) PRT(format"\n", ##args)

#define BEGIN() TC_PRT("BEGIN >>>>");
#define END() TC_PRT("END <<<<");

static mtp_device_h mtp_device;
static mtp_storage_h mtp_storage = 0;
static mtp_object_h mtp_object = 0;
static mtp_object_h* mtp_objects;
int obj_count;

GMainLoop *main_loop = NULL;

typedef struct {
	const char *tc_name;
	int tc_code;
	int (*tc_func)(void);
} tc_table_t;


static bool test_get_user_int(const char *msg, int *num)
{
	if (msg == NULL || num == NULL)
		return false;

	int rv;
	char buf[32] = { 0, };
	printf("%s\n", msg);
	rv = read(0, buf, 32);

	if (rv < 0 || *buf == 0 || *buf == '\n' || *buf == '\r')
		return false;

	*num = atoi(buf);
	return true;
}

static bool test_get_user_string(const char *msg, char *buf, int buf_size)
{
	if (msg == NULL || buf == NULL || buf_size < 2)
		return false;

	int rv;
	printf("%s\n", msg);
	memset(buf, 0, buf_size);
	rv = read(0, buf, buf_size - 1);

	if (rv < 0 || buf[0] == '\0' || buf[0] == '\n' || buf[0] == '\r') {
		buf[0] = '\0';
		return false;
	}

	if (rv >= 0)
		buf[rv] = '\0';

	return true;
}

static char *test_filetype_to_string(int type)
{
	switch (type) {
	case MTP_FILETYPE_FOLDER:				return "MTP_FILETYPE_FOLDER";
	case MTP_FILETYPE_WAV:					return "MTP_FILETYPE_WAV";
	case MTP_FILETYPE_MP3:					return "MTP_FILETYPE_MP3";
	case MTP_FILETYPE_WMA:					return "MTP_FILETYPE_WMA";
	case MTP_FILETYPE_OGG:					return "MTP_FILETYPE_OGG";
	case MTP_FILETYPE_AUDIBLE:				return "MTP_FILETYPE_AUDIBLE";
	case MTP_FILETYPE_MP4:					return "MTP_FILETYPE_MP4";
	case MTP_FILETYPE_UNDEF_AUDIO:			return "MTP_FILETYPE_UNDEF_AUDIO";
	case MTP_FILETYPE_WMV:					return "MTP_FILETYPE_WMV";
	case MTP_FILETYPE_AVI:					return "MTP_FILETYPE_AVI";
	case MTP_FILETYPE_MPEG:					return "MTP_FILETYPE_MPEG";
	case MTP_FILETYPE_ASF:					return "MTP_FILETYPE_ASF";
	case MTP_FILETYPE_QT:					return "MTP_FILETYPE_QT";
	case MTP_FILETYPE_UNDEF_VIDEO:			return "MTP_FILETYPE_UNDEF_VIDEO";
	case MTP_FILETYPE_JPEG:					return "MTP_FILETYPE_JPEG";
	case MTP_FILETYPE_JFIF:					return "MTP_FILETYPE_JFIF";
	case MTP_FILETYPE_TIFF:					return "MTP_FILETYPE_TIFF";
	case MTP_FILETYPE_BMP:					return "MTP_FILETYPE_BMP";
	case MTP_FILETYPE_GIF:					return "MTP_FILETYPE_GIF";
	case MTP_FILETYPE_PICT:					return "MTP_FILETYPE_PICT";
	case MTP_FILETYPE_PNG:					return "MTP_FILETYPE_PNG";
	case MTP_FILETYPE_VCALENDAR1:			return "MTP_FILETYPE_VCALENDAR1";
	case MTP_FILETYPE_VCALENDAR2:			return "MTP_FILETYPE_VCALENDAR2";
	case MTP_FILETYPE_VCARD2:				return "MTP_FILETYPE_VCARD2";
	case MTP_FILETYPE_VCARD3:				return "MTP_FILETYPE_VCARD3";
	case MTP_FILETYPE_WINDOWSIMAGEFORMAT:	return "MTP_FILETYPE_WINDOWSIMAGEFORMAT";
	case MTP_FILETYPE_WINEXEC:				return "MTP_FILETYPE_WINEXEC";
	case MTP_FILETYPE_TEXT:					return "MTP_FILETYPE_TEXT";
	case MTP_FILETYPE_HTML:					return "MTP_FILETYPE_HTML";
	case MTP_FILETYPE_FIRMWARE:				return "MTP_FILETYPE_FIRMWARE";
	case MTP_FILETYPE_AAC:					return "MTP_FILETYPE_AAC";
	case MTP_FILETYPE_MEDIACARD:			return "MTP_FILETYPE_MEDIACARD";
	case MTP_FILETYPE_FLAC:					return "MTP_FILETYPE_FLAC";
	case MTP_FILETYPE_MP2:					return "MTP_FILETYPE_MP2";
	case MTP_FILETYPE_M4A:					return "MTP_FILETYPE_M4A";
	case MTP_FILETYPE_DOC:					return "MTP_FILETYPE_DOC";
	case MTP_FILETYPE_XML:					return "MTP_FILETYPE_XML";
	case MTP_FILETYPE_XLS:					return "MTP_FILETYPE_XLS";
	case MTP_FILETYPE_PPT:					return "MTP_FILETYPE_PPT";
	case MTP_FILETYPE_MHT:					return "MTP_FILETYPE_MHT";
	case MTP_FILETYPE_JP2:					return "MTP_FILETYPE_JP2";
	case MTP_FILETYPE_JPX:					return "MTP_FILETYPE_JPX";
	case MTP_FILETYPE_ALBUM:				return "MTP_FILETYPE_ALBUM";
	case MTP_FILETYPE_PLAYLIST:				return "MTP_FILETYPE_PLAYLIST";
	case MTP_FILETYPE_UNKNOWN:				return "MTP_FILETYPE_UNKNOWN";
	default:								return "Not Supported type!!!";
	}
}

int manager_test_initialize(void)
{
	int ret = 0;

	BEGIN();

	ret = mtp_initialize();

	if (ret == MTP_ERROR_NONE)
		TC_PRT("Initialize successful");
	else
		TC_PRT("Initialize failed, ret [%d]", ret);

	END();
	return ret;
}

int manager_test_get_raw_devices(void)
{
	int ret = 0;
	int i;
	mtp_raw_device_h *raw_devices = NULL;
	int device_count;

	BEGIN();

	ret = mtp_get_raw_devices(&raw_devices, &device_count);
	TC_PRT("ret[%d]: device_num[%d]", ret, device_count);

	if (ret == MTP_ERROR_NONE) {
		for (i = 0; i < device_count; i++) {
			int bus_location;
			int device_number;
			char *device_name = NULL;
			mtp_get_bus_location(raw_devices[i], &bus_location);
			mtp_get_device_number(raw_devices[i], &device_number);
			mtp_get_device_name(raw_devices[i], &device_name);
			TC_PRT("device bus_location[%d], dev_no [%d], model_name[%s]",
				bus_location, device_number, device_name);
		}
	} else {
		TC_PRT("get device list failed, ret[%d]", ret);
	}

	END();
	return ret;
}

int manager_test_get_device(void)
{
	int ret = 0;
	int bus_location = 0;
	int device_number = 0;
	int device_count;
	mtp_raw_device_h *raw_devices = NULL;

	BEGIN();

	ret = mtp_get_raw_devices(&raw_devices, &device_count);

	if (ret != MTP_ERROR_NONE) {
		TC_PRT("mtp_get_raw_devices is failed!!!");
		return -1;
	}

	if (device_count == 0) {
		TC_PRT("device is not exist!!!");
		END();
		return -1;
	}

	TC_PRT("Select first device");

	mtp_get_bus_location(raw_devices[0], &bus_location);
	mtp_get_device_number(raw_devices[0], &device_number);

	TC_PRT("bus location : %d, device_number : %d", bus_location, device_number);

	ret = mtp_get_device(bus_location, device_number, &mtp_device);
	TC_PRT("ret[%d]: 1st mtp device [%d]", ret, mtp_device);

	END();
	return ret;
}

int manager_test_get_storages(void)
{
	int i;
	int ret = 0;
	int bus_location = 0;
	int device_number = 0;
	int device_count;
	int storage_count;
	mtp_raw_device_h *raw_devices = NULL;
	mtp_storage_h *mtp_storages = NULL;

	ret = mtp_get_raw_devices(&raw_devices, &device_count);

	if (ret != MTP_ERROR_NONE) {
		TC_PRT("mtp_get_raw_devices is failed!!!");
		return -1;
	}

	if (device_count == 0) {
		TC_PRT("device is not exist!!!");
		END();
		return -1;
	}

	TC_PRT("Select first device");

	mtp_get_bus_location(raw_devices[0], &bus_location);
	mtp_get_device_number(raw_devices[0], &device_number);

	TC_PRT("bus location : %d, device_number : %d", bus_location, device_number);

	ret = mtp_get_device(bus_location, device_number, &mtp_device);
	TC_PRT("ret[%d]: 1st mtp device [%d]", ret, mtp_device);

	ret = mtp_get_storages(mtp_device, &mtp_storages, &storage_count);
	TC_PRT("ret[%d]: storage_count[%d]", ret, storage_count);

	if (storage_count == 0) {
		TC_PRT("storage is not exist!!!");
		END();
		return -1;
	}

	ret = mtp_destroy_raw_devices(raw_devices);
	TC_PRT("ret[%d]: mtp_destroy_raw_devices", ret);


	for (i = 0; i < storage_count; i++)
		TC_PRT("mtp storage %d [%d]", i, mtp_storages[i]);

	mtp_storage = mtp_storages[0];

	END();
	return ret;
}

int manager_test_get_object_handles(void)
{
	int ret = 0;
	int i;
	int input_int = 0;
	int *folder_list;
	int folder_count = 0;
	int *file_list;
	int file_count = 0;
	mtp_filetype_e filetype = MTP_FILETYPE_FOLDER;
	char *filename = NULL;
	int folder_max = 0;
	int file_max = 0;
	int list_max = 0;
	BEGIN();

	ret = mtp_get_object_handles(mtp_device, mtp_storage, MTP_FILETYPE_FOLDER, mtp_object, &folder_list, &folder_count);
	TC_PRT("ret[%d]: total folder_count[%d]", ret, folder_count);

	folder_max = (folder_count < TEST_LIST_MAX) ? folder_count : TEST_LIST_MAX;

	for (i = 0; i < folder_max; i++) {
		ret = mtp_objectinfo_get_file_name(mtp_device, folder_list[i], &filename);
		ret = mtp_objectinfo_get_file_type(mtp_device, folder_list[i], &filetype);
		TC_PRT("ret[%d]: object id[%d] - filename[%s], filetype[%s]",
			ret, folder_list[i], filename, test_filetype_to_string(filetype));
	}

	ret = mtp_get_object_handles(mtp_device, mtp_storage, MTP_FILETYPE_JPEG, mtp_object, &file_list, &file_count);
	TC_PRT("ret[%d]: total file_count[%d]", ret, file_count);

	file_max = (file_count < TEST_LIST_MAX) ? file_count : TEST_LIST_MAX;

	for (i = 0; i < file_max; i++) {
		ret = mtp_objectinfo_get_file_name(mtp_device, file_list[i], &filename);
		ret = mtp_objectinfo_get_file_type(mtp_device, file_list[i], &filetype);
		TC_PRT("ret[%d]: object id[%d] - filename[%s], filetype[%s]",
			ret, file_list[i], filename, test_filetype_to_string(filetype));
	}

	if (!test_get_user_int("==> Select Object Type(FOLDER:0, JPEG:14)"
			" - (Enter for skip) :", &input_int)) {
		TC_PRT("select default : folder[%d]", input_int);
	}

	ret = mtp_get_object_handles(mtp_device, mtp_storage, input_int, mtp_object, &mtp_objects, &obj_count);

	TC_PRT("ret[%d]: total object_num[%d]", ret, obj_count);

	list_max = (obj_count < TEST_LIST_MAX) ? obj_count : TEST_LIST_MAX;

	for (i = 0; i < list_max; i++) {
		ret = mtp_objectinfo_get_file_name(mtp_device, mtp_objects[i], &filename);
		ret = mtp_objectinfo_get_file_type(mtp_device, mtp_objects[i], &filetype);
		TC_PRT("ret[%d]: object id[%d] - filename[%s], filetype[%s]",
			ret, mtp_objects[i], filename, test_filetype_to_string(filetype));
	}

	if (input_int == MTP_FILETYPE_FOLDER) {
		if (!test_get_user_int("==> Input Object ID :", &mtp_object)) {
			TC_PRT("invalid input !!![%d]", mtp_object);
			mtp_object = 0;
			END();
			return -1;
		}
		TC_PRT("selected object id[%d]", mtp_object);
		TC_PRT("===== Object List - Folder =====");
	} else {
		TC_PRT("===== Object List -   JPEG =====");
	}

	END();
	return ret;
}

int manager_test_delete_object(void)
{
	int ret = 0;
	int i;
	int input_int = 0;
	mtp_filetype_e filetype = MTP_FILETYPE_JPEG;
	char *filename = NULL;
	int list_max = 0;
	BEGIN();

	TC_PRT("total object_num[%d]", obj_count);

	list_max = (obj_count < TEST_LIST_MAX) ? obj_count : TEST_LIST_MAX;

	for (i = 0; i < list_max; i++) {
		ret = mtp_objectinfo_get_file_name(mtp_device, mtp_objects[i], &filename);
		ret = mtp_objectinfo_get_file_type(mtp_device, mtp_objects[i], &filetype);
		TC_PRT("ret[%d]: object id[%d] - filename[%s], filetype[%s]",
			ret, mtp_objects[i], filename, test_filetype_to_string(filetype));
	}

	if (!test_get_user_int("==> Input Object ID :", &input_int)) {
		TC_PRT("Invalid Input !!![%d]", input_int);
		END();
		return -1;
	}

	ret = mtp_delete_object(mtp_device, input_int);
	TC_PRT("ret[%d]: input id[%d]", ret, input_int);

	END();
	return ret;
}

int manager_test_get_object(void)
{
	int ret = 0;
	int i;
	int input_int = 0;
	mtp_filetype_e filetype = MTP_FILETYPE_JPEG;
	char *filename = NULL;
	char filepath[100] = {0,};
	int list_max = 0;
	BEGIN();

	TC_PRT("total object_num[%d]", obj_count);

	list_max = (obj_count < TEST_LIST_MAX) ? obj_count : TEST_LIST_MAX;

	for (i = 0; i < list_max; i++) {
		ret = mtp_objectinfo_get_file_name(mtp_device, mtp_objects[i], &filename);
		ret = mtp_objectinfo_get_file_type(mtp_device, mtp_objects[i], &filetype);
		TC_PRT("ret[%d]: object id[%d] - filename[%s], filetype[%s]",
			ret, mtp_objects[i], filename, test_filetype_to_string(filetype));
	}

	if (!test_get_user_int("==> Input Object ID :", &input_int)) {
		TC_PRT("Invalid Input !!![%d]", input_int);
		END();
		return -1;
	}

	snprintf(filepath, 100, "/opt/usr/media/Downloads/JpegObject_%d.jpg", input_int);

	ret = mtp_get_object(mtp_device, input_int, filepath);
	TC_PRT("ret[%d]: input id[%d]", ret, input_int);

	END();
	return ret;
}


int manager_test_get_thumbnail(void)
{
	int i;
	int ret = 0;
	int input_int = 0;
	char input_str[50] = {0, };
	char filepath[100] = {0,};
	mtp_filetype_e filetype = MTP_FILETYPE_JPEG;
	char *filename = NULL;
	int list_max = 0;
	BEGIN();

	TC_PRT("total object_num[%d]", obj_count);

	list_max = (obj_count < TEST_LIST_MAX) ? obj_count : TEST_LIST_MAX;

	for (i = 0; i < list_max; i++) {
		ret = mtp_objectinfo_get_file_name(mtp_device, mtp_objects[i], &filename);
		ret = mtp_objectinfo_get_file_type(mtp_device, mtp_objects[i], &filetype);
		TC_PRT("ret[%d]: object id[%d] - filename[%s], filetype[%s]",
			ret, mtp_objects[i], filename, test_filetype_to_string(filetype));
	}

	if (!test_get_user_int("==> Input JPEG ID :", &input_int)) {
		TC_PRT("Invalid Input !!![%d]", input_int);
		END();
		return -1;
	}

	/* String Input Test */
	if (test_get_user_string("Input Dest File Name(ex - thumbnail or thum)"
		" - (Enter for skip) :", input_str, 50)) {
		g_strstrip(input_str);
	} else {
		TC_PRT("Invalid Input !!![%s]", input_str);
		END();
		return -1;
	}

	snprintf(filepath, 100, "/opt/usr/media/Downloads/%s_%d.jpg", input_str, input_int);

	ret = mtp_get_thumbnail(mtp_device, input_int, filepath);
	TC_PRT("ret[%d]: input jpeg id[%d], input file path[%s]", ret, input_int, filepath);

	END();
	return ret;
}

int manager_test_deinitialize(void)
{
	int ret = 0;
	BEGIN();

	ret = mtp_deinitialize();
	TC_PRT("ret[%d] : deinitialize", ret);

	END();
	return ret;
}

int deviceinfo_test_get_manufacturername(void)
{
	int ret = 0;
	char *name = NULL;
	BEGIN();

	ret = mtp_deviceinfo_get_manufacturer_name(mtp_device, &name);
	TC_PRT("ret[%d]: manufacturername[%s]", ret, name);

	END();
	return ret;
}

int deviceinfo_test_get_modelname(void)
{
	int ret = 0;
	char *name = NULL;
	BEGIN();

	ret = mtp_deviceinfo_get_model_name(mtp_device, &name);
	TC_PRT("ret[%d]: modelname[%s]", ret, name);

	END();
	return ret;
}

int deviceinfo_test_get_serialnumber(void)
{
	int ret = 0;
	char *name = NULL;
	BEGIN();

	ret = mtp_deviceinfo_get_serial_number(mtp_device, &name);
	TC_PRT("ret[%d]: serialnumber[%s]", ret, name);

	END();
	return ret;
}

int deviceinfo_test_get_deviceversion(void)
{
	int ret = 0;
	char *name = NULL;
	BEGIN();

	ret = mtp_deviceinfo_get_device_version(mtp_device, &name);
	TC_PRT("ret[%d]: deviceversion[%s]", ret, name);

	END();
	return ret;
}


int storageinfo_test_get_description(void)
{
	int ret = 0;
	char *name = NULL;
	BEGIN();

	ret = mtp_storageinfo_get_description(mtp_device, mtp_storage, &name);
	TC_PRT("ret[%d]: description[%s]", ret, name);

	END();
	return ret;
}

int storageinfo_test_get_freespace(void)
{
	int ret = 0;
	unsigned long long value = 0;
	BEGIN();

	ret = mtp_storageinfo_get_free_space(mtp_device, mtp_storage, &value);
	TC_PRT("ret[%d]: freespace[%llu]", ret, value);

	END();
	return ret;
}

int storageinfo_test_get_maxcapacity(void)
{
	int ret = 0;
	unsigned long long value = 0;
	BEGIN();

	ret = mtp_storageinfo_get_max_capacity(mtp_device, mtp_storage, &value);
	TC_PRT("ret[%d]: maxcapacity[%llu]", ret, value);

	END();
	return ret;
}

int storageinfo_test_get_storagetype(void)
{
	int ret = 0;
	mtp_storage_type_e value = 0;
	BEGIN();

	ret = mtp_storageinfo_get_storage_type(mtp_device, mtp_storage, &value);
	TC_PRT("ret[%d]: storagetype[%d]", ret, value);

	END();
	return ret;
}

int storageinfo_test_get_volumeidentifier(void)
{
	int ret = 0;
	char *name = NULL;
	BEGIN();

	ret = mtp_storageinfo_get_volume_identifier(mtp_device, mtp_storage, &name);
	TC_PRT("ret[%d]: volumeidentifier[%s]", ret, name);

	END();
	return ret;
}

int objectinfo_test_get_association_desc(void)
{
	int i;
	int ret = 0;
	int value = 0;
	int list_max = 0;
	BEGIN();

	list_max = (obj_count < TEST_LIST_MAX) ? obj_count : TEST_LIST_MAX;

	for (i = 0; i < list_max; i++) {
		ret = mtp_objectinfo_get_association_desc(mtp_device, mtp_objects[i], &value);
		TC_PRT("ret[%d]: object id[%d] association_desc[%d]", ret, mtp_objects[i], value);
	}

	END();
	return ret;
}

int objectinfo_test_get_association_type(void)
{
	int i;
	int ret = 0;
	int value = 0;
	int list_max = 0;
	BEGIN();

	list_max = (obj_count < TEST_LIST_MAX) ? obj_count : TEST_LIST_MAX;

	for (i = 0; i < list_max; i++) {
		ret = mtp_objectinfo_get_association_type(mtp_device, mtp_objects[i], &value);
		TC_PRT("ret[%d]: object id[%d] association_type[%d]", ret, mtp_objects[i], value);
	}

	END();
	return ret;
}

int objectinfo_test_get_size(void)
{
	int i;
	int ret = 0;
	int value = 0;
	int list_max = 0;
	BEGIN();

	list_max = (obj_count < TEST_LIST_MAX) ? obj_count : TEST_LIST_MAX;

	for (i = 0; i < list_max; i++) {
		ret = mtp_objectinfo_get_size(mtp_device, mtp_objects[i], &value);
		TC_PRT("ret[%d]: object id[%d] size[%d]", ret, mtp_objects[i], value);
	}

	END();
	return ret;
}

int objectinfo_test_get_parent_object_handle(void)
{
	int i;
	int ret = 0;
	int value = 0;
	int list_max = 0;
	BEGIN();

	list_max = (obj_count < TEST_LIST_MAX) ? obj_count : TEST_LIST_MAX;

	for (i = 0; i < list_max; i++) {
		ret = mtp_objectinfo_get_parent_object_handle(mtp_device, mtp_objects[i], &value);
		TC_PRT("ret[%d]: object id[%d] parent_object_handle[%d]", ret, mtp_objects[i], value);
	}

	END();
	return ret;
}

int objectinfo_test_get_storage_id(void)
{
	int i;
	int ret = 0;
	int value = 0;
	int list_max = 0;
	BEGIN();

	list_max = (obj_count < TEST_LIST_MAX) ? obj_count : TEST_LIST_MAX;

	for (i = 0; i < list_max; i++) {
		ret = mtp_objectinfo_get_storage(mtp_device, mtp_objects[i], &value);
		TC_PRT("ret[%d]: object id[%d] mtp_storage[%d]", ret, mtp_objects[i], value);
	}

	END();
	return ret;
}

int objectinfo_test_get_date_created(void)
{
	int i;
	int ret = 0;
	int value = 0;
	int list_max = 0;
	BEGIN();

	list_max = (obj_count < TEST_LIST_MAX) ? obj_count : TEST_LIST_MAX;

	for (i = 0; i < list_max; i++) {
		ret = mtp_objectinfo_get_date_created(mtp_device, mtp_objects[i], &value);
		TC_PRT("ret[%d]: object id[%d] mtp_device[%d]", ret, mtp_objects[i], value);
	}

	END();
	return ret;
}

int objectinfo_test_get_date_modified(void)
{
	int i;
	int ret = 0;
	int value = 0;
	int list_max = 0;
	BEGIN();

	list_max = (obj_count < TEST_LIST_MAX) ? obj_count : TEST_LIST_MAX;

	for (i = 0; i < list_max; i++) {
		ret = mtp_objectinfo_get_date_modified(mtp_device, mtp_objects[i], &value);
		TC_PRT("ret[%d]: object id[%d] date_modified[%d]", ret, mtp_objects[i], value);
	}

	END();
	return ret;
}

int objectinfo_test_get_file_type(void)
{
	int i;
	int ret = 0;
	mtp_filetype_e value = 0;
	int list_max = 0;
	BEGIN();

	list_max = (obj_count < TEST_LIST_MAX) ? obj_count : TEST_LIST_MAX;

	for (i = 0; i < list_max; i++) {
		ret = mtp_objectinfo_get_file_type(mtp_device, mtp_objects[i], &value);
		TC_PRT("ret[%d]: object id[%d] file type[%d]", ret, mtp_objects[i], value);
	}

	END();
	return ret;
}

int objectinfo_test_get_image_bit_depth(void)
{
	int i;
	int ret = 0;
	int value = 0;
	int list_max = 0;
	BEGIN();

	list_max = (obj_count < TEST_LIST_MAX) ? obj_count : TEST_LIST_MAX;

	for (i = 0; i < list_max; i++) {
		ret = mtp_objectinfo_get_image_bit_depth(mtp_device, mtp_objects[i], &value);
		TC_PRT("ret[%d]: object id[%d] image_bit_depth[%d]", ret, mtp_objects[i], value);
	}

	END();
	return ret;
}

int objectinfo_test_get_image_pix_width(void)
{
	int i;
	int ret = 0;
	int value = 0;
	int list_max = 0;
	BEGIN();

	list_max = (obj_count < TEST_LIST_MAX) ? obj_count : TEST_LIST_MAX;

	for (i = 0; i < list_max; i++) {
		ret = mtp_objectinfo_get_image_pix_width(mtp_device, mtp_objects[i], &value);
		TC_PRT("ret[%d]: object id[%d] image_pix_width[%d]", ret, mtp_objects[i], value);
	}

	END();
	return ret;
}

int objectinfo_test_get_image_pix_height(void)
{
	int i;
	int ret = 0;
	int value = 0;
	int list_max = 0;
	BEGIN();

	list_max = (obj_count < TEST_LIST_MAX) ? obj_count : TEST_LIST_MAX;

	for (i = 0; i < list_max; i++) {
		ret = mtp_objectinfo_get_image_pix_height(mtp_device, mtp_objects[i], &value);
		TC_PRT("ret[%d]: object id[%d] image_pix_height[%d]", ret, mtp_objects[i], value);
	}

	END();
	return ret;
}

int objectinfo_test_get_thumbnail_size(void)
{
	int i;
	int ret = 0;
	int value = 0;
	int list_max = 0;
	BEGIN();

	list_max = (obj_count < TEST_LIST_MAX) ? obj_count : TEST_LIST_MAX;

	for (i = 0; i < list_max; i++) {
		ret = mtp_objectinfo_get_thumbnail_size(mtp_device, mtp_objects[i], &value);
		TC_PRT("ret[%d]: object id[%d] thumbnail_size[%d]", ret, mtp_objects[i], value);
	}

	END();
	return ret;
}

int objectinfo_test_get_thumbnail_file_type(void)
{
	int i;
	int ret = 0;
	mtp_filetype_e value = 0;
	int list_max = 0;
	BEGIN();

	list_max = (obj_count < TEST_LIST_MAX) ? obj_count : TEST_LIST_MAX;

	for (i = 0; i < list_max; i++) {
		ret = mtp_objectinfo_get_thumbnail_file_type(mtp_device, mtp_objects[i], &value);
		TC_PRT("ret[%d]: object id[%d] thumbnail_format[%d]", ret, mtp_objects[i], value);
	}

	END();
	return ret;
}

int objectinfo_test_get_thumbnail_pix_height(void)
{
	int i;
	int ret = 0;
	int value = 0;
	int list_max = 0;
	BEGIN();

	list_max = (obj_count < TEST_LIST_MAX) ? obj_count : TEST_LIST_MAX;

	for (i = 0; i < list_max; i++) {
		ret = mtp_objectinfo_get_thumbnail_pix_height(mtp_device, mtp_objects[i], &value);
		TC_PRT("ret[%d]: object id[%d] thumbnail_pix_height[%d]", ret, mtp_objects[i], value);
	}

	END();
	return ret;
}

int objectinfo_test_get_thumbnail_pix_width(void)
{
	int i;
	int ret = 0;
	int value = 0;
	int list_max = 0;
	BEGIN();

	list_max = (obj_count < TEST_LIST_MAX) ? obj_count : TEST_LIST_MAX;

	for (i = 0; i < list_max; i++) {
		ret = mtp_objectinfo_get_thumbnail_pix_width(mtp_device, mtp_objects[i], &value);
		TC_PRT("ret[%d]: object id[%d] thumbnail_pix_width[%d]", ret, mtp_objects[i], value);
	}

	END();
	return ret;
}

int objectinfo_test_get_filename(void)
{
	int i;
	int ret = 0;
	char *value = NULL;
	int list_max = 0;
	BEGIN();

	list_max = (obj_count < TEST_LIST_MAX) ? obj_count : TEST_LIST_MAX;

	for (i = 0; i < list_max; i++) {
		ret = mtp_objectinfo_get_file_name(mtp_device, mtp_objects[i], &value);
		TC_PRT("ret[%d]: object id[%d] filename[%s]", ret, mtp_objects[i], value);
	}

	END();
	return ret;
}

int objectinfo_test_get_keywords(void)
{
	int i;
	int ret = 0;
	char *value = NULL;
	int list_max = 0;
	BEGIN();

	list_max = (obj_count < TEST_LIST_MAX) ? obj_count : TEST_LIST_MAX;

	for (i = 0; i < list_max; i++) {
		ret = mtp_objectinfo_get_keywords(mtp_device, mtp_objects[i], &value);
		TC_PRT("ret[%d]: object id[%d] keywords[%s]", ret, mtp_objects[i], value);
	}

	END();
	return ret;
}

int application_test_get_image_from_DCIM(void)
{
	int ret = 0;
	int i;
	mtp_filetype_e filetype = MTP_FILETYPE_FOLDER;
	int *object_list;
	int object_count = 0;
	int *object_list2;
	int object_count2 = 0;
	char filepath[100] = {0,};
	char *filename = NULL;
	int selected_id = 0;
	int input_object_id = 0;
	int input_object_id2 = 0;
	BEGIN();

	while (true) {
		TC_PRT("storage_handle : %d", mtp_storage);

		if (!test_get_user_int("==> 1. Select Object type (FOLDER:0, JPEG:14, BMP:17)"
				" - (Enter for skip) :", &input_object_id2)) {
			TC_PRT("Invalid Input !!! [%d]", input_object_id2);
			break;
		}

		ret = mtp_get_object_handles(mtp_device, (mtp_storage > 0 ? mtp_storage : 0), input_object_id2, selected_id, &object_list, &object_count);

		TC_PRT("Total object_num [%d]", object_count);

		for (i = 0; i < object_count; i++) {
			TC_PRT("object handle %d", object_list[i]);

			ret = mtp_objectinfo_get_file_name(mtp_device, object_list[i], &filename);
			ret = mtp_objectinfo_get_file_type(mtp_device, object_list[i], &filetype);

			TC_PRT("ret : %d", ret);
			TC_PRT("Folder object id %d - filename[%s], filetype[%s]\n", object_list[i], filename, test_filetype_to_string(filetype));
		}

		if (!test_get_user_int("==> 1. Input Folder Object ID (Enter for exit):", &input_object_id)) {
			TC_PRT("input_object_id : %d", input_object_id);
			g_free(object_list);
			break;
		}

		selected_id = input_object_id;

		ret = mtp_objectinfo_get_file_name(mtp_device, selected_id, &filename);
		ret = mtp_objectinfo_get_file_type(mtp_device, selected_id, &filetype);

		TC_PRT("ret : %d", ret);
		TC_PRT("selected id[%d] - filename[%s], filetype[%s]\n", selected_id, filename, test_filetype_to_string(filetype));

		g_free(filename);
	}

	ret = mtp_get_object_handles(mtp_device, (mtp_storage > 0 ? mtp_storage : 0), MTP_FILETYPE_JPEG, selected_id, &object_list2, &object_count2);

	TC_PRT("Total object_num [%d]", object_count2);

	for (i = 0; i < object_count2; i++) {
		TC_PRT("object handle %d", object_list2[i]);

		ret = mtp_objectinfo_get_file_name(mtp_device, object_list2[i], &filename);
		ret = mtp_objectinfo_get_file_type(mtp_device, object_list2[i], &filetype);

		TC_PRT("ret : %d", ret);
		TC_PRT("JPEG id[%d] - filename[%s], filetype[%s]\n", object_list2[i], filename, test_filetype_to_string(filetype));
	}

	while (true) {
		if (!test_get_user_int("==> 2. Input JPEG Object ID (Enter for exit):", &input_object_id2)) {
			TC_PRT("input_object_id2 : %d", input_object_id2);
			break;
		}

		ret = mtp_objectinfo_get_file_name(mtp_device, input_object_id2, &filename);
		ret = mtp_objectinfo_get_file_type(mtp_device, input_object_id2, &filetype);

		TC_PRT("ret : %d", ret);
		TC_PRT("selected id[%d] - filename[%s], filetype[%s]\n", input_object_id2, filename, test_filetype_to_string(filetype));

		g_free(filename);

		if (filetype == MTP_FILETYPE_JPEG) {
			snprintf(filepath, 100, "/home/JpegObject_%d.jpg", input_object_id2);

			ret = mtp_get_object(mtp_device, input_object_id2, filepath);
			TC_PRT("mtp_get_object ret : %d", ret);
		}
	}

	END();
	return ret;
}

int application_test_get_object_handle_using_all(void)
{
	int i;
	int ret = 0;
	int *file_list;
	int file_count;

	BEGIN();

	ret = mtp_get_object_handles(mtp_device, mtp_storage, MTP_FILETYPE_ALL, 0, &file_list, &file_count);

	TC_PRT("ret[%d]: total folder_count[%d]", ret, file_count);
	for (i = 0; i < file_count; i++)
		TC_PRT("object handle [%d] : %d", file_count, file_list[i]);

	END();
	return ret;
}

int application_test_get_object_handle_using_all_image(void)
{
	int i;
	int *file_list;
	int file_count;
	int ret = 0;
	BEGIN();

	ret = mtp_get_object_handles(mtp_device, mtp_storage, MTP_FILETYPE_ALL_IMAGE, 0, &file_list, &file_count);

	TC_PRT("ret[%d]: total folder_count[%d]", ret, file_count);
	for (i = 0; i < file_count; i++)
		TC_PRT("object handle [%d] : %d", file_count, file_list[i]);

	END();
	return ret;
}

void __test_mtp_event_cb(mtp_event_e state, int arg, void *user_data)
{
	int ret = 0;

	TC_PRT("state [%d] : %d", state, arg);

	if (state == MTP_EVENT_TURNED_OFF) {
		ret = mtp_deinitialize();
		TC_PRT("ret[%d] : Terminated daemon", ret);
	}
}

int application_test_event_callback(void)
{
	int ret;

	BEGIN();

	ret = mtp_set_mtp_event_cb(__test_mtp_event_cb, NULL);

	END();

	return ret;
}

tc_table_t tc_table[] = {
	/* manager api */
	{"mtp_initialize",							1,	manager_test_initialize},
	{"mtp_get_raw_devices",						2,	manager_test_get_raw_devices},
	{"mtp_get_device",					3,	manager_test_get_device},
	{"mtp_get_storages",						4,	manager_test_get_storages},
	{"mtp_get_object_handles",					5,	manager_test_get_object_handles},
	{"mtp_delete_object",						6,	manager_test_delete_object},
	{"mtp_get_object",							7,	manager_test_get_object},
	{"mtp_get_thumbnail",						8,	manager_test_get_thumbnail},
	{"mtp_deinitialize",						9,	manager_test_deinitialize},

	/* device api */
	{"mtp_deviceinfo_manufacturer_name",		10,	deviceinfo_test_get_manufacturername},
	{"mtp_deviceinfo_model_name",				11,	deviceinfo_test_get_modelname},
	{"mtp_deviceinfo_serial_number",			12,	deviceinfo_test_get_serialnumber},
	{"mtp_deviceinfo_device_version",			13,	deviceinfo_test_get_deviceversion},

	/* storage api */
	{"mtp_storageinfo_get_description",			14,	storageinfo_test_get_description},
	{"mtp_storageinfo_get_freespace",			15,	storageinfo_test_get_freespace},
	{"mtp_storageinfo_get_maxcapacity",			16,	storageinfo_test_get_maxcapacity},
	{"mtp_storageinfo_get_storagetype",			17,	storageinfo_test_get_storagetype},
	{"mtp_storageinfo_get_volumeidentifier",	18,	storageinfo_test_get_volumeidentifier},

	/* object api */
	{"mtp_objectinfo_get_association_desc",		19,	objectinfo_test_get_association_desc},
	{"mtp_objectinfo_get_association_type",		20,	objectinfo_test_get_association_type},
	{"mtp_objectinfo_get_size",					21,	objectinfo_test_get_size},
	{"mtp_objectinfo_get_date_created",			22,	objectinfo_test_get_date_created},
	{"mtp_objectinfo_get_date_modified",		23,	objectinfo_test_get_date_modified},
	{"mtp_objectinfo_get_file_type",				24,	objectinfo_test_get_file_type},
	{"mtp_objectinfo_get_image_pix_depth",		25,	objectinfo_test_get_image_bit_depth},
	{"mtp_objectinfo_get_image_pix_width",		26,	objectinfo_test_get_image_pix_width},
	{"mtp_objectinfo_get_image_pix_height",		27,	objectinfo_test_get_image_pix_height},
	{"mtp_objectinfo_get_thumbnail_size",		28,	objectinfo_test_get_thumbnail_size},
	{"mtp_objectinfo_get_thumbnail_format",		29,	objectinfo_test_get_thumbnail_file_type},
	{"mtp_objectinfo_get_thumbnail_pix_height",	30,	objectinfo_test_get_thumbnail_pix_height},
	{"mtp_objectinfo_get_thumbnail_pix_width",	31,	objectinfo_test_get_thumbnail_pix_width},
	{"mtp_objectinfo_get_filename",				32, objectinfo_test_get_filename},
	{"mtp_objectinfo_get_keywords",				33, objectinfo_test_get_keywords},

	/* application test */
	{"get Jpeg image from /DCIM folder",		34,	application_test_get_image_from_DCIM},
	{"get object handle using ALL file type",		35,	application_test_get_object_handle_using_all},
	{"get object handle using ALL Image file type",		36,	application_test_get_object_handle_using_all_image},
	{"test callback function",		37,	application_test_event_callback},
	{"get object and get thumbnail test",		TEST_CASE_MAX,	NULL},

	/*-----------*/
	{"Finish",									0x0000,	NULL},
	{NULL,										0x00ff,	NULL},
};

static void tc_usage_print(void)
{
	int i = 0;

	while (tc_table[i].tc_name) {
		if (tc_table[i].tc_code != 0x00ff)
			printf("Key [%2d] : usage %s\n", tc_table[i].tc_code, tc_table[i].tc_name);
		else
			printf("Key [%2d] : usage %s\n\n", 0x00ff, tc_table[i].tc_name);

		i++;
	}
}

static int test_input_callback(void *data)
{
	long test_id = (long)data;
	int ret = MTP_ERROR_NONE;

	if ((test_id >= 1) && (test_id <= TEST_CASE_MAX)) {
		TC_PRT("test_input_callback test_id : %ld", test_id);

		if (tc_table[test_id-1].tc_func != NULL) {
			ret = tc_table[test_id-1].tc_func();

			if (ret != MTP_ERROR_NONE)
				TC_PRT(">>>>> Test Error Returned !!! : %d", ret);
		}
	}

	return 0;
}

static int test_mtp_terminate(void)
{
	int ret = 0;

	TC_PRT("Finished");

	manager_test_deinitialize();
	g_main_loop_quit(main_loop);

	return ret;
}

static gboolean key_event_cb(GIOChannel *chan, GIOCondition cond, gpointer data)
{
	char buf[BUFFER_LEN] = {0,};
	long test_id;
	int rv = 0;

	memset(buf, 0, sizeof(buf));
	printf("Event received from stdin\n");

	rv = read(0, buf, 100);

	if (rv < 0 || buf[0] == '0') {
		test_mtp_terminate();
		exit(1);
	}

	if (*buf == '\n' || *buf == '\r')
		tc_usage_print();

	test_id = atoi(buf);

	test_input_callback((void *)test_id);

	return TRUE;
}


int main(int argc, char ** argv)
{
	GIOChannel *key_io;

	main_loop = g_main_loop_new(NULL, FALSE);
	key_io = g_io_channel_unix_new(0);

	printf("Test Thread created...\n");

	g_io_add_watch(key_io, (G_IO_IN | G_IO_HUP | G_IO_ERR | G_IO_NVAL), key_event_cb, NULL);
	g_main_loop_run(main_loop);

	g_io_channel_unref(key_io);
	g_main_loop_unref(main_loop);

	return 0;
}
