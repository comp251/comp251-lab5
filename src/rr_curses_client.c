#include <assert.h>
#include <ctype.h>
#include <errno.h>
#include <locale.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <ncursesw/form.h>
#include <ncursesw/menu.h>
#include <ncursesw/ncurses.h>
#include <ncursesw/panel.h>

#include "conn.h"
#include "rr_client_lib.h"
#include "uio.h"
#include "util.h"

// Rhodes Ramble curses client.
// This code is an absolute mess.

#define MAX_FILE_NAME 512
#define WIN_WIDTH 80
#define WIN_HEIGHT 25

// container for window/panel pairs.
struct screen {
  PANEL *panel;
  WINDOW *window;
};

// collection of screens for app.
struct windows {
  struct screen menu;
  struct screen post;
  struct screen posts;
  struct screen login;
  struct screen comments;
  struct screen user;
};

// globals used here; anonymous struct for namespace.
struct {
  int conn_fd;
  unsigned int token;
  unsigned int screen_width;
  unsigned int screen_height;
  int argc;
  char **argv;
  char token_cache_fn[MAX_FILE_NAME];
  // panels for tui
  struct windows windows;
} g;

// Menu item type
typedef struct menuitem_t {
  char *name;
  char *desc;
  int (*process)(); // function to be invoked
} menuitem_t;

// Form exit options
enum FORM_OPTS {
  FORM_OPT_UNKNOWN = 0,
  FORM_OPT_ESC = 1,
  FORM_OPT_DONE = 2,
};

// Forward declarations of basic functions.
//
// prints program usage.
void usage(char *name);
// parses a token from the token cache file.
unsigned int parse_token();
// writes a new token to the token cache file.
void write_token(unsigned int token);

// Forward declaration of tui functions.
//
// main application menu/app entry point.
void main_menu();
// initializes screens used by the app.
void init_tui_resources();
// cleans up screens on termination.
void destroy_tui_resources();
// hides all panels
void hide_all_panels();
// Executes the post/comment form; stores post text in buffer.
enum FORM_OPTS exec_post_form(char **buffer);
// View comments on the given post id.
int view_comments(struct rr_client_post_t *parent);
// Post a comment on the given post id.
void post_comment(unsigned int post_id);
// Execute login menu.
int login_menu_fn();
// Execute new post menu.
int post_menu_fn();
// Execute view posts menu.
int view_menu_fn();
// Execute view user info menu.
int info_menu_fn();
// Execute app exit.
int exit_fn();
// display a list of posts. cbuff is a pointer to an array of char*. if cbuff is
// NULL, the array will be allocated. if elements of cbuff are NULL, space will
// be allocated for post text. caller responsible for freeing these buffers.
// buffers can be reused on subsequent calls. parent should be NULL when
// displaying posts and non-NULL when displaying comments.
int display_posts(WINDOW *window, struct rr_client_post_t **posts,
                  int posts_len, char ***cbuff, int *updown, char *last_opt,
                  int init_selected, struct rr_client_post_t *parent);

// Forward declaration of basic utils.
//
// create a curses window
WINDOW *create_window(int width, int height, int startx, int starty);

// All menu items for main menu and associated handler functions.
menuitem_t g_main_menu_choices[] = {
    {"Login", "login or update icon", login_menu_fn},
    {"View", "view rambles", view_menu_fn},
    {"Post", "post a new ramble", post_menu_fn},
    {"Info", "get your user profile", info_menu_fn},
    {"Exit", "quit", exit_fn},
};

int main(int argc, char **argv) {
  g.argc = argc;
  g.argv = argv;

  if (argc < 3) {
    usage(argv[0]);
  }

  // Connect to server.
  g.conn_fd = conn_connect(argv[1], argv[2]);
  if (g.conn_fd < 0) {
    fprintf(stderr, "error connecting to %s:%s!\n", argv[1], argv[2]);
    usage(argv[0]);
    return 1;
  }

  cat_home_dir(g.token_cache_fn, MAX_FILE_NAME, RR_TOKEN_CACHE_FN);

  setlocale(LC_ALL, "");

  // Attempt to read cached token.
  g.token = parse_token();

  // Connected; start curses mode.
  initscr();
  cbreak();
  noecho();
  keypad(stdscr, TRUE);

  // get and keep screen height/width
  getyx(stdscr, g.screen_height, g.screen_width);

  // Initialize windows + panels
  init_tui_resources();

  // Enter main menu.
  main_menu();

  // Clean up
  destroy_tui_resources();

  // Close curses.
  endwin();

  return 0;
}

