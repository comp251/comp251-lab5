#include <locale.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "../posts.h"
#include "../util.h"
#include "test_utils.h"

#define BUFF_LEN 64

post_t *make_post(unsigned int id, char *text) {
  post_t *post = malloc(sizeof(post_t));
  sprintf(post->user_name, "%u", id);
  post->display_icon = id + 1;
  strcpy(post->text, text);
  return post;
}

int test_create() {
  init_posts(5);
  destroy_posts();
  return 0;
}

int test_add_root_post() {
  init_posts(5);

  post_t *tmp = make_post(1234, "hello");
  post_t *post = add_post(NULL, tmp);
  free(tmp);
  EXPECT_NOTNULL(post);

  EXPECT_STR_EQ("1234", post->user_name);
  EXPECT_UINT_EQ(1235, post->display_icon);
  EXPECT_UINT_NEQ(0, post->id);
  EXPECT_STR_EQ("hello", post->text);

  destroy_posts();
  return 0;
}

int test_add_root_post_iter() {
  init_posts(5);

  post_t *tmp = make_post(1234, "hello");
  add_post(NULL, tmp);
  free(tmp);

  post_iter_t *it = post_iter(NULL);
  EXPECT_NOTNULL(it);
  EXPECT_STR_EQ("1234", it->post->user_name);
  EXPECT_UINT_EQ(1235, it->post->display_icon);
  EXPECT_UINT_NEQ(0, it->post->id);
  EXPECT_STR_EQ("hello", it->post->text);
  EXPECT_NULL(post_next(it));

  destroy_posts();
  return 0;
}

int test_add_root_posts() {
  init_posts(5);
  int n_posts = 5;
  char buff[BUFF_LEN];

  for (int i = 0; i < n_posts; i++) {
    itoa(buff, BUFF_LEN, i);
    post_t *tmp = make_post(i + 1, buff);
    add_post(NULL, tmp);
    free(tmp);
  }

  post_iter_t *it = post_iter(NULL);
  for (int i = 0; i < n_posts; i++) {
    EXPECT_NOTNULL(it);
    itoa(buff, BUFF_LEN, i);
    EXPECT_STR_EQ(buff, it->post->text);
    snprintf(buff, BUFF_LEN, "%d", i + 1);
    EXPECT_STR_EQ(buff, it->post->user_name);
    EXPECT_UINT_EQ(i + 2, it->post->display_icon);
    EXPECT_UINT_NEQ(0, it->post->id);
    if (i < n_posts - 1) {
      EXPECT_NOTNULL(post_next(it));
    } else {
      EXPECT_NULL(post_next(it));
    }
  }

  destroy_posts();
  return 0;
}

int test_add_many_root_posts() {
  int size = 7;
  int n_posts = 34;
  init_posts(size);
  char buff[BUFF_LEN];

  for (int i = 0; i < n_posts; i++) {
    itoa(buff, BUFF_LEN, i);
    post_t *tmp = make_post(i + 1, buff);
    add_post(NULL, tmp);
    free(tmp);
  }

  post_iter_t *it = post_iter(NULL);
  for (int i = n_posts - size; i < n_posts; i++) {
    EXPECT_NOTNULL(it);
    itoa(buff, BUFF_LEN, i);
    EXPECT_STR_EQ(buff, it->post->text);
    snprintf(buff, BUFF_LEN, "%d", i + 1);
    EXPECT_STR_EQ(buff, it->post->user_name);
    EXPECT_UINT_EQ(i + 2, it->post->display_icon);
    EXPECT_UINT_NEQ(0, it->post->id);
    if (i < n_posts - 1) {
      EXPECT_NOTNULL(post_next(it));
    } else {
      EXPECT_NULL(post_next(it));
    }
  }

  destroy_posts();
  return 0;
}

int test_lookup_post() {
  init_posts(5);

  post_t *tmp = make_post(1234, "hello");
  post_t *post = add_post(NULL, tmp);
  free(tmp);

  post_t *pos = lookup_post(post->id);
  EXPECT_PTR_EQ(post, pos);
  // Redundant...
  EXPECT_NOTNULL(pos);
  EXPECT_STR_EQ("1234", pos->user_name);
  EXPECT_UINT_EQ(1235, pos->display_icon);
  EXPECT_UINT_NEQ(0, pos->id);
  EXPECT_STR_EQ("hello", pos->text);

  destroy_posts();
  return 0;
}

int test_lookup_post_not_exist() {
  init_posts(5);

  post_t *tmp = make_post(1234, "hello");
  post_t *post = add_post(NULL, tmp);
  free(tmp);

  post_t *pos = lookup_post(post->id + 1);
  EXPECT_NULL(pos);

  destroy_posts();
  return 0;
}

