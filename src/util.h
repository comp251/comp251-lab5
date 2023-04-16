#ifndef __UTIL_H__
#define __UTIL_H__

#include "lib/map.h"

// Convert n to a string; hex representation.
void itoa(char *buff, int len, unsigned int n);

// Returns an int key that is not present in the map.
//
// Assumes that int keys are represented as hex strings.
unsigned int unique_int_key(map_t *map);

// Get path in home directory for user.
//
// buff will contain the home directory concatenated with the file name.
// e.g., if fname = "dir/file" then buff = "/home/user/dir/file"
void cat_home_dir(char *buff, int len, char *fname);

// strips whitespace from beginning/end of a string, returning its new start.
char *strip(char *str);

#endif
