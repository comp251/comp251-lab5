#include "rr_client_lib.h"

#include <errno.h>
#include <stdio.h>
#include <string.h>

#include "uio.h"
#include "util.h"

int do_login(int conn, const char *name, const char *pin, unsigned int *token) {
  return -1;
}

int do_post(int conn, unsigned int token, const char *text) { return -1; }

int do_comment(int conn, unsigned int token, unsigned int parent,
               const char *text) {
  return -1;
}

int do_vote(int conn, unsigned int token, unsigned int id, int up_down) {
  return -1;
}

int get_posts(int conn, unsigned int token, struct rr_client_post_t **posts,
              int posts_len) {
  return -1;
}

int get_comments(int conn, unsigned int token, unsigned int parent,
                 struct rr_client_post_t **posts, int posts_len) {
  return -1;
}

int get_user_info(int conn, unsigned int token,
                  struct rr_client_user_info_t *user) {
  return -1;
}

void free_posts(struct rr_client_post_t **posts, int posts_len) {
  for (int i = 0; i < posts_len && posts[i]; i++) {
    free(posts[i]->text);
    free(posts[i]);
  }
}
