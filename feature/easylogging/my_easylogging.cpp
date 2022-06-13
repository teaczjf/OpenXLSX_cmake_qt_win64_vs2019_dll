#include "my_easylogging.h"
using namespace std;

INT32 G_LOG_ENABLE = 0;              //调试中的变量，写0就好了。写1则开启相应打印
INT32 G_DEBUG_LOG_ENABLE = 0;        //调试中的变量，写0就好了。
INT32 G_DEBUG_PRINT_SOCKET_BUFF = 0; //调试中的变量，写0就好了。启用的话会打印很长的数据包的。

INT32 G_LOG_INIT_INFO = 1; //初始化信息打印进log文件 启动后，都是一次性信息。默认打开

//这两个可以由上层应用控制 开关
INT32 G_LOG_DEBUG_INFO = 1;     //调试用的化信息打印进log文件
INT32 G_DEBUG_TERMINAL_LOG = 1; //把调试信息打印到终端

// #define LogInfoDump(info, size, buff) logDump(info, buff, size, LEVEL::MY_Info)
// #define LogTraceDump(info, size, buff) logDump(info, buff, size, LEVEL::MY_Trace)
// #define LogWarnDump(info, size, buff) logDump(info, buff, size, LEVEL::MY_Warn)
// #define LogErrorDump(info, size, buff) logDump(info, buff, size, LEVEL::MY_ERR)
// #define LogDebugDump(info, size, buff) logDump(info, buff, size, LEVEL::MY_Debug)

// easylogging 相关内容
INITIALIZE_EASYLOGGINGPP

#if ELPP_FEATURE_CRASH_LOG
/**
 * @brief myCrashHandler
 * 程序奔溃前的回调函数，发出最后的呐喊，写下最后的log
 * @param sig
 */
void myCrashHandler(int sig)
{
    LOG(ERROR) << "Woops! Crashed!";
    // FOLLOWING LINE IS ABSOLUTELY NEEDED AT THE END IN ORDER TO ABORT APPLICATION
    el::Helpers::crashAbort(sig);
}
#endif

/**
 * @brief rolloutHandler
 * 日志备份，当文件超过一定大小后，就生成一个bak文件
 * @param filename
 * @param size
 */
void rolloutHandler(const char *filename, std::size_t size)
{
    /// 备份日志
    static unsigned int idx;

#if defined(_WIN32)
    cout << "###########LOG SIZE FULL#############" << endl;
    std::stringstream ss;
    string cc;
    ss << "ren " << filename << " log_backup_" << ++idx;
    cc = ss.str();
    replace(cc.begin(), cc.end(), '/', '\\');
    system(cc.c_str());
#else
    /*下面这段没有测试过*/
    system("mkdir bin");
    std::stringstream ss;
    ss << "move " << filename << " bin\\log_backup_" << ++idx;
    system(ss.str().c_str());
#endif
}

/**
 * @brief easylogginginit
 *  easylogging初始化函数，加载配置文件，注册回调函数都在这里。
 */
void easylogginginit()
{
    /*
    必须设置标记 LoggingFlag::StrictLogFileSizeCheck
    否则,配置文件中MAX_LOG_FILE_SIZE = 1048576不生效
    */
    el::Loggers::addFlag(el::LoggingFlag::StrictLogFileSizeCheck);

    const string log_conf_file = R"(./log/log.conf)";
    // const string log_conf_file = R"(/root/gitlab/xdevice-platform/doc/log.conf)";
    // 加载配置文件，构造一个配置器对象
    el::Configurations conf(log_conf_file.data());

    // 用配置文件配置所有的日志记录器
    el::Loggers::reconfigureAllLoggers(conf);
#if ELPP_FEATURE_CRASH_LOG
    el::Helpers::setCrashHandler(myCrashHandler); //配置程序闪退的时候，再log中记录一下
#endif
    /// 注册回调函数
    el::Helpers::installPreRollOutCallback(rolloutHandler);
}

/**
 * @brief
 * @param  size             日志长度
 * @param  str              日志内容
 * @param  logLevel         当前日志等级
 */
void logStrOut(int size, std::string str, LEVEL logLevel)
{
    switch (logLevel)
    {
    case MY_ERR:
        // LOG(ERROR) << "[Arr Count:" << size << "]" << str;
        LOG(ERROR) << str;
        break;
    case MY_Debug:
        // LOG(DEBUG) << "[Arr Count:" << size << "]" << str;
        LOG(DEBUG) << str;
        break;
    case MY_Info:
        // LOG(INFO) << "[Arr Count:" << size << "]" << str;
        LOG(INFO) << str;

        break;
    case MY_Trace:
        // LOG(TRACE) << "[Arr Count:" << size << "]" << str;
        LOG(TRACE) << str;
        break;
    case MY_Warn:
        // LOG(WARNING) << "[Arr Count:" << size << "]" << str;
        LOG(WARNING) << str;
        break;
    default:
        break;
    }
}

