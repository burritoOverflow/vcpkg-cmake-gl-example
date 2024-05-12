#ifndef LOGGER_H
#define LOGGER_H

#include <cstdio>
#include <glm/fwd.hpp>
#include <glm/glm.hpp>
#include <string>

class Logger {
 public:
  Logger() = delete;

  // TODO - refactor this to be less redundant
  template <typename... Args>
  inline static void LogInfo(Args... args) {
    const char* OUT_GREEN = "\x1B[32m";
    std::fprintf(OUT_FD, "%sINFO: ", OUT_GREEN);
    std::fprintf(OUT_FD, args...);
    std::fflush(OUT_FD);
  }

  template <typename... Args>
  inline static void LogError(Args... args) {
    const char* OUT_RED = "\x1B[31m";
    std::fprintf(OUT_FD, "%sERROR: ", OUT_RED);
    std::fprintf(OUT_FD, args...);
    std::fflush(OUT_FD);
  }

 private:
  static FILE* OUT_FD;
};
#endif