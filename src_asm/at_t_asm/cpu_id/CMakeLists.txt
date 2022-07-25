file(GLOB_RECURSE SRCS *.nasm *.asm *.S)
OpenAsmSupport()
message("ASM_DIALECT ${ASM_DIALECT} ${${build_temp}cpps}")
#set(CMAKE_ASM${ASM_DIALECT}_COMPILE_OBJECT "as -o <OBJECT> <SOURCE>")

add_executable(${build_temp} ${SRCS})