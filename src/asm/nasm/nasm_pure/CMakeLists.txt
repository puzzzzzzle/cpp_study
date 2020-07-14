file(GLOB_RECURSE SRCS *.nasm *.asm *.S)

add_executable(${build_temp} ${SRCS})
set_target_properties(${build_temp} PROPERTIES LINKER_LANGUAGE NASM)