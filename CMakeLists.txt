cmake_minimum_required(VERSION 3.7)
set(project_name cpp_study_all)
project(${project_name})
include(${CMAKE_SOURCE_DIR}/common/CMake/FuncDefs.cmake)

#设置版本号
set(VERSION_MAJOR 1.2)
set(VERSION_MINOR 0)
# 选项
option(boost_static "use static boost lib" ON)
option(use_boost_log "use boost log for logger" ON)

# 公用定义,需要在设定完成后include
include(${CMAKE_SOURCE_DIR}/common/CMake/CommonInclude.cmake)

# 加载conan
set(CONAN_LIBS "")
execute_process(
        COMMAND conan install ..
)
include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
conan_basic_setup()
message("conan get libs\t${CONAN_LIBS}\n")
# 遍历文件
AddAllSubDir()



