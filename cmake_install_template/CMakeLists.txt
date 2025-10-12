cmake_minimum_required(VERSION 3.17)
project(
        math_vec
        VERSION 1.0
        LANGUAGES CXX
)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# 是否为动态库
option(BUILD_SHARED_LIBS "Build shared libraries" OFF)

########## 库和可执行文件定义
# 库源文件
file(GLOB_RECURSE SRC
        ${CMAKE_SOURCE_DIR}/math_vec/*.cpp
        ${CMAKE_SOURCE_DIR}/math_vec/*.c
)
# 添加库
add_library(math_vec ${SRC})

# 头文件路径
target_include_directories(math_vec PUBLIC
        $<BUILD_INTERFACE:${CMAKE_SOURCE_DIR}/math_vec>
        $<INSTALL_INTERFACE:include/math_vec>
)
# 依赖
# 必须
find_package(ZLIB REQUIRED)
target_link_libraries(math_vec PUBLIC ZLIB::ZLIB)

find_package(Threads REQUIRED)
target_link_libraries(math_vec PUBLIC Threads::Threads)

# 可选
option(MATH_VEC_WITH_LIBPNG "Use libpng for PNG support" ON)
find_package(PNG)
if (PNG_FOUND AND MATH_VEC_WITH_LIBPNG)
    message(STATUS "Found PNG library")
    target_link_libraries(math_vec PUBLIC PNG::PNG)
    target_compile_definitions(math_vec PUBLIC MATH_VEC_HAVE_LIBPNG=1) # 同时定义宏
else ()
    message(STATUS "PNG not found or disabled")
    target_compile_definitions(math_vec PUBLIC MATH_VEC_HAVE_LIBPNG=0)
endif ()


# 添加可执行文件
add_executable(math_vec_tool main.cpp)
target_link_libraries(math_vec_tool math_vec)
target_include_directories(math_vec_tool PUBLIC $<BUILD_INTERFACE:${CMAKE_SOURCE_DIR}/>)

########## 安装
# 安装头文件
install(
        DIRECTORY math_vec/
        DESTINATION include/math_vec
        FILES_MATCHING PATTERN "*.h" PATTERN "*.hpp"
)
# 安装库文件
install(
        TARGETS math_vec math_vec_tool
        EXPORT math_vecTargets
        ARCHIVE DESTINATION lib           # 静态库(.a)
        LIBRARY DESTINATION lib           # 动态库(.so)
        RUNTIME DESTINATION bin           # 可执行文件
)
# 安装README和许可证（可选）
install(
        FILES README.md
        DESTINATION share/doc/math_vec
)
# CMake库目标导出，供 find_package 使用
install(EXPORT math_vecTargets
        DESTINATION lib/cmake/math_vec
        NAMESPACE math_vec::
)
# cmake config, find_package 依赖
include(CMakePackageConfigHelpers)
configure_package_config_file(
        ${CMAKE_CURRENT_SOURCE_DIR}/cmake/math_vecConfig.cmake.in
        ${CMAKE_CURRENT_BINARY_DIR}/math_vecConfig.cmake
        INSTALL_DESTINATION lib/cmake/math_vec
)
install(FILES ${CMAKE_CURRENT_BINARY_DIR}/math_vecConfig.cmake
        DESTINATION lib/cmake/math_vec
)
# 可选: 版本文件
write_basic_package_version_file(
        ${CMAKE_CURRENT_BINARY_DIR}/math_vecConfigVersion.cmake
        VERSION ${PROJECT_VERSION}
        COMPATIBILITY AnyNewerVersion
)
install(FILES ${CMAKE_CURRENT_BINARY_DIR}/math_vecConfigVersion.cmake
        DESTINATION lib/cmake/math_vec
)
########## 打包

set(CPACK_PACKAGE_NAME "math_vec")
set(CPACK_PACKAGE_VENDOR "puzzzzzzle")
set(CPACK_PACKAGE_CONTACT "2359173906@qq.com")
set(CPACK_PACKAGE_VERSION_MAJOR ${PROJECT_VERSION_MAJOR})
set(CPACK_PACKAGE_VERSION_MINOR ${PROJECT_VERSION_MINOR})
set(CPACK_PACKAGE_VERSION_PATCH 0)
set(CPACK_PACKAGE_DESCRIPTION_SUMMARY "A math vector library with optional PNG support.")

#set(CPACK_RESOURCE_FILE_LICENSE "${CMAKE_SOURCE_DIR}/LICENSE")
set(CPACK_RESOURCE_FILE_README "${CMAKE_SOURCE_DIR}/README.md")

# 主要文件的安装位置
set(CPACK_PACKAGING_INSTALL_PREFIX "/usr")

# 可选：生成DEB和RPM包
set(CPACK_GENERATOR "DEB;RPM;TGZ")

# deb包相关依赖
set(CPACK_DEBIAN_PACKAGE_DEPENDS "zlib1g")
# rpm包相关依赖（对Fedora/Redhat有效）
set(CPACK_RPM_PACKAGE_REQUIRES "zlib")

if(PNG_FOUND AND MATH_VEC_WITH_LIBPNG)
    set(CPACK_DEBIAN_PACKAGE_DEPENDS "${CPACK_DEBIAN_PACKAGE_DEPENDS}, libpng-dev")
    set(CPACK_RPM_PACKAGE_REQUIRES "${CPACK_RPM_PACKAGE_REQUIRES}, libpng")
endif()

# arch pacman 包相关依赖
#set(CPACK_ARCHIVE_PACKAGE_FILE_NAME "${CPACK_PACKAGE_NAME}-${PROJECT_VERSION}")

# 可选：定义包分类和对多架构支持
#set(CPACK_DEBIAN_PACKAGE_SECTION "libs")
#set(CPACK_DEBIAN_PACKAGE_ARCHITECTURE "amd64")
#
#set(CPACK_RPM_PACKAGE_GROUP "Libraries")
#set(CPACK_RPM_PACKAGE_ARCHITECTURE "x86_64")

# 可选: 文件权限与所有权
set(CPACK_DEBIAN_PACKAGE_CONTROL_STRICT_PERMISSION TRUE)


# 包安装后脚本 (如需)
#set(CPACK_DEBIAN_PACKAGE_POSTINST "${CMAKE_SOURCE_DIR}/scripts/postinst.sh")
#set(CPACK_DEBIAN_PACKAGE_PREINST "${CMAKE_SOURCE_DIR}/scripts/preinst.sh")

# !!!!!!!!!! 注意：需要先定义cpack变量, 再include, 不然不会生效 !!!!!!!!!!!!!!
include(CPack)
