#include "conn.h"

#include <netdb.h>
#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>

int conn_connect(char *host, char *port) {
  int fd = -1;
  struct addrinfo addrinfo_hints;
  memset(&addrinfo_hints, 0, sizeof(struct addrinfo));
  addrinfo_hints.ai_socktype = SOCK_STREAM;
  addrinfo_hints.ai_family = AF_INET;
  addrinfo_hints.ai_flags = AI_NUMERICSERV | AI_ADDRCONFIG;

  struct addrinfo *res = NULL;
  if (getaddrinfo(host, port, &addrinfo_hints, &res) < 0) {
    // error; abort.
    return fd;
  }

  struct addrinfo *cur = res;
  while (cur) {
    fd = socket(cur->ai_family, cur->ai_socktype, cur->ai_protocol);
    if (fd >= 0) {
      // socket open; attempt to connect.
      if (connect(fd, cur->ai_addr, cur->ai_addrlen) == 0) {
        break;
      }
      perror("connect");
      // connect failed; close socket.
      close(fd);
    }
    // socket or connect failed.
    fd = -1;
    cur = cur->ai_next;
  }
  freeaddrinfo(res);
  return fd;
}

int conn_listen(char *port) {
  int fd = -1;
  struct addrinfo addrinfo_hints;
  memset(&addrinfo_hints, 0, sizeof(struct addrinfo));
  addrinfo_hints.ai_socktype = SOCK_STREAM;
  addrinfo_hints.ai_family = AF_INET;
  addrinfo_hints.ai_flags = AI_NUMERICSERV | AI_ADDRCONFIG | AI_PASSIVE;

  struct addrinfo *res = NULL;
  if (getaddrinfo(NULL, port, &addrinfo_hints, &res) < 0) {
    // error; abort.
    return fd;
  }

  struct addrinfo *cur = res;
  while (cur) {
    fd = socket(cur->ai_family, cur->ai_socktype, cur->ai_protocol);
    if (fd >= 0) {
      // socket open; attempt to bind.
      int optval = 1;
      setsockopt(fd, SOL_SOCKET, SO_REUSEADDR, (const void *)&optval,
                 sizeof(int));
      if (bind(fd, cur->ai_addr, cur->ai_addrlen) == 0) {
        break;
      }
      perror("bind");
      // bind failed; close socket.
      close(fd);
    }
    // listen or bind failed.
    fd = -1;
    cur = cur->ai_next;
  }
  freeaddrinfo(res);
  if (fd > 0) {
    if (listen(fd, DEFAULT_QUEUE_DEPTH) < 0) {
      perror("listen");
      close(fd);
      fd = -1;
    }
  }
  return fd;
}
