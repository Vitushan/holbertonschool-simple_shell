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
    char *home = NULL;
    int result = 0;

    the_pwd = _getpwd();
    if (the_pwd == NULL)
        return (-1);
    home = _gethome();
    if (home == NULL)
    {
        free(the_pwd);
        return (-1);
    }

    if (argv[1] != NULL)
    {
        if (strcmp(argv[1], "~") == 0)
        {
            if (chdir(home) == -1)
            {
                result = -1;
            }
            else
            {
                _setenv("OLDPWD", the_pwd);
                _setenv("PWD", home);
            }
        }
    }

    free(the_pwd);
    free(home);
	free(argv);
    return (result);
}

/**
 * _setenv - change env variable OLDPWD and PWD
 * @old_pwd: the old pwd
 * @new_pwd: the new pwd
 * Return: 0 on succes, 1 on failure
 */
int _setenv(const char *name, const char *value)
{
    int i;
    size_t len;
    char *new_var;
	char **new_environ = NULL;

    for (i = 0; environ[i] != NULL; i++)
    {
        if (strncmp(environ[i], name, strlen(name)) == 0 && environ[i][strlen(name)] == '=')
        {
            len = strlen(name) + strlen(value) + 2;
            new_var = malloc(len);
            if (new_var == NULL)
                return (-1);
            snprintf(new_var, len, "%s=%s", name, value);
            free(environ[i]);
            environ[i] = new_var;
            return (0);
        }
    }

    len = strlen(name) + strlen(value) + 2;
    new_var = malloc(len);
    if (new_var == NULL)
        return (-1);
    snprintf(new_var, len, "%s=%s", name, value);
    
    new_environ = realloc(environ, (i + 2) * sizeof(char *));
    if (new_environ == NULL)
    {
        free(new_var);
        return (-1);
    }
    environ = new_environ;
    environ[i] = new_var;
    environ[i + 1] = NULL;

    return (0);
}
