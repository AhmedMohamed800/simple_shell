#include "shell.h"

/**
* _strcmp - concatenates two strings
* @s1: the first string
* @s2: the second string
* Return: (s1 < s2 - s1 > s2 - s1 = s2) less - equal - > 0
*/
int _strcmp(char *s1, char *s2)
{
	while ((*s1 != '\0' && *s2 != '\0') && (*s1 == *s2))
	{
		s1++;
		s2++;
	}
	if (*s2 == '=')
		return (0);
	return (*s1 - *s2);
}

/**
* get_env - gets the value of an environment variable
* @identi: the identifier of the vairable
* @envp: the environments array
* Return: a string tha contains the value of an ev.
*/
char *get_env(char *identi, char **envp)
{
	int n = 0;
	char *env_var, *value, *final;
	size_t env_size, i, value_size;

	while (envp[n] != NULL)
	{
		if (_strcmp(identi, envp[n]) == 0)
		{
			env_var = envp[n];
			env_size = size_of(env_var, 0);
			for (i = 0; i < env_size; i++)
			{
				if (env_var[i] == '=')
				{
					value = &env_var[i + 1];
					value_size = size_of(value, 0) + 1;
					final = malloc(value_size + 1);
					if (final == NULL)
					{
						perror("Error with malloc");
						return (NULL);
					}
					_strcpy(final, value);
					return (final);
				}
			}
		}
		n++;
	}
	return ("Not found");
}

/**
* size_of - gives the value of a string
* @str: string to be misured
* @spaces: 0 if str length and 1 if spaces length - 2 means :
* Return: size of a string
*/
size_t size_of(char *str, size_t spaces)
{
	size_t i = 0;

	if (spaces == 0)
	{
		while (*str++)
			i++;
	}
	else if (spaces == 1)
	{
		while (*str)
		{
			if (*str == ' ')
				i++;
			str++;
		}
		i += 2;
	}
	else if (spaces == 2)
	{
		while (*str)
		{
			if (*str == ':')
				i++;
			str++;
		}
		i += 2;
	}
	return (i);
}

/**
* _strcpy - copies the string pointed to by src
* @dest: pointer to the buffer in which we copy the string
* @src: string to be copied
* Return: the pointer to dest
*/
char *_strcpy(char *dest, char *src)
{
	int i;

	for (i = 0; src[i]; i++)
	{
		dest[i] = src[i];
	}
	dest[i] = '\0';
	return (dest);
}

/**
* _free_array - frees an array of strings
* @arr: array to free
* Return: nothing
*/
void _free_array(char **arr)
{
	int i;

	if (arr == NULL)
		return;
	for (i = 0; arr[i] != NULL; i++)
	{
		free(arr[i]);
	}
	free(arr);
}
