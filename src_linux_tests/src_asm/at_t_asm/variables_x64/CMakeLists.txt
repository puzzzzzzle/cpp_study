file(GLOB_RECURSE SRCS *.nasm *.asm *.S)
OpenAsmSupport()
set(CMAKE_ASM${ASM_DIALECT}_COMPILE_OBJECT "as -o <OBJECT> <SOURCE>")

add_executable(${CURRENT_TASK} ${SRCS})