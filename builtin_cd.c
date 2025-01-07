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
	int succes = 0, nb_slash = 0;

	the_pwd = _getpwd();
	if (the_pwd == NULL)
		return (1);

	if (argv[1] != NULL)
	{
		if (_strcmp(argv[1], "..") == 0)
		{
			int i = 0;
			new_pwd = malloc(_strlen(the_pwd) + 1);
			if (new_pwd == NULL)
				return (1);

			while (the_pwd[i] != '\0')
			{
				if (the_pwd[i] == '/')
					nb_slash++;
				i++;
			}
			i = 0;
			while ((nb_slash) != 0)
			{
				if (the_pwd[i] == '/')
					nb_slash--;
				new_pwd[i] = the_pwd[i];
				i++;
			}
			if (chdir(new_pwd) == 0)
			{
				printf("Répertoire changé avec succès");
				free(argv);
				return (0);
			}
		}
		else if (_strcmp(argv[1], "-") == 0)
		{
		}
		else if (_strcmp(argv[1], "~") == 0)
		{
			home = _gethome();
			if (home == NULL)
				return (1);
		}
		else if (argv[1] == NULL)
		{
		}
	}

	if (succes == 1)
		_setenv(OLD_PWD, the_pwd, new_pwd);

	free(argv);
	return (0);
}

int _setenv(char *name, char *value, char *new_value)
{
	int i;
	char **env = environ;
	int oldpwd_exist = 0;
	char *oldpwd = NULL;

	for (i = 0; env[i] != NULL; i++)
	{
		if (_strncmp(env[i], name, 7) == 0)
		{
			oldpwd_exist = 1;
			free(env[i]);
			env[i] = malloc(_strlen(value + 1) + 7);
			if (env[i] == NULL)
				return (-1);
			sprintf(env[i], "OLDPWD=%s", value);
			break;
		}
	}

	if (oldpwd_exist == 0)
	{
		oldpwd = malloc((_strlen(name)) + _strlen(value) + 3);
		if (oldpwd == NULL)
			return (1);

		sprintf(oldpwd, "%s%s", name, new_value);

		env[i + 1] = oldpwd;
		env[i + 2] = NULL;
	}

	return (0);
}
