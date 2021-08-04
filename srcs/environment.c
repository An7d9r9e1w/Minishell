/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environment.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ejina <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/04 12:56:23 by ejina             #+#    #+#             */
/*   Updated: 2021/08/04 13:02:06 by nnamor           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <vvector.h>
#include <string_utils.h>

t_vvector *get_env(char **env)
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
