/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   function_env.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ejina <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/04 11:54:02 by ejina             #+#    #+#             */
/*   Updated: 2021/08/04 11:55:09 by nnamor           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/function_env.h"
#include "../incs/vvector.h"

int	msh_env(char **args, t_vvector *env)
{
	unsigned int	i;

	(void)args;
	mqsort(env->arr, env->size, sizeof(void *), mstrcmp);
	i = 0;
	while (i < env->size)
	{
		printf("%s\n", (char *)env->arr[i]);
		i++;
	}
	return (1);
}
