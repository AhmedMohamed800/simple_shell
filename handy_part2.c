#include "shell.h"

/**
 * count_words - counting func
 * @c: input
 *
 * Return: int
 */
int count_words(char *c)
{
	int words = 2;
	char *d = {" "};

	while (*c)
	{
		if (*c == *d)
			words++;
		c++;
	}
	return(words);
}
