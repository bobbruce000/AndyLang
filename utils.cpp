#include <cassert>
#include <cerrno>
#include <cstdarg>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <fstream>
#include <vector>

#include "utils.hpp"

[[noreturn]] void fatal(const char *const fmt, ...) {
  va_list args;

  assert(fmt != NULL);
  va_start(args, fmt);
  vfprintf(stderr, fmt, args);
  fprintf(stderr, "\n");
  va_end(args);
  exit(1);
}

const char *syserr(void) { return strerror(errno); }

std::vector<char> Readfile(char *fn) {
  std::ifstream stream = std::ifstream(fn, std::ios::binary);
  if (stream) {
    std::vector<char> buffer =
        std::vector<char>(std::istreambuf_iterator<char>(stream), {});
    buffer.push_back(0);
    return buffer;
  }
  fatal("failed to open file: %s\n", fn);
}
