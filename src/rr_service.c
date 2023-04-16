#include "rr_service.h"

#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <wchar.h>

#include <sys/socket.h>

#include "rr_core.h"
#include "uio.h"

void init_rr_service() {
  rr_service_init();
  // TODO: any initialization you would like
}

void destroy_rr_service() {
  // TODO: any cleanup you would like to do
}

void parse_and_dispatch(int response_fd, char *msg, int msg_len) {
  // TODO
}
