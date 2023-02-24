file(GLOB_RECURSE SRCS *.nasm *.asm *.S)
OpenAsmSupport()
# message("ASM_DIALECT ${ASM_DIALECT} ${${CURRENT_TASK}_SRCS}")
set(CMAKE_ASM${ASM_DIALECT}_COMPILE_OBJECT "as -o <OBJECT> <SOURCE>")

add_executable(${CURRENT_TASK} ${SRCS})