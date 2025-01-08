#ifndef MAIN_H
#define MAIN_H
#include <unistd.h>

extern char **environ;
char **tokenize(ssize_t bytes_read, char *line);
char **_getenv(void);
char *get_the_right_path(char *argv, char **full_path, int i);
int forking(char *right_path, char **argv);
void free_line_fullpath(char **full_path, char *line);
char *_getpwd(void);
char *_gethome(void);
int my_cd(char **argv);
int handle_pwd_env(char *old_pwd, char *new_pwd);
char *get_the_previous_dir(char *curr_pwd);
char *get_the_previous_pwd(void);
#endif
