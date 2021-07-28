#include "function_export.h"

static int validate_env(const char *str)
{
	int i;

	i = 0;
	if ((str[i] >= '0' && str[i] <= '9') || str[i] == '=')
	{
		write(2, "export: not an identifier: ", 27);
		while (*str && *str != '=')
		{
			write(2, str, 1);
			str++;
		}
		write(2, "\n", 1);
		return (0);
	}
	while (str[i])
	{
		if (str[i] == '=')
			return (1);
		i++;
	}
	return (0);
}

int msh_export(char **args, char **env)
{
	if (args[1] == NULL)
		msh_env(args, env);
	else
	{
		if (validate_env(args[1]))
		{
			while (*env)
				env++;
			*env = args[1];
			env[1] = NULL;
		}
		else
			return (0);
	}
	return (1);
}
