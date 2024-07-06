#include <iostream>

// Define a macro to enable or disable logging
#define SCOFO_DEBUG true

#ifdef SCOFO_DEBUG
#define LOGE() std::cerr
#else
#define LOGE()                                                                                     \
    if (0)                                                                                         \
    std::cerr
#endif
