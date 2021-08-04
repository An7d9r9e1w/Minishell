/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   function_cd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ejina  <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/04 11:05:25 by ejina             #+#    #+#             */
/*   Updated: 2021/08/04 11:08:08 by nnamor           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

#include <function_cd.h>
#include <vvector.h>

static int update_oldpwd(t_vvector *my_env)
{
	char str[BUFSIZE];
	char *oldpwd;
	unsigned int i;

	if (!getcwd(str, BUFSIZE))
		return (0);
	oldpwd = ft_strjoin("OLDPWD=", str);
	if (!oldpwd)
		return (0);
	i = 0;
	while (i < my_env->size)
	{
		if (!ft_strncmp(my_env->arr[i], "OLDPWD=", 7))
		{
			vvector_erase(my_env, i, free);
			vvector_put(my_env, oldpwd);
			return (1);
		}
		i++;
	}
	free(oldpwd);
	oldpwd = NULL;
	return (0);
}
static int update_pwd(t_vvector *my_env)
{
	char str[BUFSIZE];
	char *pwd;
	unsigned int i;

	if (!getcwd(str, BUFSIZE))
		return (0);
	pwd = ft_strjoin("PWD=", str);
	if (!pwd)
		return (0);
	i = 0;
	while (i < my_env->size)
	{
		if (!ft_strncmp(my_env->arr[i], "PWD=", 4))
		{
			vvector_erase(my_env, i, free);
			vvector_put(my_env, pwd);
			return (1);
		}
		i++;
	}
	free(pwd);
	pwd = NULL;
	return (0);
}
static char *get_path(t_vvector *my_env, const char *name, int len)
{
	char *path;
	int i;
	int j;
	unsigned int size;

	size = 0;
	while (size < my_env->size)
	{
		if (!ft_strncmp(my_env->arr[size], name, len))
		{
			path = malloc(sizeof(char) * (ft_strlen(my_env->arr[size]) - len + 1));
			if (!path)
				return (path);
			i = -1;
			j = 0;
			while (((char **)my_env->arr)[size][++i])
			{
				if (i >= len)
					path[j++] = ((char **) my_env->arr)[size][i];
			}
			path[j] = 0;
			return (path);
		}
		size++;
	}
	return (NULL);
}

static char	*help_change(t_vvector *my_env, const char *str)
{
	char *need_path;

	need_path = get_path(my_env, str, ft_strlen(str));
	if (!need_path)
	{
		write(2, "msh: cd: ", 9);
		write(2, str, ft_strlen(str));
		write(2, " not set\n", 9);
		return NULL;
	}
	update_oldpwd(my_env);
	return (need_path);
}

static void change_path(int n, t_vvector *my_env)
{
	char *need_path;

	need_path = NULL;
	if (n == 0)
		need_path = help_change(my_env, "HOME=");
	else if (n == 1)
		need_path = help_change(my_env, "OLDPWD=");
	if (!need_path)
		return ;
	if (chdir(need_path) != 0)
	{
		write(2, strerror(errno), ft_strlen(strerror(errno)));
		write(2, "\n", 1);
	}
	else
		update_pwd(my_env);
	free (need_path);
	need_path = NULL;
}

int	msh_cd(char **args, t_vvector *my_env)
{
	char *err;

	if (args[1] == NULL)
		change_path(0, my_env);
	else if (!ft_strcmp(args[1], "-"))
		change_path(1, my_env);
	else
	{
		update_oldpwd(my_env);
		if (chdir(args[1]) != 0)
		{
			err = strerror(errno);
			write(2, err, ft_strlen(err));
			write(2, "\n", 1);
		}
		else
			update_pwd(my_env);
	}
	return (1);
}