WINDOW *create_window(int width, int height, int startx, int starty) {
  WINDOW *win = newwin(height, width, starty, startx);
  wrefresh(win);
  return win;
}

void hide_all_panels() {
  hide_panel(g.windows.menu.panel);
  hide_panel(g.windows.login.panel);
  hide_panel(g.windows.user.panel);
  hide_panel(g.windows.posts.panel);
  hide_panel(g.windows.post.panel);
  hide_panel(g.windows.comments.panel);
}

void init_tui_resources() {
  g.windows.menu.window = create_window(WIN_WIDTH, WIN_HEIGHT, 0, 0);
  g.windows.menu.panel = new_panel(g.windows.menu.window);
  g.windows.login.window = create_window(WIN_WIDTH, WIN_HEIGHT, 0, 0);
  g.windows.login.panel = new_panel(g.windows.login.window);
  g.windows.user.window = create_window(WIN_WIDTH, WIN_HEIGHT, 0, 0);
  g.windows.user.panel = new_panel(g.windows.user.window);
  g.windows.posts.window = create_window(WIN_WIDTH, WIN_HEIGHT, 0, 0);
  g.windows.posts.panel = new_panel(g.windows.posts.window);
  g.windows.post.window = create_window(WIN_WIDTH, WIN_HEIGHT, 0, 0);
  g.windows.post.panel = new_panel(g.windows.post.window);
  g.windows.comments.window = create_window(WIN_WIDTH, WIN_HEIGHT, 0, 0);
  g.windows.comments.panel = new_panel(g.windows.comments.window);

  hide_all_panels();
}

void destroy_tui_resources() {
  delwin(g.windows.menu.window);
  del_panel(g.windows.menu.panel);
  delwin(g.windows.login.window);
  del_panel(g.windows.login.panel);
  delwin(g.windows.user.window);
  del_panel(g.windows.user.panel);
  delwin(g.windows.posts.window);
  del_panel(g.windows.posts.panel);
  delwin(g.windows.post.window);
  del_panel(g.windows.post.panel);
  delwin(g.windows.comments.window);
  del_panel(g.windows.comments.panel);
}

int exit_fn() {
  mvprintw(0, 0, "exiting...");
  return 1;
}

enum FORM_OPTS exec_post_form(char **buffer) {
  hide_all_panels();

  FIELD *field[2];
  field[1] = NULL;
  field[0] = new_field(10, 50, 1, 10, 0, 0);
  set_field_back(field[0], A_UNDERLINE);
  set_field_back(field[0], O_AUTOSKIP);
  // TODO: better form validation

  FORM *form = new_form(field);
  set_form_win(form, g.windows.post.window);
  show_panel(g.windows.post.panel);
  update_panels();

  form_driver(form, REQ_OVL_MODE);
  post_form(form);
  keypad(g.windows.post.window, 1);

  enum FORM_OPTS result = FORM_OPT_UNKNOWN;

  pos_form_cursor(form);
  curs_set(1);

  refresh();
  wrefresh(g.windows.post.window);

  int c;
  while (result == FORM_OPT_UNKNOWN) {
    mvwprintw(g.windows.post.window, 0, 0, "enter accept/esc to quit");
    mvwprintw(g.windows.post.window, 1, 1, "text: ");
    wrefresh(g.windows.post.window);
    c = getch();
    switch (c) {
    case '\t':
    case KEY_DOWN:
      form_driver(form, REQ_NEXT_LINE);
      break;
    case KEY_BTAB:
    case KEY_UP:
      form_driver(form, REQ_PREV_LINE);
      break;
    case KEY_BACKSPACE:
    case 127:
      form_driver(form, REQ_DEL_PREV);
      break;
    case KEY_DC:
      form_driver(form, REQ_DEL_CHAR);
      break;
    case '\n':
      result = FORM_OPT_DONE;
      break;
    case 27: // esc
      result = FORM_OPT_ESC;
      break;
    case KEY_LEFT:
      form_driver(form, REQ_LEFT_CHAR);
      break;
    case KEY_RIGHT:
      form_driver(form, REQ_RIGHT_CHAR);
      break;
    default:
      form_driver(form, c);
      break;
    }
  }
  form_driver(form, REQ_VALIDATION);

