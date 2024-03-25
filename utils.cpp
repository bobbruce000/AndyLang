#include <cassert>
#include <cerrno>
#include <fcntl.h>
#include <cstdarg>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <sys/stat.h>
#include <unistd.h>

#include "utils.hpp"

void fatal(const char *const fmt, ...) {
  va_list args;

  assert(fmt != NULL);
  va_start(args, fmt);
  vfprintf(stderr, fmt, args);
  fprintf(stderr, "\n");
  va_end(args);
  exit(1);
}

const char *syserr(void) { return strerror(errno); }

char *Readfile(const char *const fn, uint32_t *size) {
  struct stat statbuf;
  uint32_t filesize;
  int32_t fd;
  char *data;

  if ((fd = open(fn, O_RDONLY)) < 0) {
    fatal("Readfile: Cannot open %s: %s", fn, syserr());
  }
  if (fstat(fd, &statbuf) != 0) {
    fatal("Cannot stat %s: %s", fn, syserr());
  }
  filesize = (size_t)statbuf.st_size;
  // lint -e{925}        Cast from pointer to pointer
  data = (char *)malloc(filesize + 1);
  assert(data != NULL);
  data[filesize] = '\0';
  if (read(fd, data, (size_t)filesize) != (ssize_t)filesize) {
    fatal("read error, %s: %s", fn, syserr());
  }
  close(fd);
  if (size != NULL) {
    *size = filesize;
  }
  return data;
}
