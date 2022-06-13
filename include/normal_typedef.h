/**
 * @file normal_typedef.h
 * @brief  common typedef
 * @author Fan Chuanlin, fanchuanlin@aliyun.com
 * @version 1.0
 * @date 2021-01-29
 * @attention
 * @brief History:
 * <table>
 * <tr><th> Date <th> Version <th> Author <th> Description
 * <tr><td> xxx-xx-xx <td> 1.0 <td> Fan Chuanlin <td> Create
 * </table>
 *
 */

#ifndef _NORMAL_TYPEDEF_H_
#define _NORMAL_TYPEDEF_H_

#include <iostream>
#include <string>
#include <iomanip>
#include <cstring>
#include <cstdio>
#include <cstdlib>
#include <fcntl.h>
#include <unistd.h>
#include <time.h>
#include <math.h>
#include <sys/time.h>

/// SOCKET
#include <string.h>
#include <errno.h>
#include <sys/types.h>
#include <pthread.h>
#include <semaphore.h>
#include <sys/time.h>
#include <pthread.h>
#if defined(_WIN32)
#include <WinSock2.h> //WindowsSocket
#include <ws2tcpip.h>
#include <windows.h>

// typedef struct tagTHREADNAME_INFO
//{
//     DWORD dwType; // must be 0x1000
//     LPCSTR szName; // pointer to name (in user addr space)
//     DWORD dwThreadID; // thread ID (-1=caller thread)
//     DWORD dwFlags; // reserved for future use, must be zero
// } THREADNAME_INFO;

// void SetThreadName(DWORD dwThreadID, LPCSTR szThreadName)
//{
//     THREADNAME_INFO info;
//     info.dwType = 0x1000;
//     info.szName = szThreadName;
//     info.dwThreadID = dwThreadID;
//     info.dwFlags = 0;

//    __try
//    {
//        RaiseException( 0x406D1388, 0, sizeof(info)/sizeof(DWORD), (DWORD*)&info );
//    }
//    __catch(EXCEPTION_CONTINUE_EXECUTION){}
//}
#else
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/prctl.h>
#endif

/// define c++11 std
#if 11
#include <vector>
#include <set>
#include <map>
#include <list>
#include <queue>
#endif
/**
 * @name  define normal type;
 *
 **  @} */
#if defined(_WIN32)
#else
typedef bool BOOLEAN;
typedef void VOID;
typedef int SOCKET;
#endif
typedef unsigned char UINT8;
typedef signed char INT8;
typedef unsigned char OCTET;
typedef char CHAR;
typedef unsigned short UINT16;
typedef signed short INT16;
typedef unsigned int UINT32;
typedef signed int INT32;
typedef unsigned long ULONG;
typedef signed long LONG;
typedef unsigned long long UINT64;
typedef long long INT64;
typedef float FLOAT;
typedef double DOUBLE;
typedef int SOCKET_FP;

/// for socket
#if defined(_WIN32)
#else
#define INVALID_SOCKET -1
typedef int SOCKET;
#endif
typedef int af_family;
typedef int in_port;

#define BACKLOG_LEN 10
#define SOCKET_SERVER_PORT 6666
#define SOCKET_CLIENT_PORT 9999
#define LOCAL_HOST "127.0.0.1" ///< 默认ip本地回环地址

///< 网络角色枚举
typedef enum
{
    SOCKET_ROLE_SERVER = 0,
    SOCKET_ROLE_CLIENT = 1
} SOCKET_ROLE_E;

///< 网络通讯协议的枚举
typedef enum
{
    SOCKET_PROTO_TCP = 0,
    SOCKET_PROTO_UDP = 1,
    SOCKET_PROTO_UDP_MC = 2 ///< udp 组播通讯
} SOCKET_PROTO_E;

#if defined(_WIN32)
#else
#define TRUE true
#define FALSE false
#endif

///<记录返回状态
typedef enum
{
    Lret_success = 0,           ///< 成功
    Lret_fail = 1,              ///< 失败
    Lret_timeout = 2,           ///< 超时错误
    Lret_accept_fail = 3,       ///< accept失败
    Lret_connet_fail = 4,       ///< 连接失败
    Lret_recv_fail = 5,         ///< 接收失败
    Lret_format_fail = 6,       ///< 报文格式打包失败
    Lret_param_check_error = 7, ///< 报文参数检查失败
    Lret_max,
} Lret;

const char ret_str[][30] =
    {
        " success ",
        " fail ",
        " timeout ",
        " accept_fail ",
        " connet_fail ",
        " recv_fail ",
        " format_fail ",
        " param_check_error "};

#define MQTT_MESSAGE_MAX_LENTH 268435455

#endif