  if (result == FORM_OPT_DONE) {
    // post request
    char *t = strip(field_buffer(field[0], 0));
    // strip runs of spaces
    char *c = t;
    char *p = c;
    while (*c) {
      *c = *(p++);
      while (*p && isspace(*p) && *c == *p) {
        p++;
      }
      c++;
    }
    *buffer = malloc(strlen(t) + 1);
    strcpy(*buffer, t);
  }

  unpost_form(form);
  free_form(form);
  free_field(field[0]);
  hide_panel(g.windows.post.panel);
  update_panels();
  refresh();
  return result;
}

int post_menu_fn() {
  char *buffer = NULL;
  enum FORM_OPTS result = exec_post_form(&buffer);
  if (result == FORM_OPT_DONE) {
    // post request
    int ok = do_post(g.conn_fd, g.token, buffer);
    if (ok < 0) {
      mvwprintw(g.windows.post.window, 10, 0, "Error posting with token %u\n",
                g.token);
      getch();
    }
  }
  return 0;
}

void post_comment(unsigned int post_id) {
  char *buffer = NULL;
  enum FORM_OPTS result = exec_post_form(&buffer);
  if (result == FORM_OPT_DONE) {
    // post request
    int ok = do_comment(g.conn_fd, g.token, post_id, buffer);
    if (ok < 0) {
      mvwprintw(g.windows.post.window, 10, 0, "Error posting with token %u\n",
                g.token);
      getch();
    }
  }
}

#define SELECTED_NONE (-2)
#define SELECTED_ESC (-1)

int display_posts(WINDOW *window, struct rr_client_post_t **posts,
                  int posts_len, char ***cbuff, int *updown, char *last_opt,
                  int init_selected, struct rr_client_post_t *parent) {
  if (!*cbuff) {
    // if there's no buffer of post text, make one.
    *cbuff = calloc(posts_len, sizeof(char *));
  }
  char **strs = *cbuff;
  wchar_t ws[2];
  ws[1] = L'\0';

  int n = posts_len + (last_opt ? 1 : 0);

  ITEM **items = calloc(n + 1, sizeof(ITEM *));
  items[n] = NULL;
  for (int i = 0; i < posts_len; i++) {
    int len = strlen(posts[i]->text) + sizeof(wchar_t) + 30;
    if (!strs[i]) {
      // alloc enough for the text, plus about 30 extra bytes.
      strs[i] = malloc(len);
    }
    ws[0] = posts[i]->icon;
    // create the post text
    snprintf(strs[i], len, "(%d) %ls %s", posts[i]->karma, ws, posts[i]->text);
    strip(strs[i]);
    // This is a disgusting hack and I apologize for it.
    items[i] = new_item(strs[i], "");
    if (!items[i]) {
      mvwprintw(window, 0, 0, "ERROR %s",
                errno == E_BAD_ARGUMENT ? "bad argument" : "system error");
      wrefresh(window);
      getch();
    }
  }
  if (last_opt) {
    // add last option!
    items[n - 1] = new_item(last_opt, "");
  }
  keypad(window, 1);

  mvwprintw(window, 0, 0, "u/d to upvote/downvote");
  int menu_offset = 1;
  if (!last_opt) {
    mvwprintw(window, menu_offset++, 0, "enter to select/esc for back");
  } else {
    mvwprintw(window, menu_offset++, 0, "esc for back");
  }
  if (parent) {
    mvwprintw(window, menu_offset++, 0, "%s", parent->text);
    menu_offset += strlen(parent->text) / WIN_WIDTH;
  }
  MENU *menu = new_menu(items);
  set_menu_win(menu, window);
  WINDOW *win = derwin(window, 0, 0, ++menu_offset, 0);
  set_menu_sub(menu, win);
  // set_menu_format(menu, 25, 80);
  set_menu_mark(menu, " > ");
  post_menu(menu);
  refresh();

  set_current_item(menu, items[init_selected]);
  int c;
  int selected = SELECTED_NONE;
  while (selected == SELECTED_NONE) {
    curs_set(0);
    c = wgetch(window);
    switch (c) {
    case 'j':
    case KEY_DOWN:
      menu_driver(menu, REQ_DOWN_ITEM);
      break;
    case 'k':
    case KEY_UP:
      menu_driver(menu, REQ_UP_ITEM);
      break;
    case KEY_NPAGE:
      menu_driver(menu, REQ_SCR_DPAGE);
      break;
    case KEY_PPAGE:
      menu_driver(menu, REQ_SCR_UPAGE);
      break;
    case 'u':
      *updown = RR_UPVOTE;
      selected = item_index(current_item(menu));
      break;
    case 'd':
      *updown = RR_DOWNVOTE;
      selected = item_index(current_item(menu));
      break;
    case 10:
    case ' ':
    case KEY_ENTER:
      *updown = 0;
      selected = item_index(current_item(menu));
      break;
    case 'q':
    case 27: // esc
      *updown = 0;
      selected = SELECTED_ESC;
      break;
    default:
      break;
    }
    if (selected == n - 1 && last_opt && *updown != 0) {
      // last option was selected with u/d
      selected = SELECTED_NONE;
      *updown = 0;
    }
    refresh();
  }

  unpost_menu(menu);
  for (int i = 0; i < posts_len; i++) {
    free_item(items[i]);
  }
  free_menu(menu);

  delwin(win);
  return selected;
}

