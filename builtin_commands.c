#include <stdlib.h>
#include <sys/wait.h>
#include <stdio.h>
#include <string.h>
#include "main.h"


/**
 * my_cd - change the directories to the new one
 * @argv: the line from the stdin
 * Return: void
 */
int my_cd(char **argv)
{
	char *curr_pwd = NULL, *new_pwd = NULL, *prev_dir = NULL, *prev_pwd = NULL;

	curr_pwd = _getpwd();
	if (curr_pwd == NULL)
		return (-1);

	if (argv[1] != NULL)
	{
		if (_strcmp(argv[1], "..") == 0)
		{
			prev_dir = get_the_previous_dir(curr_pwd);
			if (chdir(prev_dir) == -1)
				return (-1);
			new_pwd = prev_dir;
		}
		else if (_strcmp(argv[1], "-") == 0)
		{
			prev_pwd = get_the_prev_pwd();
			if (chdir(prev_pwd) == -1)
				return (-1);
			new_pwd = prev_pwd;
		}
		else if (_strcmp(argv[1], "~") == 0)
		{
			char *home_pwd = NULL;

			home_pwd = _gethome();
			if (home_pwd == NULL)
				return (-1);
			if (chdir(home_pwd) == -1)
				return (-1);
			new_pwd = home_pwd;
		}
		else if (_strncmp(argv[1], "/", 1) == 0)
		{
			if (chdir(argv[1]) == -1)
				return (-1);
			new_pwd = argv[1];
		}
	}

	handle_pwd_env(curr_pwd, new_pwd);

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

	previous_dir = malloc(sizeof(char) * _strlen(curr_pwd) + 1);
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
