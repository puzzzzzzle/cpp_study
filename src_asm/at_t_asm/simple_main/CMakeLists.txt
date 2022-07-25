file(GLOB_RECURSE SRCS *.nasm *.asm *.S)
OpenAsmSupport()

add_executable(${build_temp} ${${build_temp}cpps} ${SRCS})