int view_comments(struct rr_client_post_t *parent) {
  unsigned int post_id = parent->id;
  hide_all_panels();
  wclear(g.windows.comments.window);
  top_panel(g.windows.comments.panel);
  show_panel(g.windows.comments.panel);
  update_panels();
  refresh();
  // get posts, display
  struct rr_client_post_t **posts =
      calloc(RR_MAX_POSTS, sizeof(struct rr_client_post_t *));
  int n_posts = get_comments(g.conn_fd, g.token, post_id, posts, RR_MAX_POSTS);
  if (n_posts < 0) {
    mvwprintw(g.windows.comments.window, 0, 0, "error retrieving posts...");
    refresh();
    getch();
    free(posts);
    return 0;
  }

  char **cbuff = NULL;
  int updown = 0;
  int refresh = 0;

  int selected = 0;
  while (1) {
    selected = display_posts(g.windows.comments.window, posts, n_posts, &cbuff,
                             &updown, "new comment", selected, parent);
    assert(selected != SELECTED_NONE);
    if (selected == SELECTED_ESC) {
      // esc
      break;
    }
    if (updown) {
      // post up/down vote
      if (do_vote(g.conn_fd, g.token, posts[selected]->id, updown) < 0) {
        mvwprintw(g.windows.comments.window, 0, 0, "error voting!");
        getch();
        break;
      }
      // use cached karma
      posts[selected]->karma += updown;
    } else if (selected == n_posts) {
      // post a comment
      post_comment(post_id);
      refresh = 1;
      break;
    }
  }

  free_posts(posts, RR_MAX_POSTS);
  if (cbuff) {
    for (int i = 0; i < n_posts; i++) {
      if (cbuff[i]) {
        free(cbuff[i]);
      }
    }
    free(cbuff);
  }
  hide_panel(g.windows.comments.panel);
  update_panels();

  return refresh;
}

int view_menu_fn() {
  // get posts, display
  wclear(g.windows.posts.window);
  hide_all_panels();
  struct rr_client_post_t **posts =
      calloc(RR_MAX_POSTS, sizeof(struct rr_client_post_t *));
  int n_posts = get_posts(g.conn_fd, g.token, posts, RR_MAX_POSTS);
  if (n_posts <= 0) {
    if (n_posts < 0) {
      mvwprintw(g.windows.posts.window, 0, 0, "error retrieving posts...");
    } else {
      mvwprintw(g.windows.posts.window, 0, 0, "no posts...");
    }
    show_panel(g.windows.posts.panel);
    update_panels();
    refresh();
    getch();
    free(posts);
    return 0;
  }

  char **cbuff = NULL;
  int updown = 0;

  // We want posts to appear in LIFO order, but they are retrieved in FIFO
  // order. Reverse our post list.
  for (int i = 0; i < n_posts / 2; i++) {
    struct rr_client_post_t *tmp = posts[i];
    posts[i] = posts[n_posts - i - 1];
    posts[n_posts - i - 1] = tmp;
  }

  show_panel(g.windows.posts.panel);
  update_panels();
  refresh();

  int selected = 0;
  while (1) {
    selected = display_posts(g.windows.posts.window, posts, n_posts, &cbuff,
                             &updown, NULL, selected, NULL);
    assert(selected != SELECTED_NONE);
    if (selected == SELECTED_ESC) {
      // esc
      break;
    }
    if (updown) {
      // post up/down vote
      if (do_vote(g.conn_fd, g.token, posts[selected]->id, updown) < 0) {
        mvwprintw(g.windows.posts.window, 0, 0, "error voting!");
        getch();
        break;
      }
      // use cached karma
      posts[selected]->karma += updown;
    } else {
      // get comments
      hide_panel(g.windows.posts.panel);
      while (view_comments(posts[selected])) {
        // refresh as long as a new comment is posted.
      }
      show_panel(g.windows.posts.panel);
    }
  }

  free_posts(posts, RR_MAX_POSTS);
  if (cbuff) {
    for (int i = 0; i < n_posts; i++) {
      if (cbuff[i]) {
        free(cbuff[i]);
      }
    }
    free(cbuff);
  }

  hide_panel(g.windows.posts.panel);
  update_panels();

  return 0;
}

