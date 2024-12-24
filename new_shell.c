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
		size_t len = 0;
		ssize_t nread;

		printf("#simple_shell$ ");

		nread = getline(&line, &len, stdin);
		
	}

	return (0);
}
