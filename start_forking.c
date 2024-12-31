#include <stdlib.h>
#include <sys/wait.h>
#include <stdio.h>
#include <string.h>
#include <signal.h>
#include "main.h"


/**
 * handle_signal - handle the CTRL-C command to ignore it
 * @sig: the signal (ctrl-c)
 * Return: void
 */
void handle_signal(int sig)
{
	(void)sig;
    printf("\n");
	printf(":) ");
    fflush(stdout);
}

/**
 * forking - starting the child process to execute the command
 * @right_path: the PATH to the shell command
 * @argv: the entiere line from getline
 * Return: 0 on succes
 */
int forking(char *right_path, char **argv)
{
	pid_t pid;
	int status;

	pid = fork();

	if (pid == -1)
	{
		perror("Fork failed");
		return (-1);
	}
	else if (pid == 0)
	{
		if (execve(right_path, argv, environ) == -1)
		{
			exit(EXIT_FAILURE);
		}
	}
	else
	{
		wait(&status);
	}

	if (right_path != argv[0])
	{
		free(right_path);
	}

	return (0);
}

/**
 * free_line_fullpath - free line and full_path
 * @full_path: the arr that contain the tokenize env var PATH
 * @line: the line from the stdin
 * Return: void
 */
void free_line_fullpath(char **full_path, char *line)
{
	int i;

	free(line);

	for (i = 0; full_path[i] != NULL; i++)
	{
		free(full_path[i]);
	}

	free(full_path);
}
