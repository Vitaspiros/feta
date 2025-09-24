#pragma once

#ifdef __WIN32
// Windows uses different name for the same function for some reason
#define wcscasecmp wcsicmp
#define wcsncasecmp wcsnicmp
#endif