int test_add_many_lookup_many() {
  int size = 7;
  post_t **posts = malloc(size * sizeof(post_t *));
  int n_posts = 34;
  unsigned int *ids = malloc(n_posts * sizeof(unsigned int));
  init_posts(size);
  char buff[BUFF_LEN];

  for (int i = 0; i < n_posts; i++) {
    itoa(buff, BUFF_LEN, i);
    post_t *tmp = make_post(i + 1, buff);
    posts[i % size] = add_post(NULL, tmp);
    free(tmp);
    ids[i] = posts[i % size]->id;
  }

  for (int i = 0; i < size; i++) {
    post_t *post = lookup_post(posts[i]->id);
    EXPECT_PTR_EQ(posts[i], post);
    // Redundant...
    EXPECT_NOTNULL(post);
    EXPECT_STR_EQ(posts[i]->user_name, post->user_name);
    EXPECT_UINT_EQ(posts[i]->display_icon, post->display_icon);
    EXPECT_UINT_NEQ(0, post->id);
    EXPECT_STR_EQ(posts[i]->text, post->text);
  }

  for (int i = 0; i < n_posts; i++) {
    if (i < n_posts - size) {
      EXPECT_NULL(lookup_post(ids[i]));
    } else {
      EXPECT_NOTNULL(lookup_post(ids[i]));
    }
  }

  free(posts);
  free(ids);

  destroy_posts();
  return 0;
}

post_t *make_posts(post_t *parent, int n) {
  char buff[BUFF_LEN];
  post_t *post = NULL;
  for (int i = 0; i < n; i++) {
    itoa(buff, 10, i);
    post_t *tmp = make_post(i + 1, buff);
    post = add_post(parent, tmp);
    free(tmp);
  }
  return post;
}

int test_add_comment() {
  init_posts(5);
  post_t *post = make_posts(NULL, 2);
  post = make_posts(post, 1);
  EXPECT_NOTNULL(post);
  EXPECT_NOTNULL(post->parent);
  EXPECT_STR_EQ("2", post->parent->user_name);
  EXPECT_STR_EQ("1", post->user_name);
  EXPECT_STR_EQ("0", post->text);
  destroy_posts();
  return 0;
}

int test_add_comment_lookup() {
  init_posts(5);
  post_t *parent = make_posts(NULL, 3);
  post_t *comment = make_posts(parent, 3);
  post_t *lookup = lookup_post(comment->id);
  EXPECT_PTR_EQ(comment, lookup);
  EXPECT_PTR_EQ(parent, lookup->parent);
  destroy_posts();
  return 0;
}

int test_add_comment_iter() {
  char buff[BUFF_LEN];
  int n_posts = 7;
  init_posts(5);
  post_t *parent = make_posts(NULL, 3);
  make_posts(parent, n_posts);

  post_iter_t *iter = post_iter(parent);
  for (int i = 0; i < n_posts; i++) {
    EXPECT_PTR_EQ(parent, iter->post->parent);
    itoa(buff, BUFF_LEN, i);
    EXPECT_STR_EQ(buff, iter->post->text);
    itoa(buff, BUFF_LEN, i + 1);
    EXPECT_STR_EQ(buff, iter->post->user_name);
    EXPECT_UINT_EQ(i + 2, iter->post->display_icon);
    if (i < n_posts - 1) {
      EXPECT_NOTNULL(post_next(iter));
    } else {
      EXPECT_NULL(post_next(iter));
    }
  }

  destroy_posts();
  return 0;
}

