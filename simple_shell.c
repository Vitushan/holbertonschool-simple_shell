#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
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
	while (1)
	{
		char **argv = NULL, **full_path = NULL;
		char *line = NULL, *right_path = NULL;
		size_t len = 0;
		ssize_t nread;
		pid_t pid;
		int status;

		printf("#simple_shell$ ");
		nread = getline(&line, &len, stdin);
		if (nread == -1)
			free(line), perror("Error reading input"), exit(EXIT_FAILURE);

		argv = tokenize(nread, line);
		full_path = _getenv();
		right_path = get_the_right_path(argv, full_path);
		if (right_path != NULL)
		{
			pid = fork();
			if (pid == -1)
			{
				full_free(full_path, argv, line, right_path);
				perror("Fork failed"), exit(EXIT_FAILURE);
			}
			if (pid == 0)
			{
				if (execve(right_path, argv, NULL) == -1)
				{
					full_free(full_path, argv, line, right_path);
					perror("Erreur lors de l'exécution"), exit(EXIT_FAILURE);
				}
			}
			wait(&status);
		}
		full_free(full_path, argv, line, right_path);
	}

	return (0);
}

/**
 * full_free - free every pointer that is not NULL
 * @full_path: the array of the var PATH
 * @line: the stdin hit by the user
 * @argv: the tokenized var line
 * @right_path: the founded path for the current command
 * Return: void
 */
void full_free(char **full_path, char **argv, char *line, char *right_path)
{
	int i, j;

	if (full_path != NULL)
	{
		for (i = 0; full_path[i] != NULL; i++)
		{
			free(full_path[i]);
		}
			free(full_path);
	}

	if (argv != NULL)
	{
		for (j = 0; argv[j] != NULL; j++)
			free(argv[j]);
		free(argv);
	}

	if (line != NULL)
		free(line);

	if (right_path != NULL)
		free(right_path);
}

/**
 * tokenize - tokenize the stdin
 * @bytes_read: number of character from line
 * @line: the buffer that contain the str from the stdin
 * Return: char **, the stdin tokenized
 */
char **tokenize(ssize_t bytes_read, char *line)
{
	char *token = NULL;
	char **array = NULL;
	size_t capacity = 10;
	size_t i = 0;
	size_t j;

	if (bytes_read > 0 && line[bytes_read - 1] == '\n')
		line[bytes_read - 1] = '\0';

	array = malloc(sizeof(char *) * capacity);
	if (array == NULL)
	{
		perror("Malloc failed");
		exit(1);
	}
	if (bytes_read == -1)
		free(line), printf("\n"), exit(0);

	token = strtok(line, " ");
	while (token != NULL)
	{
		if (i >= capacity)
			capacity *= 2;
		if (i >= capacity)
		{
			char **new_array = malloc(sizeof(char *) * capacity);
			if (new_array == NULL)
				perror("Malloc failed"), exit(1);

			for (j = 0; j < i; j++)
				new_array[j] = array[j];
			free(array), array = new_array;
		}
		array[i] = token, i++;
		token = strtok(NULL, " ");
	}

	array[i] = NULL;
	return (array);
}

/**
 * _getenv - find the format of the command, then execve it
 * @void: no arg
 * Return: char **, the path
 */
char **_getenv(void)
{
	char *token = NULL, *path_var_copy = NULL, *path_var = NULL;
	char **full_path = NULL;
	char **env = environ;
	int j = 0, i, k, num_paths = 0;

	for (i = 0; env[i] != NULL; i++)
	{
		if (strncmp(env[i], "PATH=", 5) == 0)
		{
			path_var = env[i] + 5;
			break;
		}
	}

	if (path_var == NULL)
		return (NULL);
	path_var_copy = strdup(path_var);
	if (path_var_copy == NULL)
		return (NULL);

	for (token = strtok(path_var_copy, ":");
		 token != NULL; token = strtok(NULL, ":"))
		num_paths++;

	free(path_var_copy);

	full_path = malloc((num_paths + 1) * sizeof(char *));
	if (full_path == NULL)
		return (NULL);
	for (token = strtok(path_var, ":"); token != NULL; token = strtok(NULL, ":"))
	{
		full_path[j] = strdup(token);
		if (full_path[j] == NULL)
		{
			for (k = 0; k < j; k++)
				free(full_path[k]);
			free(full_path);
			return (NULL);
		}
		j++;
	}
	full_path[j] = NULL;

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

	fprintf(stderr, "./simple_shell: %s: No such file or directory\n", argv[0]);
	return (NULL);
}
