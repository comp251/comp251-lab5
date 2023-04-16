#ifndef __RR_CLIENT_LIB_H__
#define __RR_CLIENT_LIB_H__

#include <wchar.h>

// Client library for Rhodes Ramble clients. Implements the Rhodes Ramble client
// protocol.
//
// Provides basic types for display of posts/user info.
//
// Provides basic functions for executing commands against the service protocol.

// Constants that can be used by clients for buffer lengths/sizes.
#define RR_TOKEN_CACHE_FN ".rr_token"
#define RR_MAX_POST_LEN 1000
#define RR_MAX_POSTS 256
#define RR_UPVOTE 1
#define RR_DOWNVOTE (-1)
#define RR_MAX_USERNAME_LEN 15

// A post/comment
struct rr_client_post_t {
  unsigned int id; // post id; use for vote/comment
  int karma;       // post karma
  wchar_t icon;    // icon associated with the post
  char *text;      // post text
};

// A user
struct rr_client_user_info_t {
  wchar_t icon; // user icon
  int karma;    // user karma
};

// Protocol implementation functions. All functions create and post a message to
// the Rhodes Ramble service.
//
// All functions return <0 on error.
//
// All functions expect the following:
// - conn should be a valid service fd (e.g., a client socket).
// - token should be a valid token returned by do_login (exception: do_login)

// Logs a user in or resets a user's icon. Grants a new token to be used in
// subsequent interactions.
//
// token is an out parameter and initialized with the value received from the
// service.
//
// Returns <0 on error.
int do_login(int conn, const char *name, const char *pin, unsigned int *token);

// Create a post.
//
// text is a string containing the post content.
//
// Returns <0 on error.
int do_post(int conn, unsigned int token, const char *text);

// Create a comment.
//
// parent is the id of the parent post and text is the comment text.
//
// Returns <0 on error.
int do_comment(int conn, unsigned int token, unsigned int parent,
               const char *text);

// Vote on a post or comment.
//
// id is the post/comment id. updown <0 is a downvote and >0 is an upvote.
//
// Returns <0 on error.
int do_vote(int conn, unsigned int token, unsigned int id, int up_down);

// Get all posts.
//
// posts must be a pointer to an array of pointers of length post_len. After the
// call, the indices of posts will contain pointers to all posts. The array is
// null-terminated.
//
// On success, the function returns the number of posts that were retrieved.
//
// Returns <0 on error.
int get_posts(int conn, unsigned int token, struct rr_client_post_t **posts,
              int posts_len);

// Get all comments on a post.
//
// parent should be the id of the post for which this comment should be added.
// posts must be a pointer to an array of pointers of length post_len. After the
// call, the indices of posts will contain pointers to all comments. The array
// is null-terminated.
//
// On success, the function returns the number of comments that were retrieved.
//
// Returns <0 on error.
int get_comments(int conn, unsigned int token, unsigned int parent,
                 struct rr_client_post_t **posts, int posts_len);

// Get info for the logged-in user granted the given token.
//
// user is an out parameter and will be initialized with user data.
//
// Returns <0 on error.
int get_user_info(int conn, unsigned int token,
                  struct rr_client_user_info_t *user);

// Convenience function for freeing posts.
//
// posts should be a null-terminated array of posts with a MAXIMUM length of
// len.
void free_posts(struct rr_client_post_t **posts, int posts_len);

#endif
