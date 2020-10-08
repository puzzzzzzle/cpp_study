aux_source_directory(. LIBGO_SRCS)
message("libgo study cpp : ${LIBGO_SRCS}")
add_library(LIBGO_TEST ${LIBGO_SRCS})