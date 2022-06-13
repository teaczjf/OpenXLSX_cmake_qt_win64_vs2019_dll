#cmake version
cmake_minimum_required ( VERSION 3.10 )

set(CMAKE_CONFIGURATION_TYPES Release)

if(MSVC)
    add_compile_options("$<$<C_COMPILER_ID:MSVC>:/utf-8>")
    add_compile_options("$<$<CXX_COMPILER_ID:MSVC>:/utf-8>")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /UMBCS /D_UNICODE /DUNICODE")
endif()

project ( protobuf_test CXX C)
#设置程序编译输出路径

#reset output path
set ( EXECUTABLE_OUTPUT_PATH ${CMAKE_BINARY_DIR}/bin )
set ( LIBRARY_OUTPUT_PATH ${CMAKE_BINARY_DIR}/bin )
set ( CMAKE_SHARED_LIBRARY_LINK_C_FLAGS )
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)

# set(CMAKE_MY_PROJECT_PATH "E:/14_program/lkt_project/spacex-ui-bak")
# message (STATUS "current project dir is ${CMAKE_MY_PROJECT_PATH}")

#自动获取工程路径
string(REGEX REPLACE "/$" "" CURRENT_FOLDER_ABSOLUTE ${CMAKE_CURRENT_SOURCE_DIR})# 获取当前cmakelist文件存放的路径
get_filename_component(CURRENT_FOLDER ${CURRENT_FOLDER_ABSOLUTE} NAME)#获取当前存放cmakelist文件的文件夹名称，用于获取上层路径
string(REGEX REPLACE "(.*)/${CURRENT_FOLDER}$" "\\1" CMAKE_MY_PROJECT_PATH ${CURRENT_FOLDER_ABSOLUTE})#获取工程路径
# message (STATUS "1111111111111  CURRENT_FOLDER_ABSOLUTE   ==  ${CURRENT_FOLDER_ABSOLUTE}")
# string(REGEX REPLACE ".*/(.*)" "\\1" SECOND_FOLDER ${CMAKE_MY_PROJECT_PATH})#这句会获取路径${CMAKE_MY_PROJECT_PATH}最后一个文件夹的名字
#very important, for find package
#set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_MY_PROJECT_PATH}/Build)#//好像不生效 QT的路径还是的在项目中修改
set(CMAKE_FEATURE_PATH ${CMAKE_MY_PROJECT_PATH}/feature)
set(CMAKE_MY_THIRDPARTY_PATH ${CMAKE_MY_PROJECT_PATH}/thirdparty)
message (STATUS "CMAKE_MY_PROJECT_PATH ==  ${CMAKE_MY_PROJECT_PATH}")
message (STATUS "CMAKE_FEATURE_PATH ==  ${CMAKE_MY_PROJECT_PATH}")
message (STATUS "CMAKE_MY_THIRDPARTY_PATH ==  ${CMAKE_MY_THIRDPARTY_PATH}")

#第三方库的导入
#set(CMAKE_PREFIX_PATH "/opt/qt515")
#find_package(Qt5 COMPONENTS Widgets Core Network Gui Qml Quick PrintSupport Mqtt REQUIRED)
# set(CMAKE_PREFIX_PATH "D:/Qt6/6.2.4/msvc2019_64;${CMAKE_MY_PROJECT_PATH}/thirdparty/libprotobuf-win;${CMAKE_MY_PROJECT_PATH}/thirdparty/libzmq-win")#设置第三方库的存放路径
#set(CMAKE_PREFIX_PATH "D:/Qt6/6.2.4/msvc2019_64";${CMAKE_THIRDPARTY_PATH}/libmosquitto_win64_debug)#设置第三方库的存放路径
#set(CMAKE_PREFIX_PATH "D:/Qt6/6.2.4/msvc2019_64")#设置第三方库的存放路径
set(CMAKE_PREFIX_PATH "${CMAKE_MY_PROJECT_PATH}/thirdparty/libprotobuf_win64")
#find_package(Qt6 COMPONENTS Widgets Core Network Gui Qml Quick PrintSupport Mqtt Charts REQUIRED)
#find_package(ZeroMQ)
find_package(protobuf CONFIG REQUIRED)
set(CMAKE_PREFIX_PATH "${CMAKE_MY_PROJECT_PATH}/thirdparty/libOpenXLSX_win64")
find_package(OpenXLSX)



