#ifndef MAIN_H
#define MAIN_H

char **_get_line(char **line);
int _wait_status(int status);
int get_command(char **argv);
size_t _strlen(char *s);
char *_strcat(char *dest, char *src);
char *_strcpy(char *dest, char *src);
int _strcmp(char *s1, char *s2);
#endif
