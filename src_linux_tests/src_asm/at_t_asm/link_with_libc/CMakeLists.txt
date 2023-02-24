file(GLOB_RECURSE SRCS *.nasm *.asm *.S)
OpenAsmSupport()
set(CMAKE_ASM${ASM_DIALECT}_OBJECT_FORMAT elf64)
set(CMAKE_ASM${ASM_DIALECT}_COMPILE_OBJECT "as -o <OBJECT> <SOURCE>")
set(CMAKE_ASM${ASM_DIALECT}_LINK_EXECUTABLE "/usr/bin/c++  -ldl  -fPIC -ggdb3 -g3  <OBJECTS> -o <TARGET>")

add_executable(${CURRENT_TASK} ${SRCS})