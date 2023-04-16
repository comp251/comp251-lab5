#include "../rr_core.h"

#include <locale.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "test_utils.h"

int test_register_user() {
  rr_service_init();

  EXPECT_TRUE(rr_register("garfield", 1234));

  rr_service_destroy();
  return 0;
}

int test_register_get_user() {
  rr_service_init();

  struct rr_user user;
  unsigned int token = rr_register("garfield", 1234);

  EXPECT_UINT_NEQ(0, token);
  EXPECT_TRUE(rr_get_user_info(token, &user));
  EXPECT_UINT_EQ(0, user.karma);

  rr_service_destroy();
  return 0;
}

int test_post() {
  rr_service_init();

  char msg[1024] = "hello world";
  unsigned int token = rr_register("garfield", 1234);

  // should be able to post
  EXPECT_TRUE(rr_add_post(token, msg));

  // post should be retrieved
  struct rr_post **posts = NULL;
  int n_posts = rr_get_posts(token, &posts);
  EXPECT_INT_EQ(1, n_posts);
  EXPECT_STR_EQ(msg, posts[0]->text);
  EXPECT_UINT_NEQ(0, posts[0]->post_id);

  // User icon should match
  struct rr_user user;
  EXPECT_TRUE(rr_get_user_info(token, &user));
  EXPECT_UINT_EQ(posts[0]->icon, user.icon);

  free(posts[0]);
  free(posts);

  rr_service_destroy();
  return 0;
}

int test_post_karma() {
  rr_service_init();

  char msg[1024] = "hello world";
  unsigned int token = rr_register("garfield", 1234);

  rr_add_post(token, msg);
  struct rr_post **posts = NULL;
  rr_get_posts(token, &posts);

  // register another user; upvote post, check, downvote post
  token = rr_register("john", 2345);

  rr_vote(token, posts[0]->post_id, 1);
  free(posts[0]);
  free(posts);
  posts = NULL;
  rr_get_posts(token, &posts);

  EXPECT_INT_EQ(1, posts[0]->karma);

  rr_vote(token, posts[0]->post_id, -1);
  free(posts[0]);
  free(posts);
  posts = NULL;
  rr_get_posts(token, &posts);

  EXPECT_INT_EQ(0, posts[0]->karma);

  free(posts[0]);
  free(posts);

  rr_service_destroy();
  return 0;
}

int test_comment() {
  rr_service_init();

  char msg[1024] = "hello world";
  unsigned int token = rr_register("garfield", 1234);

  rr_add_post(token, msg);
  struct rr_post **posts = NULL;
  rr_get_posts(token, &posts);

  // register another user; upvote post, check, downvote post
  token = rr_register("john", 2345);

  unsigned int post_id = posts[0]->post_id;
  strcpy(msg, "wow so original.");
  rr_add_comment(token, post_id, msg);
  free(posts[0]);
  free(posts);
  posts = NULL;
  int n_comments = rr_get_comments(token, post_id, &posts);

  struct rr_user user;
  EXPECT_TRUE(rr_get_user_info(token, &user));

  EXPECT_INT_EQ(1, n_comments);
  EXPECT_STR_EQ("wow so original.", posts[0]->text);
  EXPECT_UINT_EQ(posts[0]->icon, user.icon);

  free(posts[0]);
  free(posts);
  posts = NULL;

  rr_service_destroy();
  return 0;
}

int test_comment_karma() {
  rr_service_init();

  char msg[1024] = "hello world";
  unsigned int ptoken = rr_register("garfield", 1234);

  rr_add_post(ptoken, msg);
  struct rr_post **posts = NULL;
  rr_get_posts(ptoken, &posts);

  // register another user; upvote post, check, downvote post
  unsigned int ctoken = rr_register("john", 2345);

  unsigned int post_id = posts[0]->post_id;
  strcpy(msg, "wow so original.");
  rr_add_comment(ctoken, post_id, msg);

  free(posts[0]);
  free(posts);
  posts = NULL;
  rr_get_comments(ctoken, post_id, &posts);

  // upvote comment
  rr_vote(ptoken, posts[0]->post_id, 1);

  // get comments again
  free(posts[0]);
  free(posts);
  posts = NULL;
  rr_get_comments(ctoken, post_id, &posts);

  struct rr_user user;
  EXPECT_TRUE(rr_get_user_info(ctoken, &user));
  EXPECT_UINT_EQ(1, user.karma);

  free(posts[0]);
  free(posts);
  posts = NULL;

  rr_service_destroy();
  return 0;
}

int test_foo() {
  rr_service_init();

  rr_service_destroy();
  return 0;
}

int main() {
  setlocale(LC_ALL, "");
  time_t t = time(NULL);
  // time_t t = 1678516687;
  srand(t);
  printf("seed %ld\n", t);
  ADD_TEST(test_register_user);
  ADD_TEST(test_register_get_user);
  ADD_TEST(test_post);
  ADD_TEST(test_post_karma);
  ADD_TEST(test_comment);
  ADD_TEST(test_comment_karma);

  return run_tests(/*fail_fast=*/1, /*clean_after=*/1);
}
