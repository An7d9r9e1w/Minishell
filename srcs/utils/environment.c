/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environment.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ejina <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/04 12:56:23 by ejina             #+#    #+#             */
/*   Updated: 2021/08/12 14:49:32 by nnamor           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stdio.h>//TEST

#include <vvector.h>
#include <cvector.h>
#include <string_utils.h>
#include <error.h>

t_vvector	*get_environments(char **env)
{
	t_vvector	*vv;

	vv = vvector_create();
	if (!vv)
		return (0);
	while (*env)
	{
		if (vvector_put(vv, mstrdup(*env++)) == -1)
		{
			vvector_free(vv);
			return (0);
		}
	}
	return (vv);
}

int	get_environment_index(t_vvector *envs, char	*name)
{
	unsigned int	i;
	int				name_len;

	if (!name || !*name)
		return (-1);
	name_len = mstrlen(name);
	i = -1;
	while (++i < envs->size)
		if (!mstrncmp(envs->arr[i], name, name_len)
			&& ((char *)envs->arr[i])[name_len] == '=')
			return (i);
	return (-1);
}

int	last_return(int new_stat, int get)
{
	static int	stat = 0;

	if (get)
		return (stat);
	stat = new_stat;
	return (stat);
}

char	*get_environment_value(t_vvector *envs, char *name)
{
	unsigned int	i;

	if (!mstrcmp(name, "?"))
		return (mitoa(last_return(0, 1)));
	i = get_environment_index(envs, name);
	if (i == (unsigned int)(-1))
		return (0);
	return (envs->arr[i] + mstrlen(name) + 1);
}

int	set_environment(t_vvector *envs, char *name, char *value)
{
	t_cvector	*cv;
	int			index;

	if (!name || !value)
		return (-1);
	cv = 0;
	cv = cvector_create();
	if (!cv || cvector_write(cv, name, mstrlen(name)) == -1
		|| cvector_write(cv, "=", 1) == -1
		|| cvector_write(cv, value, mstrlen(value)) == -1)
	{
		cvector_free(cv);
		return (-1);
	}
	index = get_environment_index(envs, name);
	if (index >= 0)
	{
		free(envs->arr[index]);
		envs->arr[index] = mstrdup(cv->arr);
		cvector_free(cv);
		return (-!(envs->arr[index]));
	}
	index = vvector_put(envs, mstrdup(cv->arr));
	cvector_free(cv);
	return (index);
}
