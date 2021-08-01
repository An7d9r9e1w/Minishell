/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vvector_2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nnamor <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/01 09:13:57 by nnamor            #+#    #+#             */
/*   Updated: 2021/08/01 09:29:35 by nnamor           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <vvector.h>

int	vvector_get_index(t_vvector *vv, void *to_find,
		int	(*compare)(const void *, const void *))
{
	void			*arr_cur;
	unsigned int	i;

	if (!to_find || !compare)
		return (-1);
	arr_cur = vv->arr;
	i = vv->arr;
	i = vv->size;
	while (i--)
		if (!compare(arr_cur++, to_find))
			return (vv->size - i - 1);
	return (-1);
}

void	*vvector_find(t_vvector *vv, void *to_find,
			int (*compare)(const char *, const void *))
{
	int	index;

	index = vvector_get_index(vv, to_find, compare);
	if (index == -1)
		return (0);
	return (vv->arr[index]);
}

int	vvector_replace(t_vvector *vv, unsigned int index, void *data)
{
	if (index > vv->size)
		return (vvector_put(vv, data));
	free(vv->arr[index]);
	vv->arr[index] = data;
	return (0);
}
