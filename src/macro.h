#include <features.h>

#if defined( __GNU_LIBRARY__)
#define OPTIND_RESET() optind = 0;
#else
#define OPTIND_RESET() optind = 1;
#endif
