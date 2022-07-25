file(GLOB_RECURSE SRCS *.nasm *.asm *.S)
OpenAsmSupport()
message("ASM_DIALECT ${ASM_DIALECT}")
#set(CMAKE_ASM${ASM_DIALECT}_COMPILE_OBJECT "as -o <OBJECT> <SOURCE>")

add_executable(${build_temp} ${${build_temp}cpps} ${SRCS})