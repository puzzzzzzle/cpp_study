
#include "sysdep_t.h"

ENTRY(__test_func)
	ret
PSEUDO_END(__test_func)

weak_alias (__test_func, test_func)



