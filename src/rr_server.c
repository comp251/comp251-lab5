#include <locale.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>

#include <pthread.h>

#include <netinet/in.h>
#include <sys/socket.h>
#include <sys/types.h>

#include <arpa/inet.h>

#include <netdb.h>

#include "conn.h"
#include "rr_service.h"
#include "uio.h"

#define MAX_CONN 1024
#define BUFFER_SIZE 2048
#define HOST_PORT_LEN 256
#define BACKLOG 1024

// Handles a connection from a client; reads requests and delegates responding
// to the rr_service (via parse_and_dispatch).
void handle(int sock, struct sockaddr_storage *addr) {
  char host[HOST_PORT_LEN];
  char port[HOST_PORT_LEN];
  char inbuff[BUFFER_SIZE];
  int msz;
  // get the client name to display.
  getnameinfo((struct sockaddr *)addr, sizeof(struct sockaddr_storage), host,
              HOST_PORT_LEN, port, HOST_PORT_LEN, 0);
  printf("connection from %s:%s\n", host, port);

  // read a line from the client until EOF.
  while (msz = uio_readline(inbuff, BUFFER_SIZE, sock), msz > 0) {
    // chop off the \n.
    inbuff[msz] = '\0';

    // echo the client request for logging.
    printf("%s> %s", host, inbuff);

    // dispatch handling of the message to rr_service.
    parse_and_dispatch(sock, inbuff, msz);
  }

  // goodbye 🥹
  printf("%s:%s disconnected\n", host, port);
  close(sock);
}

int main(int argc, char **argv) {
  srand(time(NULL)); // remove to seed with a fixed value
  // srand(42);
  setlocale(LC_ALL, "");

  // Initialize the service layer
  init_rr_service();

  // Ensure that we were given a port to listen on in argv[1]
  if (argc < 2) {
    fprintf(stderr,
            "Usage: %s PORT\n\nStarts Rhodes Ramble server listening on the "
            "given port PORT.\n",
            argv[0]);
    exit(1);
  }

  // TODO: create a server socket! (use conn.h functions)
  int conn = -1;
  if (conn < 0) {
    fprintf(stderr, "Error listening on %s\n", argv[1]);
  }
  printf("listening on %s...\n", argv[1]);

  while (1) {
    socklen_t csz = sizeof(struct sockaddr_storage);
    struct sockaddr_storage *caddr = malloc(csz);

    // TODO: accept a connection from a client!
    int client = -1;

    if (client < 0) {
      // handle accept error.
      perror("accept");
      free(caddr);
      continue;
    }

    // enter client handling loop.
    handle(client, caddr);

    // clean up client resources.
    free(caddr);
  }

  return 0;
}
