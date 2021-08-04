/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vvector_2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nnamor <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/01 09:13:57 by nnamor            #+#    #+#             */
/*   Updated: 2021/08/03 14:24:54 by nnamor           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

#include <vvector.h>
#include <error.h>

int	vvector_get_index(t_vvector *vv, void *to_find,
		int	(*compare)(const void *, const void *))
{
	void			*arr_cur;
	unsigned int	i;

	if (!to_find || !compare)
		return (-1);
	arr_cur = vv->arr;
	i = vv->size;
	while (i--)
		if (!compare(arr_cur++, to_find))
			return (vv->size - i - 1);
	return (-1);
}

void	*vvector_find(t_vvector *vv, void *to_find,
			int (*compare)(const void *, const void *))
{
	int	index;

	index = vvector_get_index(vv, to_find, compare);
	if (index == -1)
		return (0);
	return (vv->arr[index]);
}

int	vvector_replace(t_vvector *vv, unsigned int index, void *data)
{
	if (!data)
		return (-1);
	if (index > vv->size)
		return (vvector_put(vv, data));
	free(vv->arr[index]);
	vv->arr[index] = data;
	return (0);
}

static int	vvector_memcpy(unsigned char *dst, const unsigned char *src,
		unsigned int width)
{
	const unsigned char	*begin = dst;

	while (width--)
		*dst++ = *src++;
	return (dst - begin);
}

void	*vvector_export(t_vvector *vv, unsigned int width, int *len)
{
	unsigned char		*arr;
	unsigned int		i;

	if (!vv->size)
		return (0);
	arr = malloc(width * vv->size);
	if (!arr)
		return (error_p(-1));
	i = -1;
	while (++i < vv->size)
		arr += vvector_memcpy(arr, vv->arr[i], width);
	*len = vv->size;
	return (arr - vv->size * width);
}
