/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   function_cd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ejina  <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/04 11:05:25 by ejina             #+#    #+#             */
/*   Updated: 2021/08/08 10:23:26 by nnamor           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

#include <function_cd.h>
#include <error.h>

static char	*get_path(t_vvector *my_env, const char *name, int len)
{
	char			*path;
	int				i;
	int				j;
	unsigned int	size;

	size = 0;
	while (size < my_env->size)
	{
		if (!mstrncmp(my_env->arr[size], name, len))
		{
			path = malloc(sizeof(char)
					* (mstrlen(my_env->arr[size]) - len + 1));
			if (!path)
				return (error_p(-1));
			i = -1;
			j = 0;
			while (((char **)my_env->arr)[size][++i])
				if (i >= len)
					path[j++] = ((char **) my_env->arr)[size][i];
			path[j] = 0;
			return (path);
		}
		size++;
	}
	return (0);
}

static char	*help_change(t_vvector *my_env, const char *str)
{
	char	*need_path;

	need_path = get_path(my_env, str, mstrlen(str));
	if (!need_path)
	{
		write(2, "msh: cd: ", 9);
		write(2, str, mstrlen(str));
		write(2, " not set\n", 9);
		return (0);
	}
	if (update_oldpwd(my_env) < 0)
		return (0);
	return (need_path);
}

static int	change_path(int n, t_vvector *my_env)
{
	char	*need_path;

	need_path = NULL;
	if (n == 0)
		need_path = help_change(my_env, "HOME=");
	else if (n == 1)
		need_path = help_change(my_env, "OLDPWD=");
	if (!need_path)
		return (-1);
	if (chdir(need_path) != 0)
		return (error(-1, 0, 0));
	else
		if (update_pwd(my_env) < 0)
			return (-1);
	free (need_path);
	need_path = NULL;
	return (1);
}

int	msh_cd(char **args, t_vvector *my_env)
{
	if (args[1] == NULL)
	{
		if (change_path(0, my_env) < 0)
			return (-1);
	}
	else if (!mstrcmp(args[1], "-"))
	{
		if (change_path(1, my_env) < 0)
			return (-1);
	}
	else
	{
		if (update_oldpwd(my_env) < 0)
			return (-1);
		if (chdir(args[1]) < 0)
			return (error(-1, 0, 0));
		else
			if (update_pwd(my_env) < 0)
				return (-1);
	}
	return (1);
}
