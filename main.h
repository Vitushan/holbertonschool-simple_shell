#ifndef MAIN_H
#define MAIN_H
#include <unistd.h>

extern char **environ;
char **tokenize(ssize_t bytes_read, char *line);
char **_getenv(void);
char *get_the_right_path(char *argv, char **full_path);
void full_free(char **full_path, char **argv, char *line, char *right_path);
#endif
