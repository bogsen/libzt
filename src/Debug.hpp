/*
 * ZeroTier SDK - Network Virtualization Everywhere
 * Copyright (C) 2011-2019  ZeroTier, Inc.  https://www.zerotier.com/
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program. If not, see <http://www.gnu.org/licenses/>.
 *
 * --
 *
 * You can be released from the requirements of the license by purchasing
 * a commercial license. Buying such a license is mandatory as soon as you
 * develop commercial closed-source software that incorporates or links
 * directly against ZeroTier software without disclosing the source code
 * of your own application.
 */

/**
 * @file
 *
 * Debug macros
 */

#ifndef LIBZT_DEBUG_HPP
#define LIBZT_DEBUG_HPP

//////////////////////////////////////////////////////////////////////////////
// Debugging Macros                                                         //
//////////////////////////////////////////////////////////////////////////////

#if defined(__linux__) || defined(__APPLE__)
#include <sys/syscall.h>
#include <pthread.h>
#include <unistd.h>
#endif
#include <string.h>

#define ZT_MSG_ERROR       true // Errors
#define ZT_MSG_INFO        true // Information which is generally useful to any developer
#define ZT_MSG_TEST        true // For use in selftest
#define ZT_MSG_TRANSFER    true // RX/TX specific statements

#define ZT_COLOR           true

// Debug output colors
#if defined(__APPLE__)
		#include "TargetConditionals.h"
#endif
#if defined(ZT_COLOR) && !defined(_WIN32) && !defined(__ANDROID__) && !defined(TARGET_OS_IPHONE) && !defined(TARGET_IPHONE_SIMULATOR) && !defined(__APP_FRAMEWORK__)
	#define ZT_RED   "\x1B[31m"
	#define ZT_GRN   "\x1B[32m"
	#define ZT_YEL   "\x1B[33m"
	#define ZT_BLU   "\x1B[34m"
	#define ZT_MAG   "\x1B[35m"
	#define ZT_CYN   "\x1B[36m"
	#define ZT_WHT   "\x1B[37m"
	#define ZT_RESET "\x1B[0m"
#else
	#define ZT_RED
	#define ZT_GRN
	#define ZT_YEL
	#define ZT_BLU
	#define ZT_MAG
	#define ZT_CYN
	#define ZT_WHT
	#define ZT_RESET
#endif

#define ZT_FILENAME (strrchr(__FILE__, '/') ? strrchr(__FILE__, '/') + 1 : __FILE__) // short

#if defined(__JNI_LIB__)
		#include <jni.h>
#endif
#if defined(__ANDROID__)
		#include <android/log.h>
		#define ZT_LOG_TAG "ZTSDK"
#endif

#if defined(LIBZT_DEBUG) || defined(LIBZT_TRACE) || defined(__NATIVETEST__)
	//
	#if ZT_MSG_ERROR == true
		#if defined(__ANDROID__)
			#define DEBUG_ERROR(fmt, args...) ((void)__android_log_print(ANDROID_LOG_VERBOSE, ZT_LOG_TAG, \
				"%17s:%5d:%20s: " fmt "\n", ZT_FILENAME, __LINE__, __FUNCTION__, ##args))
		#elif defined(_WIN32)
			#define DEBUG_ERROR(fmt, ...) fprintf(stderr, ZT_RED "%17s:%5d:%25s: " fmt "\n" \
				ZT_RESET, ZT_FILENAME, __LINE__, __FUNCTION__, __VA_ARGS__)
		#else
		#define DEBUG_ERROR(fmt, args ...) fprintf(stderr, ZT_RED "%17s:%5d:%25s: " fmt "\n" \
				ZT_RESET, ZT_FILENAME, __LINE__, __FUNCTION__, ##args)
		#endif
	#else
		#define DEBUG_ERROR(fmt, args...)
	#endif

	//
	#if ZT_MSG_TEST == true
		#if defined(__ANDROID__)
			#define DEBUG_TEST(fmt, args...) ((void)__android_log_print(ANDROID_LOG_VERBOSE, ZT_LOG_TAG, \
				"%17s:%5d:%25s: " fmt "\n", ZT_FILENAME, __LINE__, __FUNCTION__, ##args))
		#elif defined(_WIN32)
			#define DEBUG_TEST(fmt, ...) fprintf(stderr, ZT_CYN "%17s:%5d:%25s: " fmt "\n" \
				ZT_RESET, ZT_FILENAME, __LINE__, __FUNCTION__, __VA_ARGS__)
		#else
		#define DEBUG_TEST(fmt, args ...) fprintf(stderr, ZT_CYN "%17s:%5d:%25s: " fmt "\n" \
				ZT_RESET, ZT_FILENAME, __LINE__, __FUNCTION__, ##args)
		#endif
	#else
		#define DEBUG_TEST(fmt, args...)
	#endif

	//
	#if ZT_MSG_INFO == true
		#if defined(__ANDROID__)
			#define DEBUG_INFO(fmt, args...) ((void)__android_log_print(ANDROID_LOG_VERBOSE, ZT_LOG_TAG, \
				"%17s:%5d:%20s: " fmt "\n", ZT_FILENAME, __LINE__, __FUNCTION__, ##args))
		#elif defined(_WIN32)
			#define DEBUG_INFO(fmt, ...) fprintf(stderr, ZT_WHT "%17s:%5d:%25s: " fmt "\n" \
				ZT_RESET, ZT_FILENAME, __LINE__, __FUNCTION__, __VA_ARGS__)
		#else
			#define DEBUG_INFO(fmt, args ...) fprintf(stderr, ZT_WHT "%17s:%5d:%25s: " fmt "\n" \
				ZT_RESET, ZT_FILENAME, __LINE__, __FUNCTION__, ##args)
		#endif
	#else
		#define DEBUG_INFO(fmt, args...)
	#endif

	//
	#if ZT_MSG_TRANSFER == true
		#if defined(__ANDROID__)
			#define DEBUG_TRANS(fmt, args...) ((void)__android_log_print(ANDROID_LOG_VERBOSE, ZT_LOG_TAG, \
				"%17s:%5d:%25s: " fmt "\n", ZT_FILENAME, __LINE__, __FUNCTION__, ##args))
		#elif defined(_WIN32)
			#define DEBUG_TRANS(fmt, ...) fprintf(stderr, ZT_GRN "%17s:%5d:%25s: " fmt "\n" \
				ZT_RESET, ZT_FILENAME, __LINE__, __FUNCTION__, __VA_ARGS__)
		#else
			#define DEBUG_TRANS(fmt, args ...) fprintf(stderr, ZT_GRN "%17s:%5d:%25s: " fmt "\n" \
				ZT_RESET, ZT_FILENAME, __LINE__, __FUNCTION__, ##args)
		#endif
	#else
		#define DEBUG_TRANS(fmt, args...)
	#endif

#else // !LIBZT_DEBUG || !__NATIVE_TEST__
	#if defined(_WIN32)
		#define DEBUG_ERROR(...)
		#define DEBUG_TEST(...)
		#define DEBUG_INFO(...)
		#define DEBUG_TRANS(...)
	#else
		#define DEBUG_ERROR(fmt, args...)
		#define DEBUG_TEST(fmt, args...)
		#define DEBUG_INFO(fmt, args...)
		#define DEBUG_TRANS(fmt, args...)
	#endif
#endif

#endif // _H