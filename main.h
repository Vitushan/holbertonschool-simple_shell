#ifndef MAIN_H
#define MAIN_H
#include <unistd.h>

extern char **environ;
char **tokenize(ssize_t bytes_read, char *line);
char **_getenv(void);
char *get_the_right_path(char *argv, char **full_path, int i);
int forking(char *right_path, char **argv);
void free_line_fullpath(char **full_path, char *line);
void handle_signal(int sig);
char *_getpwd(void);
int my_cd(char **argv);
char *_strcpy(char *dest, char *src);
int _strlen(char *s);
int _strcmp(char *s1, char *s2);
int _strncmp(const char *str1, const char *str2, size_t n);
char *_strdup(char *s);
#endif