int info_menu_fn() {
  // get user info and display it.
  struct rr_client_user_info_t user;
  int ok = get_user_info(g.conn_fd, g.token, &user);
  mvwprintw(g.windows.user.window, 0, 0, "user info");
  if (ok < 0) {
    mvwprintw(g.windows.user.window, 1, 0, "error retrieving user info...");
  } else {
    int line = 1;
    wchar_t wstr[2];
    wstr[0] = user.icon;
    wstr[1] = L'\0';
    mvwprintw(g.windows.user.window, line++, 0, "icon: %ls", wstr);
    mvwprintw(g.windows.user.window, line++, 0, "karma: %d", user.karma);
  }
  top_panel(g.windows.user.panel);
  show_panel(g.windows.user.panel);
  update_panels();
  wrefresh(g.windows.user.window);
  refresh();
  getch();
  hide_panel(g.windows.user.panel);
  update_panels();
  return 0;
}

int login_menu_fn() {
  hide_all_panels();

  FIELD *field[3];
  field[2] = NULL;                         // null-terminate
  field[0] = new_field(1, 15, 0, 0, 0, 0); // username
  set_field_back(field[0], A_UNDERLINE);
  set_field_back(field[0], O_AUTOSKIP);
  field[1] = new_field(1, 15, 2, 0, 0, 0); // pin
  set_field_back(field[1], A_UNDERLINE);
  set_field_back(field[1], O_AUTOSKIP);

  // TODO: Better field validation
  // set_field_type(field[0], TYPE_ALNUM, 15);
  // set_field_type(field[1], TYPE_INTEGER, 10);

  wclear(g.windows.login.window);
  FORM *form = new_form(field);
  WINDOW *form_win = derwin(g.windows.login.window, 0, 0, 1, 12);
  set_form_win(form, g.windows.login.window);
  set_form_sub(form, form_win);

  form_driver(form, REQ_OVL_MODE);
  post_form(form);
  keypad(form_win, 1);

  enum FORM_OPTS result = FORM_OPT_UNKNOWN;

  pos_form_cursor(form);
  curs_set(1);
  mvwprintw(g.windows.login.window, 0, 0, "enter to accept/esc to quit");
  mvwprintw(g.windows.login.window, 1, 1, "Username: ");
  mvwprintw(g.windows.login.window, 3, 1, "Pin: ");
  show_panel(g.windows.login.panel);
  update_panels();
  refresh();
  wrefresh(g.windows.login.window);
  wrefresh(form_win);

  int c;
  while (result == FORM_OPT_UNKNOWN) {

    c = getch();
    switch (c) {
    case '\t':
    case KEY_DOWN:
      form_driver(form, REQ_NEXT_FIELD);
      form_driver(form, REQ_END_LINE);
      break;
    case KEY_BTAB:
    case KEY_UP:
      form_driver(form, REQ_PREV_FIELD);
      form_driver(form, REQ_END_LINE);
      break;
    case KEY_BACKSPACE:
    case 127:
      form_driver(form, REQ_DEL_PREV);
      break;
    case KEY_DC:
      form_driver(form, REQ_CLR_EOF);
      break;
    case '\n':
      result = FORM_OPT_DONE;
      break;
    case 27: // esc
      result = FORM_OPT_ESC;
      break;
    case KEY_LEFT:
      form_driver(form, REQ_LEFT_CHAR);
      break;
    case KEY_RIGHT:
      form_driver(form, REQ_RIGHT_CHAR);
      break;
    case ' ':
      // ignore spaces
      break;
    default:
      form_driver(form, c);
      break;
    }
    wrefresh(form_win);
  }
  form_driver(form, REQ_VALIDATION);

  if (result == FORM_OPT_DONE) {
    // post request
    unsigned int token = 0;
    char *name = strip(field_buffer(field[0], 0));
    char *pin = strip(field_buffer(field[1], 0));
    int ok = do_login(g.conn_fd, name, pin, &token);
    if (ok < 0) {
      g.token = 0;
      mvwprintw(g.windows.login.window, 5, 0,
                "Error authenticating %s with pin %s!", name, pin);
    } else {
      write_token(token);
      mvwprintw(g.windows.login.window, 5, 0, "Got token: %u", token);
      g.token = token;
    }
    mvwprintw(g.windows.login.window, 6, 0, "press any key");
    wrefresh(g.windows.login.window);
    refresh();
    getch();
  }

  unpost_form(form);
  free_form(form);
  free_field(field[0]);
  free_field(field[1]);
  delwin(form_win);

  hide_panel(g.windows.login.panel);
  update_panels();
  refresh();

  return 0;
}

