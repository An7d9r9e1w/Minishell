#include "../incs/function_unset.h"

static int validate_env(const char *str)
{
	int i;

	i = 0;
	if ((str[i] >= '0'&& str[i] <= '9'))
	{
		printf("unset: %s: invalid parameter name\n", str);
		return (0);
	}
	else if (str[i] == '=')
	{
		str++;
		printf("msh: %s not found\n", str);
		return (0);
	}
	while (str[i])
	{
		if (str[i] == '=')
		{
			printf("unset: %s: invalid parameter name\n", str);
			return (0);
		}
		i++;
	}
	return (1);
}

int msh_unset(char **args, t_vvector *env)
{
	int index;
	char *need_str;

	need_str = NULL;
	if (!args[1])
	{
		write(2, "unset: not enough arguments\n", 28);
		return (1);
	}
	if (validate_env(args[1]))
	{
		need_str = get_str(args[1]);
		index = vvector_get_index_n(env, need_str, mstrlen(need_str), ft_strncmp);
		if (index != -1)
			vvector_erase(env, index, free);
	}
	if (need_str)
		free(need_str);
	return (1);
}
