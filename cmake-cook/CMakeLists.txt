# 定义cmake的最低版本
cmake_minimum_required(VERSION 3.16.7 FATAL_ERROR)

# 指定项目名称与编程语言，不指定默认为c++
project(hello LANGUAGES CXX)

# 根据源文件生成可执行文件
add_executable(hello-01 hello.cpp)

# 将自定义的类或者其他所用的资源文件封装为静态库。
add_library(Messageout-static
    STATIC
        Messageout_static.h
        Messageout_static.cpp)

# 将自定义的类或者其他所用的资源文件封装为动态库。
add_library(Messageout-shared
        SHARED
            Messageout_shared.h
            Messageout_shared.cpp)

# 使用OBJECT对同一份源文件构建动态库以及静态库
add_library(Messageout-obj
        OBJECT
            Messageout.h
            Messageout.cpp)
# 可能在某些平台和/或使用较老的编译器上，需要显式地为目标设置POSITION_INDEPENDENT_CODE属性。
set_target_properties(Messageout-obj
        PROPERTIES
            POSITION_INDEPENDENT_CODE 1)
add_library(Messageout-obj-shared
        SHARED
            $<TARGET_OBJECTS:Messageout-obj>)
add_library(Messageout-obj-static
        SHARED
            $<TARGET_OBJECTS:Messageout-obj>)

# *******************************************************************
# 使用add_library(message SHARED Messageout_shared.h Messageout_shared.cpp)从静态库切换到动态共享对象(DSO)
# OBJECT：需要将同一份源文件生成静态库和动态库时使用。
# MODULE：又为DSO组。与SHARED库不同，它们不链接到项目中的任何目标，不过可以进行动态加载。该参数可以用于构建运行时插件。
# IMPORTED：此类库目标表示位于项目外部的库。此类库的主要用途是，对现有依赖项进行构建。
# INTERFACE：与IMPORTED库类似。不过，该类型库可变，没有位置信息。它主要用于项目之外的目标构建使用。
# ALIAS：顾名思义，这种库为项目中已存在的库目标定义别名。不过，不能为IMPORTED库选择别名。
# *******************************************************************

# 将静态库链接到可执行文件，在add_executable()执行后进行链接库的操作
target_link_libraries(hello-01 Messageout-static)
target_link_libraries(hello-01 Messageout-shared)
target_link_libraries(hello-01 Messageout-obj-shared)

# 设置全局变量USE_LIBRARY，并且设置它的值为OFF，打印它的值。
set(USE_LIBRARY OFF)
message(STATUS "Compile sources into a library? ${USE_LIBRARY}")
# 逻辑变量可以设置为
# 1、ON、YES、true、Y或非零数，则逻辑变量为true。
# 0、OFF、NO、false、N、IGNORE、NOTFOUND、空字符串，或者以-NOTFOUND为后缀，则逻辑变量为false。

# 引入一个变量_sources，包括Message.hpp和Message.cpp。可以在构建库或者其他地方使用_sources替代Message.hpp Message.cpp。
list(APPEND _sources Message.hpp Message.cpp)

# 该选项实现从外部设置变量的值，并设置其默认值为OFF
option(USE_LIBRARY_SHARED "Compile sources into a library" OFF)

# 类似C++包含头文件，CMakeDependentOption一般是CMake自带或者定制，cmake_dependent_option属于CMakeDependentOption。
include(CMakeDependentOption)
cmake_dependent_option()

# 为Messageout-shared库目标设置了编译选项,也可以对可执行文件设置编译选项
target_compile_options(Messageout-shared
  PRIVATE
    "-g"
  )
