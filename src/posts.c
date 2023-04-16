#include "posts.h"

#include <assert.h>
#include <stdlib.h>
#include <string.h>

#include "lib/map.h"
#include "util.h"

#define LOOKUP_SIZE 1024

// Array of posts
post_t **posts = NULL;
map_t *ids = NULL;

int posts_size = 0;
int n_posts = 0;

#define ID_BUFF_LEN 32

// Internal iterator struct
struct post_iter_internal {
  struct post_iter iter; // embedded external struct; type can be used as
                         // external struct
  post_t *parent;
  int idx;
};

// Return unsigned int id as a string; returns pointer to static buffer, not
// threadsafe.
const char *idtoa(unsigned int tok) {
  static char buff[ID_BUFF_LEN];
  itoa(buff, ID_BUFF_LEN, tok);
  return buff;
}

void init_posts(int max_posts) {
  assert(!posts);
  posts = calloc(max_posts, sizeof(post_t *));
  ids = map_create(LOOKUP_SIZE);
  posts_size = max_posts;
  n_posts = 0;
}

void destroy_posts() {
  for (int i = 0; i < posts_size && i < n_posts; i++) {
    for (int j = 0; j < posts[i]->n_children; j++) {
      free(posts[i]->child[j]);
    }
    free(posts[i]->child);
    free(posts[i]);
  }
  free(posts);
  map_free(&ids);
  posts = NULL;
  n_posts = 0;
  posts_size = 0;
}

post_t *add_post(post_t *parent, post_t *child) {
  child->id = unique_int_key(ids);
  child->parent = parent;
  child->child = NULL;
  child->karma = 0;
  child->n_children = 0;
  post_t *ret = malloc(sizeof(post_t));
  memcpy(ret, child, sizeof(post_t));
  int pos;
  if (parent) {
    pos = parent->n_children;
    parent->n_children++;
    parent->child =
        realloc(parent->child, parent->n_children * sizeof(post_t *));
    parent->child[pos] = ret;
    map_put(ids, idtoa(child->id), ret);
    return ret;
  }
  pos = n_posts % posts_size; // compute post position
  if (n_posts >= posts_size) {
    // free earliest post
    for (int i = 0; i < posts[pos]->n_children; i++) {
      map_remove(ids, idtoa(posts[pos]->child[i]->id));
      free(posts[pos]->child[i]);
    }
    map_remove(ids, idtoa(posts[pos]->id));
    free(posts[pos]->child);
    free(posts[pos]);
  }
  posts[pos] = ret;
  map_put(ids, idtoa(child->id), ret);
  n_posts++;
  return ret;
}

post_t *lookup_post(unsigned int post_id) {
  post_t *post = NULL;
  map_get(ids, idtoa(post_id), (void **)&post);
  return post;
}

post_iter_t *post_iter(post_t *post) {
  struct post_iter_internal *it = malloc(sizeof(struct post_iter_internal));
  if (!n_posts || (post && !post->n_children)) {
    return NULL;
  }
  if (!post) {
    int pos = n_posts < posts_size ? 0 : n_posts % posts_size;
    it->idx = 0;
    it->parent = NULL;
    it->iter.post = posts[pos];
    return (post_iter_t *)it;
  }
  it->parent = post;
  it->idx = 0;
  it->iter.post = post->child[it->idx];
  return (post_iter_t *)it;
}

post_iter_t *post_next(post_iter_t *cur) {
  struct post_iter_internal *it = (struct post_iter_internal *)cur;
  it->idx++;
  if (it->parent) {
    if (it->idx >= it->parent->n_children) {
      free(cur);
      return NULL;
    }
    it->iter.post = it->parent->child[it->idx];
    return (post_iter_t *)it;
  }
  int len = (n_posts >= posts_size) ? posts_size : n_posts;
  int idx = n_posts < posts_size ? it->idx : (n_posts + it->idx) % posts_size;
  if (it->idx >= len) {
    free(cur);
    return NULL;
  }
  it->iter.post = posts[idx];
  return (post_iter_t *)it;
}
