file(GLOB_RECURSE SRCS *.nasm *.asm *.S)
OpenAsmSupport()
add_executable(${CURRENT_TASK} ${${CURRENT_TASK}_SRCS} ${SRCS})