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

#ifndef __MTP_DEBUG_H__
#define __MTP_DEBUG_H__

#include <stdio.h>

#define COLOR_BLACK "\033[0;30m"
#define COLOR_RED   "\033[0;31m"
#define COLOR_GREEN "\033[0;32m"
#define COLOR_BROWN "\033[0;33m"
#define COLOR_BLUE  "\033[0;34m"
#define COLOR_PURPLE    "\033[0;35m"
#define COLOR_CYAN  "\033[0;36m"
#define COLOR_GRAY  "\033[0;37m"
#define COLOR_END   "\033[0;m"

#define _ERR(fmt, ...) \
	do \
	{ \
		LOGE(COLOR_RED fmt COLOR_END, ##__VA_ARGS__); \
	} \
	while (0)

#define _INFO(fmt, ...) \
	do \
	{ \
		LOGI(COLOR_GREEN fmt COLOR_END, ##__VA_ARGS__); \
	} \
	while (0)

#define _WARN(fmt, ...) \
	do \
	{ \
		LOGI(COLOR_BROWN fmt COLOR_END, ##__VA_ARGS__); \
	} \
	while (0)

#define _DBG(fmt, ...) \
	do \
	{ \
		LOGD(fmt, ##__VA_ARGS__); \
	} \
	while (0)

#define _BEGIN() \
	do \
	{ \
		LOGD(COLOR_BLUE "BEGIN >>>>" COLOR_END); \
	} \
	while (0)

#define _END() \
	do \
	{ \
		LOGD(COLOR_BLUE "END <<<<" COLOR_END); \
	} \
	while (0)

#define cond_expr_ret(expr, val) \
	do {\
		if (expr) { \
			_ERR("[precond fail] expr : %s, ret : %d\n", #expr, val); \
			return (val); \
		} \
	} while(0)

#define cond_ret(val) \
	do {\
		if(val) { \
			_ERR("[precond fail] ret : %d\n", val); \
			return (val); \
		} \
	} while(0)

#define PRT(format, args...) printf("%s:%d() "format, __FUNCTION__, __LINE__, ##args)
#define TC_PRT(format, args...) PRT(format"\n", ##args)

#endif