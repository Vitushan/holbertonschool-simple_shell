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
		char **argv = NULL;
		char *line = NULL;
		int status, get_cmd_return;

		printf("#simple_shell$ ");

		argv = _get_line(&line);
		if (argv == NULL)
		{
			free(line);
			return (-1);
		}

		get_cmd_return = get_command(argv);
		if (get_cmd_return == 50)
		{
			free(argv);
			free(line);
			exit(0);
		}
		else if (get_cmd_return == 0)
		{
			wait(&status);
			_wait_status(status);
		}
		free(argv);
		free(line);
	}

	return (0);
}

/**
 * _wait_status - get status of the wait function
 * @status: the return status of the child process
 * Return: int
 */
int _wait_status(int status)
{
	if (WIFEXITED(status))
	{
		int exit_status = WEXITSTATUS(status);

		if (exit_status == 0)
		{
			return (0);
		} else if (exit_status != 0)
		{
			fprintf(stderr, "Error: Command failed with exit code %d\n", exit_status);
			return (exit_status);
		}
	}
	else if (WIFSIGNALED(status))
	{
		int signal_number = WTERMSIG(status);

		fprintf(stderr, "Error: Command terminated by signal %d\n", signal_number);
		return (signal_number + 128);
	}
	else if (WIFSTOPPED(status))
	{
		int signal_number = WSTOPSIG(status);

		fprintf(stderr, "Error: Command stopped by signal %d\n", signal_number);
		return (signal_number + 128);
	}

	return (-1);
}

/**
 * get_command - find the format of the command, then execve it
 * @argv: the command to execute
 * Return: int
 */
int get_command(char **argv)
{
	pid_t pid;
	char *new_argv0 = NULL;

	if (_strcmp(argv[0], "exit") == 0)
		return (50);

	if (argv[0][0] != '/')
	{
		char *_path = "/bin/";
		char buffer[100] = {0};

		new_argv0 = malloc(_strlen(_path) + _strlen(argv[0]) + 1);
		if (new_argv0 == NULL)
			return (-1);

		_strcpy(buffer, argv[0]), _strcpy(new_argv0, _path);
		_strcat(new_argv0, buffer);

		argv[0] = new_argv0;
	}
	if (access(argv[0], F_OK) != 0)
	{
		fprintf(stderr, "./simple_shell: 1: %s: not found\n", argv[0]);
		free(new_argv0);
		return (-1);
	}
	pid = fork();
	if (pid == -1)
		perror("Error"), exit(EXIT_FAILURE), free(argv);

	if (pid == 0)
	{
		if (execve(argv[0], argv, NULL) == -1)
		{
			perror("Error"), free(argv);
			exit(EXIT_FAILURE);
		}
	}

	return (0);
}

/**
 * _get_line - get the line (stdin) and split it into tokens
 * @line: the str to tokenize
 * Return: char **
 */
char **_get_line(char **line)
{
	int i = 0;
	size_t len = 0;
	size_t bytes_read;
	char *token = NULL;
	char **array = NULL;
	size_t capacity = 10;

	bytes_read = getline(line, &len, stdin);
	if (bytes_read > 0 && (*line)[bytes_read - 1] == '\n')
		(*line)[bytes_read - 1] = '\0';
	array = malloc(sizeof(char *) * capacity);
	if (array == NULL)
	{
		perror("Malloc failed");
		exit(1);
	}
	if (bytes_read == -1)
		free(*line), printf("\n"), exit(0);

	token = strtok(*line, " ");
	while (token != NULL)
	{
		if (i >= capacity)
		{
			capacity *= 2;
			char **new_array = malloc(sizeof(char *) * capacity);

			if (new_array == NULL)
				perror("Malloc failed"), exit(1);

			for (int j = 0; j < i; j++)
				new_array[j] = array[j];
			free(array), array = new_array;
		}
		array[i] = token, i++;
		token = strtok(NULL, " ");
	}
	array[i] = NULL;
	return (array);
}
