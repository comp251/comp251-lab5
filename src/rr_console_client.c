#include <assert.h>
#include <errno.h>
#include <locale.h>
#include <netdb.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <wchar.h>

#include <arpa/inet.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <sys/types.h>

#include "conn.h"
#include "rr_client_lib.h"
#include "uio.h"
#include "util.h"

#define BUFF_LEN 4096
#define FNAME_LEN 512

void usage() {
  printf("Terminal UI for Rhodes Ramble\n");
  printf("commands:\n"
         "\t\tl <name> <pin> register user with given name and pin (this is "
         "your password/id)\n"
         "\t\tg              get all messages\n"
         "\t\tu <id>         upvote message/comment with given id\n"
         "\t\td <id>         downvote message/comment with given id\n"
         "\t\tp <text>       post message with given text\n"
         "\t\tc <id> <text>  comment on message with given id\n"
         "\t\tm <id>         get message comments for message with given id\n"
         "\t\ti              get your user info\n"
         "\t\tq              quit\n"
         "\t\t?              print this message\n");
}

void print_posts(struct rr_client_post_t **posts, int max_len) {
  char buffer[BUFF_LEN];
  for (int i = 0; i < max_len && posts[i]; i++) {
    snprintf(buffer, BUFF_LEN, " %d > (%d) %lc %s\n", posts[i]->id,
             posts[i]->karma, posts[i]->icon, posts[i]->text);
    printf("%s", buffer);
  }
}

int main(int argc, char *argv[]) {
  char tok_fname[FNAME_LEN];
  char buffer[BUFF_LEN];
  unsigned int token = 0;
  unsigned int id;
  int dir;
  char *name, *pin, *text;
  struct rr_client_post_t **posts =
      malloc(RR_MAX_POSTS * sizeof(struct rr_client_post_t *));
  struct rr_client_user_info_t user;
  int ok;
  FILE *f;
  int nocache = argc > 3 && strcmp(argv[3], "-nocache") == 0;

  setlocale(LC_ALL, "");

  cat_home_dir(tok_fname, FNAME_LEN, RR_TOKEN_CACHE_FN);
  // Read cached token, if any
  if (nocache) {
    // skip reading token
    printf("skipping reading token from %s...\n", tok_fname);
  } else {
    printf("trying to read token from %s...\n", tok_fname);
    f = fopen(tok_fname, "r");
    if (f) {
      fgets(buffer, BUFF_LEN, f);
      token = strtoul(buffer, NULL, 10);
      printf("Got cached token %u\n", token);
      fclose(f);
    } else {
      printf("not found.\n");
    }
  }

  // Connect to service
  int sockfd = conn_connect(argv[1], argv[2]);

  usage();
  printf("> ");
  while (fgets(buffer, BUFF_LEN, stdin) != NULL) {
    buffer[strnlen(buffer, BUFF_LEN) - 1] = '\0';
    switch (buffer[0]) {

    case 'l':
      // login
      name = strchr(buffer, ' ') + 1;
      pin = strchr(name, ' ') + 1;
      ok = do_login(sockfd, name, pin, &token);
      if (ok < 0) {
        printf("Error logging in with %s/%s\n", name, pin);
        break;
      }
      printf("got token %u\n", token);
      if (nocache) {
        // skip caching token
        printf("skipping caching token to %s...\n", tok_fname);
      } else {
        // cache token to file
        f = fopen(tok_fname, "w");
        if (!f) {
          printf("error saving token\n");
          break;
        }
        fprintf(f, "%u\n", token);
        fclose(f);
        printf("token cached to %s...\n", tok_fname);
      }
      break;

    case 'g':
      // get posts
      ok = get_posts(sockfd, token, posts, RR_MAX_POSTS);
      if (ok < 0) {
        printf("error getting posts\n");
        break;
      }
      print_posts(posts, RR_MAX_POSTS);
      free_posts(posts, RR_MAX_POSTS);
      break;

    case 'm':
      // get comments
      id = strtoul(strchr(buffer, ' '), NULL, 10);
      ok = get_comments(sockfd, token, id, posts, RR_MAX_POSTS);
      if (ok < 0) {
        printf("error getting comments for post %u\n", id);
        break;
      }
      print_posts(posts, RR_MAX_POSTS);
      free_posts(posts, RR_MAX_POSTS);
      break;

    case 'p':
      // post a new message
      text = strchr(buffer, ' ') + 1;
      ok = do_post(sockfd, token, text);
      if (ok < 0) {
        printf("error adding post\n");
      }
      break;

    case 'c':
      // post a new comment
      id = strtoul(strchr(buffer, ' '), &text, 10);
      ok = do_comment(sockfd, token, id, text);
      if (ok < 0) {
        printf("error adding comment for post id %u\n", id);
      }
      break;

    case 'u':
    case 'd':
      // vote
      dir = buffer[0] == 'u' ? RR_UPVOTE : RR_DOWNVOTE;
      id = strtoul(strchr(buffer, ' '), NULL, 10);
      ok = do_vote(sockfd, token, id, dir);
      if (ok < 0) {
        printf("error voting %d on post %u\n", dir, id);
      }
      break;

    case 'i':
      // get user info
      ok = get_user_info(sockfd, token, &user);
      if (ok < 0) {
        printf("error getting user info\n");
        break;
      }
      printf("icon/karma: %lc/%d\n", user.icon, user.karma);
      break;

    case 'q':
      free(posts);
      close(sockfd);
      return 0;

    default:
      usage();
      break;
    }
    printf("> ");
  }

  return 0;
}
