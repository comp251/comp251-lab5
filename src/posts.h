#ifndef __POSTS_H__
#define __POSTS_H__

#include <stdlib.h>
#include <wchar.h>

#include "users.h"

#define MAX_POST_LEN 1024

// A post
typedef struct post {
  unsigned int id;
  char user_name[MAX_USERNAME_LEN]; // users's name
  wchar_t display_icon;             // icon to display for owner
  char text[MAX_POST_LEN];          // post text
  int n_children;                   // number of child posts (comments)
  int karma;                        // post karma (positive or negative)
  struct post **child;              // array of pointers to child posts
  struct post *parent;              // parent post (NULL if top-level)
} post_t;

// Iterator over posts
typedef struct post_iter {
  post_t *post;
} post_iter_t;

// Initialize the post database.
void init_posts(int max_posts);

// Destroy the post database.
void destroy_posts();

// Create a new post.
//
// If parent is null, create a new root post. If parent is non-null, creates a
// child post of the given parent.
post_t *add_post(post_t *parent, post_t *child);

// Lookup a post given an id.
//
// Returns NULL if post does not exist.
post_t *lookup_post(unsigned int post_id);

// Get an iterator for a post.
//
// A NULL post gives the iterator to root posts.
//
// A non-null post gives an iterator to child posts.
//
// Returns NULL if there are no posts or no child posts for the given post.
post_iter_t *post_iter(post_t *post);

// Advance an iterator.
//
// Returns cur, or NULL if there are no more entries.
//
// Frees cur if there are no more entries.
post_iter_t *post_next(post_iter_t *cur);

#endif
