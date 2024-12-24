#ifndef MAIN_H
#define MAIN_H
#include <unistd.h>

extern char **environ;
char **_getenv(void);
char *get_the_right_path(char **argv, char **full_path);
char **tokenize(ssize_t bytes_read, char *line);
void free_full_path(char **full_path);
#endif
