#ifndef _MY_EASYLOGGING_H_
#define _MY_EASYLOGGING_H_
#include "inc/easylogging++.h"
#include "normal_typedef.h"

enum LEVEL
{
    MY_ERR = 0,
    MY_Warn,
    MY_Debug,
    MY_Trace,
    MY_Info
};

void myCrashHandler(int sig);
void rolloutHandler(const char *filename, std::size_t size);
void easylogginginit();
void logStrOut(int size, std::string str, LEVEL logLevel);

#define LogInfoDump(info, buff, size) logDump(info, buff, size, LEVEL::MY_Info)
#define LogTraceDump(info, buff, size) logDump(info, buff, size, LEVEL::MY_Trace)
#define LogWarnDump(info, buff, size) logDump(info, buff, size, LEVEL::MY_Warn)
#define LogErrorDump(info, buff, size) logDump(info, buff, size, LEVEL::MY_ERR)
#define LogDebugDump(info, buff, size) logDump(info, buff, size, LEVEL::MY_Debug)
/**
 * @brief
 * 能方便输出：char buf[len] , int buf[lend]等数组，
 * 而无需区分数组元素是字符类型还是整数类型。
 * 能方便输出数据包。
 * @tparam _TYPE
 * @param  info             日志头
 * @param  buff             日志内容
 * @param  size             buff的size
 * @param  logLevel         日志等级
 */
template <typename T1>
void logDump(char *info, T1 *buff, int size, LEVEL logLevel)
{
    std::string str(info);
    str += ": ";
    if (buff == NULL || size <= 0)
        str += "buff is null!";
    else
    {
        std::stringstream ss;
        for (int _dumpArrSize = 0; _dumpArrSize < size; ++_dumpArrSize)
            ss << (buff[_dumpArrSize]) << ",";
        str += ss.str();
    }
    logStrOut(size, str, logLevel);
}

template <>
void logDump(char *info, char *buff, int size, LEVEL logLevel);

template <>
void logDump(char *info, UINT8 *buff, int size, LEVEL logLevel);

void log_test();

// template <typename T>
// void fun(T a)
// {
//     std::cout << "The main template fun(): " << a << std::endl;
// }
// template <> // 对int型特例化
// void fun(int a);
void printf_init_log(char *log_info);
void printf_debug_log(char *log_info);
void En_G_LOG_DEBUG_INFO(int is_en);
void En_G_DEBUG_TERMINAL_LOG(int is_en);

#endif

// template <>
// void logDump(char *info, unsigned char *buff, int size, LEVEL logLevel);

// template <>
// void logDump(char *info, const char *buff, int size, LEVEL logLevel);

// template <>
// void logDump(char *info, const unsigned char *buff, int size, LEVEL logLevel);
