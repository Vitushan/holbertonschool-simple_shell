#include <stdio.h>

int main(int ac, char **argv)
{
	unsigned int i = 0, j;

		while (argv[i] != NULL)
			i++;

		for (j = 0; j < ac; j++)
			printf("argv[%d] = %s\n", j, argv[j]);


			printf("%d\n", i);
			return (0);
}
