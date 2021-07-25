#include "function_unset.h"

static int index_env(const char *arg, char **env)
{
	int	i;
	int	j;

	i = 0;
	while(env[i])
	{
		j = 0;
		while (env[i][j] == arg[j] && env[i][j] != '=')
			j++;
		if (env[i][j] == '=')
			return (i);
		i++;
	}
	return (-1);
}

int msh_unset(char **args, char **env)
{
	int i;

	i = 0;
	if (!args[1])
	{
		write(2, "unset: not enough arguments\n", 28);
		return (0);
	}
	i = index_env(args[1], env);
	if (i != -1)
	{
		env[i] = NULL;
		while(env[i + 1])
		{
			env[i] = env[i + 1];//strdup?
			i++;
		}
		env[i] = NULL;
	}
	return (1);
}