file(GLOB_RECURSE SRCS *.nasm *.asm *.S)
OpenAsmSupport()

set(CMAKE_ASM${ASM_DIALECT}_COMPILE_OBJECT "as -gstabs --32 -o <OBJECT> <SOURCE>")
set(CMAKE_ASM${ASM_DIALECT}_LINK_EXECUTABLE
        "ld -m elf_i386 -dynamic-linker /lib/ld-linux.so.2 -lc <OBJECTS> -o <TARGET> <LINK_LIBRARIES>")
add_executable(${build_temp} ${${build_temp}cpps} ${SRCS})