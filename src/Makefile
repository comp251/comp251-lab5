# make DEFINE=-DDEBUG <target>
DEFINE=
DEBUGGER=-g
CFLAGS=$(DEBUGGER) $(DEFINE) -Wall -Werror -I/usr/include/ncursesw
CC=gcc
OUTPUT=

# make SAN=asan
SAN=
ifeq ($(SAN),asan)
	CFLAGS+=-fsanitize=address
endif

TESTS=
TESTS+=tests/users_test
TESTS+=tests/posts_test
TESTS+=tests/rr_core_test

APPS=
APPS+=rr_server
APPS+=rr_console_client
APPS+=rr_curses_client
APPS+=scratch/emoji_menu

all: $(TESTS) $(APPS)

test: $(TESTS)
	$(foreach TEST,$(TESTS), ./$(TEST);)

test-leaks: $(TESTS)
	$(foreach TEST,$(TESTS), valgrind --leak-check=full ./$(TEST);)

tests/users_test: tests/users_test.o tests/test_utils.o lib/map.o users.o emojis.o util.o
	$(CC) $(CFLAGS) -o $@ $^

tests/posts_test: tests/posts_test.o tests/test_utils.o lib/map.o posts.o util.o
	$(CC) $(CFLAGS) -o $@ $^

tests/rr_core_test: tests/rr_core_test.o rr_core.o tests/test_utils.o lib/map.o posts.o util.o users.o  emojis.o
	$(CC) $(CFLAGS) -o $@ $^

rr_server: rr_server.o rr_service.o rr_core.o posts.o users.o lib/map.o emojis.o util.o uio.o conn.o
	$(CC) $(DEBUGGER) -o $@ $^ -lpthread

rr_console_client: rr_console_client.o uio.o conn.o util.o lib/map.o rr_client_lib.o
	$(CC) $(DEBUGGER) -o $@ $^

rr_curses_client: rr_curses_client.o uio.o conn.o util.o lib/map.o rr_client_lib.o
	$(CC) $(DEBUGGER) -o $@ $^ -lncursesw -lmenuw -lpanelw -lformw 

scratch/emoji_menu: scratch/emoji_menu.o emojis.o
	$(CC) $(DEBUGGER) -o $@ $^ -lncursesw -lmenuw

clean:
	rm -f *.o tests/*.o scratch/*.o $(TESTS) $(APPS)
