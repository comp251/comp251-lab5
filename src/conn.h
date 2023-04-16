#ifndef __CONN_H__
#define __CONN_H__

#define DEFAULT_QUEUE_DEPTH 1024

int conn_connect(char *host, char *port);
int conn_listen(char *port);

#endif
