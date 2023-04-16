#include "users.h"

#include "emojis.h"
#include "lib/map.h"
#include "util.h"

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define DEFAULT_DB_SIZE 1024

map_t *tokens = NULL; // map token -> user
map_t *users = NULL;  // map username -> user

#define TOK_BUFF_LEN 32

const char *toktoa(unsigned int tok) {
  static char buff[TOK_BUFF_LEN];
  itoa(buff, TOK_BUFF_LEN, tok);
  return buff;
}

void make_token(user_t *u) {
  // create random token
  do {
    u->token = rand();
    if (!u->token) {
      u->token++;
    }
  } while (map_get(tokens, toktoa(u->token), NULL));
}

void rand_icon(user_t *u) {
  // create random icon
  wchar_t old = u->icon;
  int idx = rand() % n_emoji();
  // make sure the new icon is not the old
  idx = emojis[idx] == old ? (idx + 1) % n_emoji() : idx;
  u->icon = emojis[idx];
}

void init_user_db() {
  assert(!tokens && !users); // must only be called once
  tokens = map_create(DEFAULT_DB_SIZE);
  users = map_create(DEFAULT_DB_SIZE);
}

void *free_el(const char *key, void *value) {
  free(value);
  return NULL;
}

void destroy_user_db() {
  // Removing all users from one map should free all users in another.
  map_apply(tokens, free_el);
  map_free(&tokens);
  map_free(&users);
}

int register_user(user_t *user) {
  user_t *u = NULL;
  map_get(users, user->user_name, (void **)&u);
  if (u) {
    // existing user; validate pin
    if (u->pin != user->pin) {
      return ERR_INVALID_TOKEN;
    }
    // remove from db, issue new token
    assert(map_remove(tokens, toktoa(u->token)));
  } else {
    // new user, allocate
    u = malloc(sizeof(user_t));
    // initialize all randomized user fields in template
    user->icon = L'\0';
    user->karma = 0;
    user->token = 0;
    // copy template user
    memcpy(u, user, sizeof(user_t));
  }
  // get a new token and icon
  make_token(u);
  rand_icon(u);
  // add new or replace existing
  map_put(users, u->user_name, u);
  map_put(tokens, toktoa(u->token), u);
  // overwrite parameter with all new user data
  *user = *u;
  return u->token;
}

int get_user(user_t *user) {
  user_t *u = NULL;
  map_get(tokens, toktoa(user->token), (void **)&u);
  if (!u) {
    return ERR_INVALID_TOKEN;
  }
  // user exists, copy to arg.
  assert(user->token == u->token);
  *user = *u;
  return TOKEN_OK;
}

int update_user_karma(user_t *user) {
  user_t *u = NULL;
  map_get(users, user->user_name, (void **)&u);
  if (!u) {
    return ERR_UNKNOWN_USER;
  }
  // user exists, update karma.
  u->karma += user->karma;
  return TOKEN_OK;
}
