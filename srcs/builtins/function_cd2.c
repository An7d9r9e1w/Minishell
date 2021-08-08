/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   function_cd2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ejina  <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/04 11:05:25 by ejina             #+#    #+#             */
/*   Updated: 2021/08/08 10:25:08 by nnamor           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

#include <function_cd.h>
#include <error.h>

int	update_oldpwd(t_vvector *my_env)
{
	char			str[BUFSIZE];
	char			*oldpwd;
	unsigned int	i;

	if (!getcwd(str, BUFSIZE))
		return (error(-1, 0, 0));
	oldpwd = mstrjoin("OLDPWD=", str);
	if (!oldpwd)
		return (-1);
	i = 0;
	while (i < my_env->size)
	{
		if (!mstrncmp(my_env->arr[i], "OLDPWD=", 7))
		{
			if (vvector_erase(my_env, i, free) < 0)
				return (-1);
			if (vvector_put(my_env, oldpwd) < 0)
				return (-1);
			return (1);
		}
		i++;
	}
	free(oldpwd);
	oldpwd = NULL;
	return (1);
}

int	update_pwd(t_vvector *my_env)
{
	char			str[BUFSIZE];
	char			*pwd;
	unsigned int	i;

	if (!getcwd(str, BUFSIZE))
		return (error(-1, 0, 0));
	pwd = mstrjoin("PWD=", str);
	if (!pwd)
		return (-1);
	i = 0;
	while (i < my_env->size)
	{
		if (!mstrncmp(my_env->arr[i], "PWD=", 4))
		{
			if (vvector_erase(my_env, i, free) < 0)
				return (-1);
			if (vvector_put(my_env, pwd) < 0)
				return (-1);
			return (1);
		}
		i++;
	}
	free(pwd);
	pwd = NULL;
	return (1);
}
