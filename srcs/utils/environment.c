/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environment.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ejina <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/04 12:56:23 by ejina             #+#    #+#             */
/*   Updated: 2021/08/04 15:51:08 by nnamor           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <vvector.h>
#include <string_utils.h>

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

char	*get_environment_value(t_vvector *envs, char *name)
{
	unsigned int	i;

	i = get_environment_index(envs, name);
	if (i == (unsigned int)(-1))
		return (0);
	return (envs->arr[i] + mstrlen(name) + 1);
}
