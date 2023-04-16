#include <locale.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "../emojis.h"
#include "../users.h"
#include "test_utils.h"

user_t make_test_user(int pin) {
  user_t u;
  snprintf(u.user_name, 11, "%d", pin);
  u.pin = pin;
  u.icon = -1;
  u.token = 0;
  u.karma = 0;
  return u;
}

int test_new_user() {
  init_user_db();
  user_t u = make_test_user(1234);
  EXPECT_INT_GT(register_user(&u), 0);
  EXPECT_STR_EQ(u.user_name, "1234");
  EXPECT_UINT_EQ(1234, u.pin);
  EXPECT_UINT_NEQ(0, u.token);
  EXPECT_INT_NEQ(-1, u.icon);
  EXPECT_INT_EQ(0, u.karma);

  destroy_user_db();
  return 0;
}

int test_reset_user() {
  init_user_db();
  user_t u = make_test_user(1234);
  register_user(&u);
  user_t old = u;
  EXPECT_INT_GT(register_user(&u), 0);
  EXPECT_STR_EQ(u.user_name, old.user_name);
  EXPECT_UINT_EQ(old.pin, u.pin);
  EXPECT_UINT_NEQ(old.token, u.token);
  EXPECT_INT_NEQ(old.icon, u.icon);
  EXPECT_INT_EQ(u.karma, old.karma);

  destroy_user_db();
  return 0;
}

int test_reset_user_invalid_pin() {
  init_user_db();
  user_t u = make_test_user(1234);
  register_user(&u);
  u.pin = 6789;
  EXPECT_INT_LTE(register_user(&u), 0);
  destroy_user_db();
  return 0;
}

int test_add_users() {
  init_user_db();
  user_t u = make_test_user(1234);
  register_user(&u);
  user_t v = make_test_user(2345);
  register_user(&v);

  EXPECT_UINT_NEQ(0, u.token);
  EXPECT_UINT_NEQ(0, v.token);
  EXPECT_UINT_NEQ(u.token, v.token);
  EXPECT_UINT_EQ(1234, u.pin);
  EXPECT_UINT_EQ(2345, v.pin);

  destroy_user_db();
  return 0;
}

int test_add_update_users() {
  init_user_db();
  user_t u = make_test_user(1234);
  register_user(&u);
  user_t v = make_test_user(2345);
  register_user(&v);

  user_t uu;
  strcpy(uu.user_name, u.user_name);
  uu.pin = u.pin;
  user_t vv;
  strcpy(vv.user_name, v.user_name);
  vv.pin = v.pin;

  register_user(&uu);
  register_user(&vv);

  EXPECT_UINT_NEQ(0, uu.token);
  EXPECT_UINT_NEQ(0, vv.token);
  EXPECT_UINT_NEQ(uu.token, vv.token);
  EXPECT_UINT_NEQ(u.token, uu.token);
  EXPECT_UINT_NEQ(v.token, vv.token);
  EXPECT_UINT_EQ(1234, uu.pin);
  EXPECT_UINT_EQ(2345, vv.pin);

  destroy_user_db();
  return 0;
}

int test_karma() {
  init_user_db();
  user_t u = make_test_user(1234);
  register_user(&u);
  unsigned int token = u.token;

  // +2 karma
  u.karma = 2;
  EXPECT_TRUE(update_user_karma(&u));
  // +1 karma
  u.karma = 1;
  EXPECT_TRUE(update_user_karma(&u));

  u = make_test_user(1234);
  u.token = token;
  get_user(&u);
  EXPECT_INT_EQ(3, u.karma);

  // -6 karma
  u.karma = -8;
  EXPECT_TRUE(update_user_karma(&u));

  u = make_test_user(1234);
  u.token = token;
  get_user(&u);
  EXPECT_INT_EQ(-5, u.karma);

  destroy_user_db();
  return 0;
}

int test_foo() {
  init_user_db();
  destroy_user_db();
  return 0;
}

int main() {
  setlocale(LC_ALL, "");
  time_t t = time(NULL);
  // time_t t = 1678516687;
  srand(t);
  printf("seed %ld\n", t);

  ADD_TEST(test_new_user);
  ADD_TEST(test_reset_user);
  ADD_TEST(test_reset_user_invalid_pin);
  ADD_TEST(test_add_users);
  ADD_TEST(test_add_update_users);
  ADD_TEST(test_karma);

  run_tests(/*fail_fast=*/1, /*clean_after=*/1);
  return 0;
}
