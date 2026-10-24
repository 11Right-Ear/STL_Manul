cmake_minimum_required (VERSION 4.1.0)

#工程名
project(CPPSTL)

#设置cc主函数路径 和 h头文件路径
aux_source_directory(tests MAIN_PATH)

#  - PROJECT_SOURCE_DIR: 支持 #include "Phase1/01_iterator/xxx.hpp" 这种相对根目录的写法
include_directories(${PROJECT_SOURCE_DIR})
# include_directories(${PROJECT_SOURCE_DIR}/Phase0/01_template_basics)
# include_directories(${PROJECT_SOURCE_DIR}/Phase0/02_type_deduction)
# include_directories(${PROJECT_SOURCE_DIR}/Phase0/03_constexpr)
include_directories(${PROJECT_SOURCE_DIR}/Phase1/01_iterator)
include_directories(${PROJECT_SOURCE_DIR}/Phase1/02_allocator)
include_directories(${PROJECT_SOURCE_DIR}/Phase1/03_traits)

#设置输出的路径
# set (EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_PATH}/bin)
set (EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/bin)

#可执行文件编译
add_executable(main.out ${MAIN_PATH})