/**
 * @brief
 * 对char *型特例化
 * @tparam
 * @param  info             My Param doc
 * @param  buff             My Param doc
 * @param  size             My Param doc
 * @param  logLevel         My Param doc
 */
template <>
void logDump(char *info, char *buff, int size, LEVEL logLevel)
{
    std::string str(info);
    str += "(ASCII): ";
    if (buff == NULL || size <= 0)
        str += "buff is null!";
    else
    {
        std::stringstream ss;
        for (int _dumpArrSize = 0; _dumpArrSize < size; ++_dumpArrSize)
            ss << static_cast<int>(buff[_dumpArrSize]) << " ";
        str += ss.str();
    }
    logStrOut(size, str, logLevel);
}
/**
 * @brief
 * 对UINT8 *型特例化 安装16进制打印
 * @tparam
 * @param  info             My Param doc
 * @param  buff             My Param doc
 * @param  size             My Param doc
 * @param  logLevel         My Param doc
 */
template <>
void logDump(char *info, UINT8 *buff, int size, LEVEL logLevel)
{
    std::string str(info);
    str += "(HEX): ";
    if (buff == NULL || size <= 0)
        str += "buff is null!";
    else
    {
        std::stringstream ss, s1;
        for (int _dumpArrSize = 0; _dumpArrSize < size; ++_dumpArrSize)
            // s1 =(buff[_dumpArrSize];
            ss << std::hex << static_cast<uint>(buff[_dumpArrSize]) << " ";
        str += ss.str();
    }
    logStrOut(size, str, logLevel);
}

// template <typename T>
// void fun(T a)
// {
//     cout << "The main template fun(): " << a << endl;
// }

// template <> // 对int型特例化
// void fun(int a)
// {
//     cout << "Specialized template for int type: " << a << endl;
// }

/**
 * @brief
 * 测试函数
 */
void log_test()
{
    char aa = 4;
    // char *cc = "12345";
    UINT8 cc[] = {0X31, 0X31, 0X31};
    char buf[3] = {5, 6, 7};
    LOG(INFO) << "》》》》》》》》》》打印测试《《《《《《《《";
    LOG(INFO) << " UINT8 cc[] = {0X31, 0X31, 0X31};";

    LOG(INFO) << "     char buf[3] = {5, 6, 7};";
    LOG(INFO) << "#################封装之前###########";
    LOG(INFO) << "打印cc ：" << cc;
    LOG(INFO) << "打印buf[3]："
              << "buf = " << buf << " buf[0] = " << buf[0] << " buf[1] = " << buf[1] << " (INT8)buf[2] = " << (UINT8)(buf[2]);
    LOG(INFO) << "####################封装之后##########";
    LogInfoDump("打印cc", cc, 3);
    LogInfoDump("打印buf[3]", buf, 3);
}

/**
 * @brief En_G_LOG_DEBUG_INFO
 * 配置是否将debug信息写入log文本
 * @param is_en
 */
void En_G_LOG_DEBUG_INFO(int is_en)
{
    if (is_en == 1)
    {
        G_LOG_DEBUG_INFO = 1;
    }
    else
    {
        G_LOG_DEBUG_INFO = 0;
    }
}

/**
 * @brief En_G_DEBUG_TERMINAL_LOG
 * 配置是否将debug信息打印到terminal
 * @param is_en
 */
void En_G_DEBUG_TERMINAL_LOG(int is_en)
{
    if (is_en == 1)
    {
        G_DEBUG_TERMINAL_LOG = 1;
    }
    else
    {
        G_DEBUG_TERMINAL_LOG = 0;
    }
}

/**
 * @brief printf_init_log
 * 印初始化log 适配了QT可以在终端显示出来
 * @param log_info
 */
void printf_init_log(char *log_info)
{
    LOG_IF(G_LOG_INIT_INFO, INFO) << log_info;
#if defined(_WIN32)
    if (G_DEBUG_TERMINAL_LOG)
    {
        qDebug() << log_info;
    }
#else
    if (G_DEBUG_TERMINAL_LOG)
    {
        cout << log_info << endl;
    }
#endif
}

/**
 * @brief printf_debug_log
 * 打印调试log
 * @param log_info
 */
void printf_debug_log(char *log_info)
{
    LOG_IF(G_LOG_DEBUG_INFO, INFO) << log_info;
#if defined(_WIN32)
    if (G_DEBUG_TERMINAL_LOG)
    {
        qDebug() << log_info;
    }
#else
    if (G_DEBUG_TERMINAL_LOG)
    {
        cout << log_info << endl;
    }
#endif
}