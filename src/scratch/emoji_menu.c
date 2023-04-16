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

#include "../emojis.h"

int main(int argc, char **argv) {

  setlocale(LC_ALL, "");

  initscr();
  cbreak();
  noecho();
  keypad(stdscr, TRUE);

  MENU *menu;
  ITEM **items = NULL;

  int n = n_emoji();
  items = calloc(n + 1, sizeof(ITEM *));

  int idx = 0;
  for (int i = 0; i < n; i++) {
    char *mem = malloc(sizeof(wchar_t) + 1);
    sprintf(mem, "%lc", emoji(i));
    items[idx] = new_item(mem, "");
    if (!items[idx]) {
      fprintf(stderr, "error item %d\n", i);
    }
    idx++;
  }
  items[idx] = NULL;
  menu = new_menu(items);
  set_menu_mark(menu, "> ");
  post_menu(menu);
  refresh();

  int c;
  while (1) {
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

    default:
      break;
    }
    refresh();
  }
  for (int i = 0; i < n; i++) {
    if (items[i]) {
      free_item(items[i]);
    }
  }
  free_menu(menu);

  endwin();

  return 0;
}
