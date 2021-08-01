#include "../headers/function_env.h"

int msh_env(char **args, char **env)
{
	(void)args;
	while (*env)
	{
		printf("%s\n", *env);
		env++;
	}
	return (1);
}