void main_menu() {
  ITEM **items = NULL;
  MENU *menu = NULL;

  while (!g.token) {
    login_menu_fn();
  }

  int n_choices = sizeof(g_main_menu_choices) / sizeof(g_main_menu_choices[0]);
  items = calloc(n_choices + 1, sizeof(ITEM *));
  for (int i = 0; i < n_choices; i++) {
    items[i] =
        new_item(g_main_menu_choices[i].name, g_main_menu_choices[i].desc);
    set_item_userptr(items[i], g_main_menu_choices[i].process);
  }
  items[n_choices] = NULL;
  menu = new_menu(items);
  set_menu_win(menu, g.windows.menu.window);
  WINDOW *win = derwin(g.windows.menu.window, 0, 0, 2, 0);
  set_menu_sub(menu, win);
  set_menu_mark(menu, "> ");
  top_panel(g.windows.menu.panel);
  show_panel(g.windows.menu.panel);
  update_panels();
  mvwprintw(g.windows.menu.window, 0, 0,
            "Rhodes Ramble - Login to register/update icon");
  post_menu(menu);
  refresh();
  wrefresh(g.windows.menu.window);

  int c;
  ITEM *cur = NULL;
  int (*cur_fn)() = NULL;
  int done = 0;
  while (!done) {
    curs_set(0);
    c = getch();
    switch (c) {
    case 'j':
    case KEY_DOWN:
      menu_driver(menu, REQ_DOWN_ITEM);
      break;

    case 'k':
    case KEY_UP:
      menu_driver(menu, REQ_UP_ITEM);
      break;

    case 10:
    case ' ':
    case KEY_ENTER:
      cur = current_item(menu);
      cur_fn = item_userptr(cur);
      done = cur_fn();
      break;
    case 27: // esc
    case 'q':
      done = 1;
      break;
    default:
      break;
    }

    top_panel(g.windows.menu.panel);
    show_panel(g.windows.menu.panel);
    update_panels();
    refresh();
  }
  unpost_menu(menu);
  for (int i = 0; i < n_choices; i++) {
    free_item(items[i]);
  }
  free_menu(menu);
  delwin(win);
}

void usage(char *name) {
  printf("Usage: %s HOST PORT [TOKEN_FILENAME]\n", name);
  exit(1);
}

unsigned int parse_token() {
  unsigned int token = 0;
  FILE *f = fopen(g.token_cache_fn, "r");
  if (!f) {
    fprintf(stderr, "could not open token file %s; no token found\n",
            g.token_cache_fn);
    return 0;
  }
  char tok_buff[80];
  if (fgets(tok_buff, 80, f) != NULL) {
    errno = 0;
    token = strtoul(tok_buff, NULL, 10);
    if (errno) {
      return 0;
    }
    fprintf(stderr, "read token %u\n", token);
  } else {
    fprintf(stderr, "no token found.\n");
    return 0;
  }
  return token;
}

void write_token(unsigned int token) {
  FILE *f = fopen(g.token_cache_fn, "w");
  if (!f) {
    fprintf(stderr, "could not open token file %s; no token found\n",
            g.token_cache_fn);
    return;
  }
  fprintf(f, "%u\n", token);
  fclose(f);
}
