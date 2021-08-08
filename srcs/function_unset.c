/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   function_unset.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ejina <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/04 11:56:06 by ejina             #+#    #+#             */
/*   Updated: 2021/08/04 15:48:25 by nnamor           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/function_unset.h"
#include "../incs/environment.h"
#include "../incs/error.h"

static int	validate_env(const char *str)
{
	int	i;

	i = 0;
	if ((str[i] >= '0' && str[i] <= '9'))
	{
		printf("unset: %s: invalid parameter name\n", str);
		return (-1);
	}
	else if (str[i] == '=')
	{
		str++;
		printf("msh: %s not found\n", str);
		return (-1);
	}
	while (str[i])
	{
		if (str[i] == '=')
		{
			printf("unset: %s: invalid parameter name\n", str);
			return (-1);
		}
		i++;
	}
	return (1);
}

int	msh_unset(char **args, t_vvector *env)
{
	int		index;
	char	*need_str;

	need_str = NULL;
	if (!args[1])
	{
		write(2, "unset: not enough arguments\n", 28);
		return (-1);
	}
	if (validate_env(args[1]) > 0)
	{
		need_str = get_str(args[1]);
		if (!need_str)
			return (-1);
		index = get_environment_index(env, need_str);
		if (index != -1)
			vvector_erase(env, index, free);
	}
	if (need_str)
		free(need_str);
	return (1);
}
