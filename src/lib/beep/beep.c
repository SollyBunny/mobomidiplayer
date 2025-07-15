#if defined(_WIN32) || defined(_WIN64)
#error "Beep not supported on windows"
#elif defined(__APPLE__) || defined(__MACH__)
#error "Beep not supported on apple"
#elif defined(__unix__) || defined(__unix)
#include "impl/linux.h"
#else
#error "Beep is not supported on this platform"
#endif
