#include <stdlib.h>
#include <sys/wait.h>
#include <stdio.h>
#include <string.h>
#include <signal.h>
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
	char *the_pwd = NULL;
	char *new_pwd = NULL;
	char *home = NULL;
	char *OLD_PWD = "OLDPWD=";
	int succes = 0, nb_slash = 0, i = 0;

	the_pwd = _getpwd();
	if (the_pwd == NULL)
		return (1);

	if (argv[1] != NULL)
	{
		if (_strcmp(argv[1], "..") == 0)
		{
			new_pwd = malloc(_strlen(the_pwd) + 1);
			if (new_pwd == NULL)
				return (1);

			for (i = 0; the_pwd[i] != '\0'; i++)
			{
				if (the_pwd[i] == '/')
					nb_slash++;
			}

			i = 0;
			while ((nb_slash - 1) != 0)
			{
				if (the_pwd[i] == '/')
					nb_slash--;
				new_pwd[i] = the_pwd[i];
				i++;
			}
			new_pwd[i] = '\0';
			if (chdir(new_pwd) != 0)
			{
				perror("cd");
				free(new_pwd);
				return (1);
			}
			succes = 1;
			free(new_pwd);
		}
		else if (_strcmp(argv[1], "-") == 0)
		{
			char *oldpwd = NULL;

			oldpwd = getenv("OLDPWD");
			if (oldpwd == NULL)
			{
				fprintf(stderr, "cd: OLDPWD not set\n");
				return (1);
			}
			if (_getpwd() != NULL)
				_setenv("OLD_PWD", the_pwd);
				
			if (chdir(oldpwd) != 0)
			{
				perror("cd");
				return (1);
			}
				printf("%s\n", oldpwd);
				_setenv("PWD=", oldpwd);
				succes = 1;
		}
		else if (_strcmp(argv[1], "~") == 0)
		{
			home = _gethome();
			if (home == NULL)
				return (1);

				if (chdir(home) != 0)
				{
					perror("cd");
					free(home);
					return (1);
				}
				succes = 1;
				free(home);
		}
		else
		{
			if (chdir(argv[1]) != 0)
			{
				perror("cd");
				return (1);
			}
			succes = 1;
		}
	}
	else{
		home = _gethome();
		if (home == NULL)
			return (1);
		
		if (chdir(home) != 0)
		{
			perror("cd");
			free(home);
			return (1);
		}
		succes = 1;
		free(home);
	}
		if (succes == 1)
			_setenv(OLD_PWD, the_pwd);

		free(the_pwd);
		return (0);
}

int _setenv(char *name, char *value)
{
	int i, j = 0;
	char **env = environ;
	int oldpwd_exist = 0;
	char *oldpwd = NULL;

	for (i = 0; env[i] != NULL; i++)
	{
		if (_strncmp(env[i], name, 7) == 0)
		{
			oldpwd_exist = 1;
			break;
		}
	}

	if (oldpwd_exist == 0)
	{
		oldpwd = malloc((_strlen(name)) + _strlen(value) + 3);
		if (oldpwd == NULL)
			return (1);

		sprintf(oldpwd, "%s%s", name, value);

		while (oldpwd[j] != '\0')
			j++;

		oldpwd[j] = '\0';

		env[i + 1] = oldpwd;
	}

	return (0);
}