#引入库
#find_package(Qt6 COMPONENTS Widgets Core Network Gui Qml Quick PrintSupport Mqtt Charts REQUIRED)
#find_package(mosquitto)

#set include file
include_directories ( ${CMAKE_MY_PROJECT_PATH}/include)
include_directories ( ${CMAKE_MY_THIRDPARTY_PATH}/libOpenXLSX_win64/include)
include_directories ( ${CMAKE_MY_THIRDPARTY_PATH}/libOpenXLSX_win64/include/OpenXLSX)
#include_directories ( ${CMAKE_FEATURE_PATH}/easylogging)
#include_directories ( ${CMAKE_FEATURE_PATH}/easylogging/inc)
#这样设置过后，就能实现在右侧树状图中看到本工程文件下的全部头文件了 *.h  *.hpp  但是这也只是表示显示，不代表被包含进工程。编译生效的还是include_directories这句话，否则编译会提示找不到头文件的
FILE(GLOB_RECURSE LibFiles "${CMAKE_MY_PROJECT_PATH}/*.h*" )
add_custom_target(headers SOURCES ${LibFiles})


#set source file
#aux_source_directory ( ${CMAKE_MY_PROJECT_PATH}/src DIR_USR_SOURCE)
aux_source_directory ( ${CMAKE_MY_PROJECT_PATH} DIR_USR_SOURCE)

#aux_source_directory ( ${CMAKE_FEATURE_PATH}/easylogging DIR_USR_SOURCE)
#aux_source_directory ( ${CMAKE_FEATURE_PATH}/easylogging/src DIR_USR_SOURCE)

#set qrc file
# set (QRC_SOURCE)
# list(APPEND QRC_SOURCE ${CMAKE_MY_PROJECT_PATH}/qml-source/qml.qrc)
# message (STATUS "qrc file is ${QRC_SOURCE}")

#set debug
if(CMAKE_BUILD_TYPE STREQUAL Debug)
    add_definitions (
        -DPRINT_DEBUG_INFO
    )
endif()
add_definitions (
    -DWIN32_LEAN_AND_MEAN
)

#设置库的路径和头文件
#方法一 动态库
#include_directories ( ${CMAKE_THIRDPARTY_PATH}/libmosquitto_win64/include)
#link_directories("${CMAKE_THIRDPARTY_PATH}/libmosquitto_win64/lib")
#方法二 静态库
set(CMAKE_PREFIX_PATH "${CMAKE_MY_PROJECT_PATH}/thirdparty/libOpenXLSX_win64")
find_package(OpenXLSX)
#方法三 静态库
add_library ( OpenXLSX  STATIC IMPORTED )
set_property (TARGET OpenXLSX PROPERTY IMPORTED_LOCATION ${CMAKE_MY_THIRDPARTY_PATH}/libOpenXLSX_win64/lib/OpenXLSX.lib)

#include_directories ( ${CMAKE_THIRDPARTY_PATH}/libOpenXLSX_win64/include)
#link_directories("${CMAKE_THIRDPARTY_PATH}/libOpenXLSX_win64/lib")

MESSAGE( STATUS "=================There are source files : ${DIR_USR_SOURCE}====================.")

set(CMAKE_MY_TARGET_NAME ${CMAKE_PROJECT_NAME})#获取工程名
#generate target
add_executable ( ${CMAKE_MY_TARGET_NAME} ${DIR_USR_SOURCE} )#执行编译
# add_executable ( ${CMAKE_PROJECT_NAME} ${DIR_USR_SOURCE} ${QRC_SOURCE})
#设置了Debug版本和Release版本下可执行文件的后缀名
if(CMAKE_BUILD_TYPE STREQUAL Debug)
    set_target_properties(${CMAKE_MY_TARGET_NAME} PROPERTIES DEBUG_POSTFIX "_d")
else()
    set_target_properties(${CMAKE_MY_TARGET_NAME} PROPERTIES RELEASE_POSTFIX "_r")
endif()

#链接库
if(CMAKE_BUILD_TYPE STREQUAL Debug)
    target_link_libraries(${CMAKE_MY_TARGET_NAME} PRIVATE OpenXLSX)
else()
    target_link_libraries(${CMAKE_MY_TARGET_NAME} PRIVATE OpenXLSX)
endif()

#target_link_libraries ( ${CMAKE_PROJECT_NAME} PRIVATE pthread mosquittopp_static mosquitto_static crypt  dl)

#add custom

add_custom_target ( clean-all COMMAND rm -rf {CMAKE_BINARY_DIR}/* )
