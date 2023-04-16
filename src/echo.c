#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include <netinet/in.h>
#include <sys/socket.h>
#include <sys/types.h>

#include <arpa/inet.h>

#include <netdb.h>

#define BUFFER_SIZE 1024
#define BACKLOG 10

void dump_addr(struct sockaddr_in *addr) {
  char hbuff[INET6_ADDRSTRLEN];
  char sbuff[NI_MAXSERV];
  socklen_t addr_len = sizeof(*addr);
  if (getnameinfo((struct sockaddr *)addr, addr_len, hbuff, sizeof(hbuff),
                  sbuff, sizeof(sbuff), NI_NUMERICHOST)) {
    perror("getnameinfo");
    exit(1);
  }
  printf("\n\nListening on %s:%s\n", hbuff, sbuff);
}

void handle(int sock, struct sockaddr_in *addr) {
  dump_addr(addr);
  char inbuff[BUFFER_SIZE];
  int msz;
  while (msz = recv(sock, inbuff, BUFFER_SIZE, 0), msz > 0) {
    if (msz <= 0) {
      close(sock);
      printf("done\n");
      return;
    }
    inbuff[msz] = '\0';
    printf("> %s\n", inbuff);
    send(sock, inbuff, msz, 0);
  }
  printf("done\n");
  close(sock);
}

int main(int argc, char **argv) {

  struct sockaddr_in addr;
  memset(&addr, 0, sizeof(addr));
  addr.sin_family = AF_INET;
  addr.sin_port = htons(atoi(argv[1]));
  addr.sin_addr.s_addr = htonl(INADDR_ANY);

  int sock = socket(AF_INET, SOCK_STREAM, 0);
  if (bind(sock, (struct sockaddr *)&addr, sizeof(addr)) < 0) {
    perror("bind");
    exit(1);
  }

  if (listen(sock, BACKLOG) < 0) {
    perror("listen");
    exit(1);
  }
  int option = 1;
  setsockopt(sock, SOL_SOCKET, SO_REUSEADDR, &option, sizeof(option));

  dump_addr(&addr);

  while (1) {
    struct sockaddr_in caddr;
    socklen_t csz = sizeof(caddr);
    int c = accept(sock, (struct sockaddr *)&caddr, &csz);
    if (c < 0) {
      perror("accept");
      continue;
    }
    handle(c, &caddr);
  }

  return 0;
}
