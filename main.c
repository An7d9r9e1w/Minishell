#include "main.h"
#include <stdio.h>
#include <unistd.h>
int ft_strlen(const char *str);

int msh_exit(char **args)
{
	(void)args;
	return (0);
}

//// Для cd сделать переключение на HOME,чтобы в env менялись значения
int main(int argc, char **argv, char **env)
{
	msh_env(argv, env);
	printf("--------------------------\n");
	msh_export(argv, env);
	printf("--------------------------\n");
	msh_env(argv, env);
	(void)argc;
	return 0;
}