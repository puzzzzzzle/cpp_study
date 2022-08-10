file(GLOB_RECURSE SRCS *.nasm *.asm *.S)
OpenAsmSupport()
set(CMAKE_ASM${ASM_DIALECT}_COMPILE_OBJECT "as -o <OBJECT> <SOURCE>")
set(CMAKE_ASM${ASM_DIALECT}_LINK_EXECUTABLE "<CMAKE_LINKER> -dynamic-linker /lib64/ld-linux-x86-64.so.2 -lc <OBJECTS> -o <TARGET>")

add_executable(${build_temp} ${SRCS})