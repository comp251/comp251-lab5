#ifndef __RR_CORE_H__
#define __RR_CORE_H__

#include <stdlib.h>
#include <wchar.h>

// Core of the Rhodes Ramble service. Implements the ramble/user storage layer
// and is used by the service to implement the core application logic.

struct rr_user {
  wchar_t icon;
  int karma;
};

struct rr_post {
  unsigned int post_id;
  wchar_t icon;
  int karma;
  char text[1024];
};

// Initialize the RR service
void rr_service_init();

// Destroy the RR service
void rr_service_destroy();

// Add a post.
//
// Returns post id (positive) on success; 0 on failure.
unsigned int rr_add_post(unsigned int token, char *post_text);

// Add a comment.
//
// Returns comment id (positive) on success; 0 on failure.
unsigned int rr_add_comment(unsigned int token, unsigned int post_id,
                            char *comment_text);

// Register a user.
//
// Returns user token on success; 0 on failure.
unsigned int rr_register(char *user_name, unsigned int pin);

// Retrieve a list of posts.
//
// posts will be allocated to store a list of pointers to posts. Must be NULL.
// caller takes ownership of this list and must free both the list and the
// posts.
//
// Returns the number of posts, or -1 on error.
int rr_get_posts(unsigned int token, struct rr_post ***posts);

// Retrieve a list of comments for a post.
//
// comments will be allocated to store a list of comments. Must be NULL.
// caller takes ownership of this list and must free both the list and the
// posts.
//
// Returns the number of comments, or -1 on error.
int rr_get_comments(unsigned int token, unsigned int post_id,
                    struct rr_post ***comments);

// Get user info.
//
// user should be a valid pointer and will be populated upon return.
//
// Returns 0 on failure; nonzero on success.
int rr_get_user_info(unsigned int token, struct rr_user *user);

// Vote for a post/comment.
//
// Returns nonzero on success.
int rr_vote(unsigned int voter_token, unsigned int post_id, int updown);

#endif
