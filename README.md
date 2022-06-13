## OpenXLSX 测试工程

```
excel读写的库
源码 https://github.com/troldal/OpenXLSX
```

## windows vs2019 64位  编译

```
cmake-gui  vs2019编译
会报这个错误
Selecting Windows SDK version 10.0.19041.0 to target Windows 10.0.19044.
E:/14_program/lkt_project/download/OpenXLSX/Benchmarks/gbench/cmake/ModulesE:/14_program/lkt_project/download/OpenXLSX/Benchmarks/gbench/cmake
git version: v0.0.0 normalized to 0.0.0
Version: 1.6.0
Performing Test HAVE_STD_REGEX -- success
Performing Test HAVE_GNU_POSIX_REGEX -- failed to compile
Performing Test HAVE_POSIX_REGEX -- failed to compile
Performing Test HAVE_STEADY_CLOCK -- success
Configuring done
Generating done

无视报错，生成vs工程，生成install的解决方案。会提示这两个字符错误，
    wks1.cell(XLCellReference("A3")).value() = "こんにちは世界";
    wks1.cell(XLCellReference("A4")).value() = "नमस्ते दुनिया!";
    就临时改成其他内容。
    wks1.cell(XLCellReference("A3")).value() = "你好，世界!";
    wks1.cell(XLCellReference("A4")).value() = "你好，世界!";
编译通过，成功生成了对应的库与头文件。


#方法三 静态库
add_library ( OpenXLSX  STATIC IMPORTED )
set_property (TARGET OpenXLSX PROPERTY IMPORTED_LOCATION ${CMAKE_MY_THIRDPARTY_PATH}/libOpenXLSX_win64/lib/OpenXLSX.lib)

target_link_libraries(${CMAKE_MY_TARGET_NAME} PRIVATE OpenXLSX)

```



