#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include "main.h"

/**
 * main - main function
 *
 * Return: Always 0.
 */
int main(void)
{
	char **full_path = NULL;
	char *right_path = NULL;
	char **argv = NULL;
	char *line = NULL;
	int len = 0;
	int i = 0;

	full_path = _getenv();

	argv = getline(&line, &len, stdin);

	right_path = get_the_right_path(full_path, argv);

	while (full_path[i] != NULL)
	{
		printf("%s\n", full_path[i]);
		i++;
	}

	return (0);
}

/**
 * _getenv - find the format of the command, then execve it
 * @void: no arg
 * Return: char **, the path
 */
char **_getenv(void)
{
	unsigned int i, k, j = 0, num_paths = 0;
	char **full_path = NULL;
	char *token = NULL;
	char **env = environ;

	for (i = 0; env[i] != NULL; i++)
	{
		if (strncmp(env[i], "PATH", strlen("PATH")) == 0)
		{
			token = strtok(env[i] + 5, ":");
			while (token != NULL)
			{
				num_paths++;
				token = strtok(NULL, ":");
			}

			full_path = malloc((num_paths + 1) * sizeof(char *));
			if (full_path == NULL)
				return (NULL);

			token = strtok(env[i] + 5, ":");
			while (token != NULL)
			{
				full_path[j] = strdup(token);
				token = strtok(NULL, ":");
				j++;
			}
			full_path[j] = NULL;
			break;
		}
	}

	return (full_path);
}

/**
 * get_the_right_path - find the right path to execute the shell command
 * @argv: the line from the stdin
 * @full_path: the env variable "PATH="
 * Return: char *, the right path, or NULL
 */
char *get_the_right_path(char **argv, char **full_path)
{
	char *path_finded = NULL;
	int i = 0;

	if (argv == NULL || full_path == NULL)
	{
		fprintf(stderr, "Invalid arguments\n");
		return (NULL);
	}

	if (argv[0] == NULL || argv[0][0] == '\0')
	{
		fprintf(stderr, "Command '%s' is invalid\n", argv[0]);
		return (NULL);
	}

	if (access(argv[0], X_OK) == 0)
		return (argv[0]);

	while (full_path[i] != NULL)
	{
		path_finded = malloc(strlen(full_path[i]) + strlen(argv[0]) + 2);
		if (path_finded == NULL)
			return (NULL);

		sprintf(path_finded, "%s/%s", full_path[i], argv[0]);

		if (access(path_finded, X_OK) == 0)
			return (path_finded);

		free(path_finded);
		i++;
	}

	fprintf(stderr, "./simple_shell: 1: %s: not found\n", argv[0]);
	return (NULL);
}
