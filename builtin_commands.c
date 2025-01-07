#include <stdlib.h>
#include <sys/wait.h>
#include <stdio.h>
#include <string.h>
#include "main.h"

/**
 * _getpwd - get the PWD environment variable
 * @void: no arg
 * Return: char *, the pwd
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
 * _gethome - get the HOME environment variable
 * @void: no arg
 * Return: char *, the pwd
 */
char *_gethome(void)
{
	char *home = NULL;
	char **env = environ;
	int i;

	for (i = 0; env[i] != NULL; i++)
	{
		if (_strncmp(env[i], "HOME=", 5) == 0)
		{
			home = _strdup(env[i] + 5);
			break;
		}
	}

	if (home == NULL)
		return (NULL);

	return (home);
}

/**
 * my_cd - change the directories to the new one
 * @argv: the line from the stdin
 * Return: void
 */
int my_cd(char **argv)
{
	char *curr_pwd = NULL;
	char *new_pwd = NULL;
	char *prev_pwd = NULL;

	(void)new_pwd;
	(void)

	curr_pwd = _getpwd();
	if (curr_pwd == NULL)
		return (-1);

	if (argv[1] != NULL)
	{
		if (_strcmp(argv[1], "..") == 0)
		{
			prev_pwd = get_the_previous_dir(curr_pwd);
			if (chdir(prev_pwd) == -1)
				return (-1);
		}
		else if (_strcmp(argv[1], "-") == 0)
		{

		}
		else if (_strcmp(argv[1], "~") == 0)
		{

		}
		else if (_strncmp(argv[1], "/", 1) == 0)
		{
			
		}
	}

	return (0);
}

/**
 * handle_pwd_env - change env variable OLDPWD and PWD
 * @old_pwd: the old pwd
 * @new_pwd: the new pwd
 * Return: 0 on succes, 1 on failure
 */
int handle_pwd_env(char *old_pwd, char *new_pwd)
{

	return (0);
}

/**
 * get_the_previous_dir - get the previous directory
 * @curr_pwd: the current pwd
 * Return: the previous dir
 */
char *get_the_previous_dir(char *curr_pwd)
{
	int i = 0;
	char *previous_dir = NULL;
    int nb_slash = 0;

	while (curr_pwd[i] != '\0')
	{
		if (curr_pwd[i] == '/')
			nb_slash++;
		i++;
	}

	previous_dir = malloc(sizeof(char) * strlen(curr_pwd) + 1);
	if (previous_dir == NULL)
		return (-1);

    i = 0;

	while (nb_slash != 0)
	{
		if (curr_pwd[i] == '/')
			nb_slash--;
		previous_dir[i] = curr_pwd[i];
		i++;
	}

	return (previous_dir);
}
