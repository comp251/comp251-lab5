#include "rr_core.h"

#include <stdlib.h>
#include <string.h>
#include <wchar.h>

#include "posts.h"
#include "users.h"

// Age out posts quickly
#define DEFAULT_POST_SIZE 20

// Initialize the RR service
void rr_service_init() {
  init_posts(DEFAULT_POST_SIZE);
  init_user_db();
}

// Destroy the RR service
void rr_service_destroy() {
  destroy_posts();
  destroy_user_db();
}

// Add a post.
//
// Returns post id (positive) on success; 0 on failure.
unsigned int rr_add_post(unsigned int token, char *post_text) {
  // validate user
  user_t user;
  user.token = token;
  if (get_user(&user) == ERR_INVALID_TOKEN) {
    return 0;
  }
  // make new post
  post_t post;
  strncpy(post.user_name, user.user_name, MAX_USERNAME_LEN);
  post.display_icon = user.icon;
  strncpy(post.text, post_text, MAX_POST_LEN);
  post_t *posted = add_post(NULL, &post);
  if (!posted) {
    return 0;
  }
  return posted->id;
}

// Add a comment.
//
// Returns comment id (positive) on success; 0 on failure.
unsigned int rr_add_comment(unsigned int token, unsigned int post_id,
                            char *comment_text) {
  // validate user
  user_t user;
  user.token = token;
  if (get_user(&user) == ERR_INVALID_TOKEN) {
    return 0;
  }
  // look up parent post
  post_t *parent = lookup_post(post_id);
  if (!parent) {
    return 0;
  }
  // make new post
  post_t post;
  strncpy(post.user_name, user.user_name, MAX_USERNAME_LEN);
  post.display_icon = user.icon;
  strncpy(post.text, comment_text, MAX_POST_LEN);
  post_t *posted = add_post(parent, &post);
  if (!posted) {
    return 0;
  }
  return posted->id;
}

// Register a user.
//
// Returns user token on success; 0 on failure.
unsigned int rr_register(char *user_name, unsigned int pin) {
  user_t user;
  strncpy(user.user_name, user_name, sizeof(user.user_name));
  user.pin = pin;
  register_user(&user);
  return user.token;
}

int get_posts_helper(struct rr_post ***posts, post_iter_t *it) {
  int n_posts = 0;
  int posts_size = 0;
  for (; it; it = post_next(it)) {
    if (n_posts >= posts_size) {
      posts_size = posts_size > 0 ? posts_size * 2 : 4;
      *posts = realloc(*posts, posts_size * sizeof(post_t *));
    }
    (*posts)[n_posts] = malloc(sizeof(struct rr_post));
    (*posts)[n_posts]->icon = it->post->display_icon;
    (*posts)[n_posts]->post_id = it->post->id;
    (*posts)[n_posts]->karma = it->post->karma;
    strncpy((*posts)[n_posts]->text, it->post->text, MAX_POST_LEN);
    n_posts++;
  }
  return n_posts;
}

// Retrieve a list of posts.
//
// comments will be allocated to store a list of comments. Must be NULL.
// caller takes ownership of this list and must free both the list and the
// posts.
//
// Returns the number of posts, or 0 on error.
int rr_get_posts(unsigned int token, struct rr_post ***posts) {
  // validate user
  user_t user;
  user.token = token;
  if (get_user(&user) == ERR_INVALID_TOKEN) {
    return -1;
  }
  // get iterator
  post_iter_t *it = post_iter(NULL);
  if (!it) {
    return -1;
  }
  return get_posts_helper(posts, it);
}

// Retrieve a list of comments for a post.
//
// comments will be allocated to store a list of comments. Must be NULL.
// caller takes ownership of this list and must free both the list and the
// posts.
//
// Returns the number of comments, or 0 on error.
int rr_get_comments(unsigned int token, unsigned int post_id,
                    struct rr_post ***comments) {
  // validate user
  user_t user;
  user.token = token;
  if (get_user(&user) == ERR_INVALID_TOKEN) {
    return -1;
  }
  // lookup post
  post_t *post = lookup_post(post_id);
  if (!post) {
    return -1;
  }
  // get iterator
  post_iter_t *it = post_iter(post);
  if (!it) {
    return -1;
  }
  return get_posts_helper(comments, it);
}

int rr_vote(unsigned int voter_token, unsigned int post_id, int updown) {
  user_t user;
  user.token = voter_token;
  if (get_user(&user) == ERR_INVALID_TOKEN) {
    return 0;
  }
  // get post, update karma
  post_t *post = lookup_post(post_id);
  if (!post) {
    return 0;
  }
  updown = updown > 0 ? 1 : -1;
  post->karma += updown;
  // get user, update karma
  memset(&user, 0, sizeof(user_t));
  strncpy(user.user_name, post->user_name, MAX_USERNAME_LEN);
  user.karma = updown;
  if (update_user_karma(&user) == ERR_INVALID_TOKEN) {
    return 0;
  }
  return 1;
}

// Get user info.
//
// user should be a valid pointer and will be populated upon return.
//
// Returns 0 on failure; nonzero on success.
int rr_get_user_info(unsigned int token, struct rr_user *user) {
  user_t u;
  u.token = token;
  if (get_user(&u) == ERR_INVALID_TOKEN) {
    return 0;
  }
  user->icon = u.icon;
  user->karma = u.karma;
  return 1;
}
