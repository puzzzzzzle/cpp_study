include_directories(.)
#OpenAsmSupport()
enable_language(ASM)
file(GLOB_RECURSE SRCS *.nasm *.asm *.S *.s *.cpp *.c)
set(CMAKE_ASM${ASM_DIALECT}_COMPILE_OBJECT "as -o <OBJECT> <SOURCE>")

# 可执行文件
add_executable(${build_temp} ${${build_temp}cpps} ${SRCS})

#通用动态链接库
target_link_libraries(${build_temp} ${COMMON_LIBS})
