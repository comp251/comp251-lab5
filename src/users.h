#ifndef __USERS_H__
#define __USERS_H__

#include <wchar.h>

#define ERR_INVALID_TOKEN 0
#define ERR_INVALID_PIN -1
#define ERR_UNKNOWN_USER -2
#define TOKEN_OK 1

#define MAX_PIN_LEN 8
#define MAX_USERNAME_LEN 16

typedef struct user {
  char user_name[MAX_USERNAME_LEN]; // user name
  unsigned int pin;                 // pin
  unsigned int token;               // auth token
  wchar_t icon;                     // emoji icon
  int karma;                        // balance
} user_t;

// Initialize the user db.
void init_user_db();

// Destroy the user db.
void destroy_user_db();

// Register a new user or reset an existing user's token/icon.
//
//
// User must not be null and have the new user's pin populated.
// After the call, the rest of the parameters will be filled.
//
// Returns user's token, or <= 0 if there was an error.
int register_user(user_t *user);

// Retrieve an existing user without modification.
//
// User must not be null and must contain a token. User is looked up by token.
// After the call, the user will be populated with the user's icon and karma.
//
// Returns <= 0 if there was an error.
int get_user(user_t *user);

// Update a user's karma.
//
// The user name and karma must be present. The karma is treated as a delta and
// added to the user's karma.
//
// Returns <= 0 if there was an error.
int update_user_karma(user_t *user);

#endif
