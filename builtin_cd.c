#include <stdlib.h>
#include <sys/wait.h>
#include <stdio.h>
#include <string.h>
#include <signal.h>
#include "main.h"

/**
 * _getpwd - get the PWD environment variable
 * @void: no arg
 * Return: char **, the pwd
 */
char *_getpwd(void)
{
	char *pwd = NULL;
	char **env = environ;
	int i;

	for (i = 0; env[i] != NULL; i++)
	{
		if (_strncmp(env[i], "PWD=", 4) == 0)
		{
			pwd = _strdup(env[i] + 4);
			break;
		}
	}

	if (pwd == NULL)
		return (NULL);

	return (pwd);
}

/**
 * my_cd - change the directories to the new one
 * @argv: the line from the stdin
 * Return: void
 */
int my_cd(char **argv)
{
	char *the_pwd = NULL;

	the_pwd = _getpwd();
	if (the_pwd == NULL)
		return (1);

	printf("%s", the_pwd);

	free(argv);
	return (0);
}