int test_many_posts_many_comments() {
  // add many posts and many comments on each post
  char buff[BUFF_LEN];
  int posts_size = 10;
  int n_posts = 15;
  int n_comments = 32;
  // Expect the first n_posts - posts_size to be freed.
  unsigned int *post_ids = malloc(n_posts * sizeof(unsigned int));
  // Expect the first n_comments / 2 * (n_posts - posts_size) to be freed.
  unsigned int *comment_ids =
      malloc(n_comments * n_posts * sizeof(unsigned int));
  init_posts(posts_size);

  int c_idx = 0;
  for (int i = 0; i < n_posts; i++) {
    itoa(buff, BUFF_LEN, i);
    post_t *tmp = make_post(i, buff);
    post_t *post = add_post(NULL, tmp);
    free(tmp);
    post_ids[i] = post->id;
    // add half comments now
    for (int j = 0; j < n_comments / 2; j++) {
      itoa(buff, BUFF_LEN, i * 100 + j);
      tmp = make_post(j, buff);
      post_t *c = add_post(post, tmp);
      free(tmp);
      // comment_ids[i * (n_comments / 2) + j] = c->id;
      comment_ids[c_idx++] = c->id;
    }
  }

  // validate the uniqueness of ids.
  for (int i = 0; i < n_posts; i++) {
    for (int j = 0; j < n_posts; j++) {
      if (i == j) {
        continue;
      }
      EXPECT_UINT_NEQ(post_ids[i], post_ids[j]);
    }
    for (int j = 0; j < n_comments; j++) {
      EXPECT_UINT_NEQ(post_ids[i], comment_ids[j]);
    }
  }
  for (int i = 0; i < n_comments; i++) {
    for (int j = 0; j < n_comments; j++) {
      if (i == j) {
        continue;
      }
      EXPECT_UINT_NEQ(comment_ids[i], comment_ids[j]);
    }
    for (int j = 0; j < n_posts; j++) {
      EXPECT_UINT_NEQ(comment_ids[i], post_ids[j]);
    }
  }

  // only the last posts_size posts should be valid, and their pins should start
  // at n_posts - post_size.
  //
  // validate that lookups are correct for these.
  for (int i = 0; i < n_posts; i++) {
    if (i < n_posts - posts_size) {
      EXPECT_NULL(lookup_post(post_ids[i]));
    } else {
      EXPECT_NOTNULL(lookup_post(post_ids[i]));
    }
  }
  for (int i = 0; i < n_posts * (n_comments / 2); i++) {
    if (i < (n_posts - posts_size) * (n_comments / 2)) {
      EXPECT_NULL(lookup_post(comment_ids[i]));
    } else {
      EXPECT_NOTNULL(lookup_post(comment_ids[i]));
    }
  }

  // lookups worked correctly. now iterate over all posts once, adding comments
  // to each root post.
  int pid = 0;
  post_iter_t *it;
  for (pid = n_posts - posts_size, it = post_iter(NULL); it;
       it = post_next(it), pid++) {
    snprintf(buff, BUFF_LEN, "%d", pid);
    EXPECT_STR_EQ(buff, it->post->user_name);
    for (int i = n_comments / 2; i < n_comments; i++) {
      itoa(buff, BUFF_LEN, pid * 100 + i);
      post_t *tmp = make_post(i, buff);
      post_t *c = add_post(it->post, tmp);
      free(tmp);
      // comment_ids[n_comments / 2 * n_posts +
      //             (pid - n_posts - posts_size) * n_comments / 2 + i] = c->id;
      comment_ids[c_idx++] = c->id;
    }
  }

  // now iterate over all posts and comments, validating posts and comments.
  int valid_posts = 0;
  for (pid = n_posts - posts_size, it = post_iter(NULL); it;
       it = post_next(it), pid++) {
    snprintf(buff, BUFF_LEN, "%d", pid);
    EXPECT_STR_EQ(buff, it->post->user_name);
    int valid_comments = 0;
    post_iter_t *cit;
    for (cit = post_iter(it->post); cit; cit = post_next(cit)) {
      EXPECT_PTR_EQ(it->post, cit->post->parent);
      itoa(buff, BUFF_LEN, pid * 100 + valid_comments);
      EXPECT_STR_EQ(buff, cit->post->text);
      snprintf(buff, BUFF_LEN, "%d", valid_comments);
      EXPECT_STR_EQ(buff, cit->post->user_name);
      valid_comments++;
    }
    EXPECT_INT_EQ(n_comments, valid_comments);
    valid_posts++;
  }
  EXPECT_INT_EQ(posts_size, valid_posts);

  // whew.
  free(post_ids);
  free(comment_ids);
  destroy_posts();
  return 0;
}

int main() {
  setlocale(LC_ALL, "");
  time_t t = time(NULL);
  // time_t t = 1678516687;
  srand(t);
  printf("seed %ld\n", t);

  ADD_TEST(test_create);
  ADD_TEST(test_add_root_post);
  ADD_TEST(test_add_root_post_iter);
  ADD_TEST(test_add_root_posts);
  ADD_TEST(test_add_many_root_posts);
  ADD_TEST(test_lookup_post);
  ADD_TEST(test_lookup_post_not_exist);
  ADD_TEST(test_add_many_lookup_many);
  ADD_TEST(test_add_comment);
  ADD_TEST(test_add_comment_lookup);
  ADD_TEST(test_add_comment_iter);
  ADD_TEST(test_many_posts_many_comments);

  // run tests
  run_tests(/*fail_fast=*/1, /*clean_after=*/1);
  return 0;
}
