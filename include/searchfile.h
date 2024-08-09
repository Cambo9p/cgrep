#ifndef SEARCH_H
#define SEARCH_H
#include "args.h"
#include "formatted_ans.h"

// searches for the pattern in file TODO add options passed into here
void cgrep_search_file(char *filename, char *pattern);
void cgrep_linear_search(grep_args_t *args);

#endif
