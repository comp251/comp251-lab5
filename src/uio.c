#include "uio.h"

#include <errno.h>
#include <stdio.h>
#include <unistd.h>

size_t uio_readline(char *buff, size_t buff_size, int fd) {
  size_t n = 0;
  if (!buff || buff_size < 2) {
    errno = EINVAL;
    return -1;
  }
  char c; // read buffer
  while (1) {
    int nc = read(fd, &c, 1);
    if (nc < 0) {
      if (errno != EINTR) {
        // an unrecoverable error occurred.
        return -1;
      }
    } else if (!nc) {
      // end of file
      break;
    } else {
      // read a character; append
      buff[n++] = c;
      if (c == '\n') {
        break;
      }
    }
    if (n >= buff_size - 1) {
      break;
    }
  }
  // terminate buffer; since buff_size is at least 2, we break at n >=
  // buff_size - 1, and we only increase n by at most one each iteration, we are
  // guaranteed there is room in buff.
  buff[n] = '\0';
  return n;
}

size_t uio_write(char *buff, size_t buff_size, int fd) {
  size_t n = 0;
  if (!buff || !buff_size) {
    errno = EINVAL;
    return -1;
  }
  char *b = buff; // write cursor
  while (n < buff_size) {
    int nc = write(fd, b, buff_size - n);
    if (nc <= 0) {
      if (errno != EINTR) {
        // an unrecoverable error occurred.
        return -1;
      }
      // reset and try again.
      nc = 0;
    }
    b += nc;
    n += nc;
  }
  return n;
}
