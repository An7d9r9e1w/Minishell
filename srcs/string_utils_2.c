/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   string_utils_2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nnamor <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/31 10:03:20 by nnamor            #+#    #+#             */
/*   Updated: 2021/07/31 10:10:15 by nnamor           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

#include <string_utils.h>

char	**convert_into_solid_arr(char **strs, unsigned int len)
{
	char			**arr;
	char			*tmp;
	unsigned int	chars;
	unsigned int	i;

	chars = 0;
	i = -1;
	while (++i < len)
		chars += mstrlen(strs[i]) + 1;
	arr = malloc(sizeof(char *) * (len + 1) + sizeof(char) * chars);
	if (!arr)
		return (0);
	tmp = (char *)(arr + len + 1);
	i = -1;
	while (++i < len)
	{
		chars = mstrlen(strs[i]) + 1;
		arr[i] = tmp;
		mstrlcpy(tmp, strs[i], chars);
		tmp += chars;
	}
	arr[len] = 0;
	return (arr);
}
