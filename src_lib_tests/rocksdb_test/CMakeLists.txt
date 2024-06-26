# Try to find RocksDB headers and library.
#
# Usage of this module as follows:
#
#     find_package(RocksDB)
#
# Variables used by this module, they can change the default behaviour and need
# to be set before calling find_package:
#
#  ROCKSDB_ROOT_DIR          Set this variable to the root installation of
#                            RocksDB if the module has problems finding the
#                            proper installation path.
#
# Variables defined by this module:
#
#  ROCKSDB_FOUND               System has RocksDB library/headers.
#  ROCKSDB_LIBRARIES           The RocksDB library.
#  ROCKSDB_INCLUDE_DIRS        The location of RocksDB headers.

find_path(ROCKSDB_ROOT_DIR
        NAMES include/rocksdb/db.h
)

find_library(ROCKSDB_LIBRARIES
        NAMES rocksdb
        HINTS ${ROCKSDB_ROOT_DIR}/lib
)

find_path(ROCKSDB_INCLUDE_DIRS
        NAMES rocksdb/db.h
        HINTS ${ROCKSDB_ROOT_DIR}/include
)

include(FindPackageHandleStandardArgs)
find_package_handle_standard_args(RocksDB DEFAULT_MSG
        ROCKSDB_LIBRARIES
        ROCKSDB_INCLUDE_DIRS
)

mark_as_advanced(
        ROCKSDB_ROOT_DIR
        ROCKSDB_LIBRARIES
        ROCKSDB_INCLUDE_DIRS
)


aux_source_directory(. ${CURRENT_TASK}_SRCS)
include_directories(.)

if (NOT ROCKSDB_FOUND)
    message(FATAL_ERROR "ROCKSDB_FOUND not found")
endif ()
include_directories(ROCKSDB_LIBRARIES)

# 可执行文件
add_executable(${CURRENT_TASK} ${${CURRENT_TASK}_SRCS})
#通用动态链接库
target_link_libraries(${CURRENT_TASK} ${COMMON_LIBS} ${ROCKSDB_LIBRARIES})
