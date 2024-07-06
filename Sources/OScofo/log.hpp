#pragma once

#include <iostream>
#include <sstream>

#define SCOFO_DEBUG true

#if SCOFO_DEBUG
class LogStream {
  public:
    template <typename T> LogStream &operator<<(const T &value) {
        buffer << value;
        return *this;
    }

    ~LogStream() {
        std::string message = buffer.str();
        const char *c_message = message.c_str();
        printf("%s\n", c_message);
        std::cout.flush();
    }

  private:
    std::ostringstream buffer;
};

#define LOGE() LogStream()
#else
#define LOGE()                                                                                     \
    if (0)                                                                                         \
    std::cerr
#endif
