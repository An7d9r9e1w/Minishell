/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   function_export.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ejina <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/04 11:55:24 by ejina             #+#    #+#             */
/*   Updated: 2021/08/04 15:47:44 by nnamor           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/function_export.h"
#include "../incs/environment.h"
#include "../incs/error.h"

static int	validate_env(const char *str)
{
	int	i;

	i = 0;
	if ((str[i] >= '0' && str[i] <= '9'))
	{
		write(2, "export: not an identifier: ", 27);
		while (*str && *str != '=')
		{
			write(2, str, 1);
			str++;
		}
		write(2, "\n", 1);
		return (-1);
	}
	else if (str[i] == '=')
	{
		str++;
		printf("msh: %s not found\n", str);
		return (-1);
	}
	while (str[i])
		if (str[i++] == '=')
			return (1);
	return (-1);
}

char	*get_str(char *str)
{
	char	*need_str;
	int		i;

	i = 0;
	need_str = malloc(mstrlen(str) + 1);
	if (!need_str)
		return (error_p(-1));
	while (str[i] && str[i] != '=')
	{
		need_str[i] = str[i];
		i++;
	}
	need_str[i] = 0;
	return (need_str);
}

int	msh_export(char **args, t_vvector *env)
{
	char	*str;
	int		index;
	char	*need_str;

	need_str = NULL;
	if (args[1] == NULL)
		msh_env(args, env);
	else if (validate_env(args[1]) > 0)
	{
		need_str = get_str(args[1]);
		if (!need_str)
			return (-1);
		str = mstrdup(args[1]);
		if (!str)
			return (-1);
		index = get_environment_index(env, need_str);
		if (index != -1)
			vvector_erase(env, index, free);
		vvector_put(env, str);
	}
	if (need_str)
		free(need_str);
	return (1);
}
