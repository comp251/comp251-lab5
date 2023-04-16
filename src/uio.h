#ifndef __UIO_H__
#define __UIO_H__

#include <stdlib.h>

// Reads a line from fd into buff, including newline character (\n).
//
// buff_size must be at least 2 (to read at least one char and \0).
//
// Reads until buff_size chars have been read, EOF, or end of line.
//
// Returns number of bytes read, not including the null terminator, or -1 if
// there was an unrecoverable error.
size_t uio_readline(char *buff, size_t buff_size, int fd);

// Writes buff_size bytes from buff to fd.
//
// Retries writes. If fd is of bounded size, there must be enough room left in
// fd for buff_size bytes; otherwise, the function will block forever.
//
// Returns the number of bytes written, or -1 if there was an unrecoverable
// error.
size_t uio_write(char *buff, size_t buff_size, int fd);

#endif
