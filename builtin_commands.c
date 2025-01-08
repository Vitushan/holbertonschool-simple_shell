#include <stdlib.h>
#include <sys/wait.h>
#include <stdio.h>
#include <string.h>
#include "main.h"


/**
 * my_cd - change the directories to the new one
 * @argv: the line from the stdin
 * Return: 0 on success, -1 on failure
 */
int my_cd(char **argv)
{
	char *curr_pwd = NULL, *new_pwd = NULL;

	curr_pwd = _getpwd();
	new_pwd = curr_pwd;
	if (argv[1] != NULL)
	{
		if (strcmp(argv[1], "..") == 0)
			new_pwd = get_the_previous_dir(curr_pwd);
		else if (strcmp(argv[1], "-") == 0)
			new_pwd = get_the_previous_pwd();
		else if (strcmp(argv[1], "~") == 0)
			new_pwd = _gethome();
		else
			new_pwd = argv[1];
	}
	else
		new_pwd = _gethome();
	chdir(new_pwd);
	handle_pwd_env(curr_pwd, new_pwd);
	free(curr_pwd);
	if (new_pwd != curr_pwd)
		free(new_pwd);
	free(argv);
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
	int j = 0;
	char *previous_dir = NULL;
	int nb_slash = 0;

	while (curr_pwd[i] != '\0')
	{
		if (curr_pwd[i] == '/')
			nb_slash++;
		i++;
	}

	previous_dir = malloc(sizeof(char) * (strlen(curr_pwd) + 1));
	if (previous_dir == NULL)
		return (NULL);

	i = 0;

	while (nb_slash >= 1 && curr_pwd[i] != '\0')
	{
		if (curr_pwd[i] == '/')
			nb_slash--;
		previous_dir[j++] = curr_pwd[i++];
	}
	previous_dir[j] = '\0';

	return (previous_dir);
}

/**
 * get_the_previous_pwd - get the previous working directory
 * Return: char *
 */
char *get_the_previous_pwd(void)
{
	char **env = environ;
	int i = 0;

	while (env[i] != NULL)
	{
		if (strncmp(env[i], "OLDPWD=", 7) == 0)
			return (strdup(env[i] + 7));
		i++;
	}

	return (NULL);
}

/**
 * handle_pwd_env - change env variable OLDPWD and PWD
 * @old_pwd: the old pwd
 * @new_pwd: the new pwd
 * Return: 0 on success, -1 on failure
 */
int handle_pwd_env(char *old_pwd, char *new_pwd)
{
	char **env = environ;
	int i = 0, index_pwd, index_old_pwd, old_pwd_exist = 0;
	char *new_old_pwd_var = NULL;
	char *new_pwd_var = NULL;

	while (env[i] != NULL)
	{
		if (strncmp(env[i], "PWD=", 4) == 0)
			index_pwd = i;
		if (strncmp(env[i], "OLDPWD=", 7) == 0)
		{
			index_old_pwd = i;
			old_pwd_exist = 1;
		}
		i++;
	}

	if (old_pwd_exist == 1)
	{
		new_old_pwd_var = malloc(strlen(old_pwd) + 8);
		sprintf(new_old_pwd_var, "OLDPWD=%s", old_pwd);
		env[index_old_pwd] = new_old_pwd_var;
	}
	else
	{

	}

	new_pwd_var = malloc(strlen(new_pwd) + 5);
	sprintf(new_pwd_var, "PWD=%s", new_pwd);
	env[index_pwd] = new_pwd_var;

	return (0);
}
