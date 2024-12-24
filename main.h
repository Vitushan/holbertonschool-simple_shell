#ifndef MAIN_H
#define MAIN_H

extern char **environ;
char **_getenv(void);
char *get_the_right_path(char **argv, char **full_path);
#endif
