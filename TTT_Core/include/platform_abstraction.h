#pragma once
/*
 Needed by the Visual C++ compiler to use certain legacy C functions.
 Put them first.
 */
#define _CRT_SECURE_NO_WARNINGS
#define _USE_MATH_DEFINES



/*
 Include commonly used C/C++ header files.
 */
////////////////////////////////////////////////////////////////////////////////
//C Header files
#include <cstdio>
#include <cstdint>
#include <cstring>
#include <cmath>

//System
#include <memory>
#include <mutex>
#include <stdexcept>
#include <atomic>
#include <system_error>
#include <thread>

//IO and Streams
#include <iostream>
#include <fstream>
#include <sstream>
#include <iomanip>

//Containers
#include <string>
#include <list>
#include <queue>
#include <vector>
#include <stack>
#include <set>
#include <map>
#include <unordered_map>
#include <unordered_set>

//Algorithms and Math
#include <algorithm>
#include <functional>
#include <random>
#include <bitset>
////////////////////////////////////////////////////////////////////////////////



/*
 Different compilers define different way of determining if compiling for 
 debug mode. This next block of code is meant to provide a common of 
 checking for the debug directive. Code should only check for "DEBUG". No 
 need to check for any other preprocessor directive.
 */
////////////////////////////////////////////////////////////////////////////////
#if !defined(NDEBUG) || defined(_DEBUG) || defined(DEBUG)

#ifndef _DEBUG
#define _DEBUG
#endif

#ifndef DEBUG
#define DEBUG
#endif

#endif
////////////////////////////////////////////////////////////////////////////////



/*
 This next section abstracts objects across different platforms. For example:
 The data-type used to represent a file is different across Windows and POSIX
 systems. So here, we will abstract the different underlying types so that 
 code can use the abstracted type. When the code is compiled for each 
 platform, the compiler will take care of substituting the abstracted type 
 for the platform-dependent type.
 
 Abstracted types:
 * File Handle 
 * Thread Handle
 * System Error Code
 * Socket Handle
 * Socket Error Code
 * The value of an invalid file handle.
 * The value of an invalid thread handle.
 * The value of an invalid socket handle.

 Use these abstracted types in all function signatures:
 * sys_error_t
 * handle_t
 * thread_handle_t
 * file_handle_t
 * socket_error_t
 * socket_t
 * INVALID_HANDLE
 * NO_FILE
 * NO_SOCKET

 */
////////////////////////////////////////////////////////////////////////////////

/*
 Include stuff for Windows.
 */
#ifdef _WIN32

#ifndef WIN32_LEAN_AND_MEAN
// Exclude rarely used Windows stuff.
#define WIN32_LEAN_AND_MEAN
#endif

// Use C++ min and max functions instead of Windows.
#define NOMINMAX 

// Include Windows header files.
#include <Windows.h>
#include <WinSock2.h>

// Add GDI or DirectX stuff here.

using sys_error_t = DWORD;

/*
 Generic Handle
 */
using handle_t = HANDLE;
template<typename Handle = handle_t>
constexpr Handle INVALID_HANDLE = INVALID_HANDLE_VALUE;

/*
 Thread Handle Type
 */
using thread_handle_t = HANDLE;

/*
 File Handle Type
 */
using file_handle_t = HANDLE;
static const file_handle_t NO_FILE = INVALID_HANDLE_VALUE;

using socket_error_t = int;

/*
 Socket Handle Type
 */
using socket_t = SOCKET;
static const socket_t NO_SOCKET = INVALID_SOCKET;

/*
 Otherwise, include stuff for Linux/POSIX systems.
 */
#else

// Include Linux/POSIX header files.
#include <unistd.h>
#include <pthread.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <sys/stat.h>

// TODO: Add third-party GUI headers here. X Window stuff?
// https://stackoverflow.com/questions/12717138/what-is-linux-s-native-gui-api

using sys_error_t = int;

/*
 Generic Handle
 */
using handle_t = typename void*
template<typename Handle = handle_t>
constexpr Handle INVALID_HANDLE = static_cast<Handle>(-1);

/*
 Thread Handle Type
 */
using thread_handle_t = pthread_t;

/*
 File Handle Type
 */
using file_handle_t = int;
static constexpr file_handle_t NO_FILE = -1;

using socket_error_t = int;

/*
 Socket Handle Type
 */
using socket_t = int;
static constexpr socket_t NO_SOCKET = -1;


#endif
////////////////////////////////////////////////////////////////////////////////