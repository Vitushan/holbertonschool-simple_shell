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
	char **argv = NULL, **full_path = NULL;
	char *line = NULL, *right_path = NULL;
	size_t len = 0;
	ssize_t nread;
	int is_interactive, iteration = 0;

	full_path = _getenv();
	if (full_path == NULL)
		perror("Failed to get PATH"), exit(EXIT_FAILURE);
	is_interactive = isatty(STDIN_FILENO);
	signal(SIGINT, handle_signal);
	while (1)
	{
		iteration++;
		if (is_interactive == 1)
			printf(":) ");
		nread = getline(&line, &len, stdin);
		if (nread == -1)
		{
			if (is_interactive == 1)
				printf("\n");
			break;
		}
		argv = tokenize(nread, line);
		if (argv == NULL || argv[0] == NULL || argv[0][0] == '\0')
		{
			free(argv);
			continue;
		}
		if (_strcmp(argv[0], "exit") == 0)
		{
			free(argv), free_line_fullpath(full_path, line);
			exit(0);
		}
		right_path = get_the_right_path(argv[0], full_path, iteration);
		if (right_path != NULL)
			forking(right_path, argv), free(argv);
	}
	free_line_fullpath(full_path, line);
	return (0);
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
		if (_strncmp(env[i], "PATH=", 5) == 0)
		{
			path_var = _strdup(env[i] + 5);
			break;
		}
	}
	if (path_var == NULL)
		return (NULL);
	path_var_copy = _strdup(path_var);
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
		full_path[j] = _strdup(token);
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
	free(path_var);
	return (full_path);
}

/**
 * get_the_right_path - find the right path to execute the shell command
 * @argv: the command to execute
 * @full_path: the env variable "PATH="
 * @i: the number of the iteration from the main loop
 * Return: char *, the right path, or NULL
 */
char *get_the_right_path(char *argv, char **full_path, int i)
{
	char *path_finded = NULL;
	int j = 0, found = 0, abs_path = 0;

	if (_strncmp(argv, "/", 1) == 0)
	{
		abs_path = 1;
		if (access(argv, F_OK) == 0)
		{
			if (access(argv, X_OK) == 0)
				return (_strdup(argv));
			found = 1;
		}
	}

	while (full_path[j] != NULL && abs_path == 0)
	{
		path_finded = malloc(_strlen(full_path[j]) + _strlen(argv) + 2);
		if (path_finded == NULL)
			return (NULL);

		sprintf(path_finded, "%s/%s", full_path[j], argv);

		if (access(path_finded, F_OK) == 0)
		{
			if (access(path_finded, X_OK) == 0)
				return (path_finded);
			found = 1;
			free(path_finded);
		}
		else
			free(path_finded);
		j++;
	}

	if (found == 1)
		fprintf(stderr, "./hsh: %d: %s: Permission denied\n", i, argv);

	fprintf(stderr, "./hsh: %d: %s: not found\n", i, argv);

	return (NULL);
}
