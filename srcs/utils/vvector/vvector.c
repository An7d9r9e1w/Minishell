/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vvector.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nnamor <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/31 10:04:08 by nnamor            #+#    #+#             */
/*   Updated: 2021/08/03 14:24:21 by nnamor           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

#include <vvector.h>
#include <error.h>

t_vvector	*vvector_create(void)
{
	t_vvector	*vv;

	vv = malloc(sizeof(t_vvector));
	if (!vv)
		return (error_p(-1));
	vv->capacity = VV_CAPACITY;
	vv->arr = malloc(sizeof(void *) * vv->capacity);
	if (!vv->arr)
	{
		free(vv);
		return (error_p(-1));
	}
	vv->size = 0;
	return (vv);
}

void	vvector_free(t_vvector *vv)
{
	if (vv)
	{
		if (vv->arr)
		{
			while (vv->size)
				free(vv->arr[--vv->size]);
			free(vv->arr);
		}
		free(vv);
	}
}

static int	vvector_realloc(t_vvector *vv, unsigned int new_size)
{
	void	**arr;
	void	**arr_cur;
	int		i;

	arr = malloc(sizeof(void *) * new_size);
	if (!arr)
		return (error(-1, 0, 0));
	arr_cur = arr;
	i = vv->size;
	while (i--)
		*arr_cur++ = *vv->arr++;
	free(vv->arr - vv->size);
	vv->arr = arr;
	vv->capacity = new_size;
	return (0);
}

int	vvector_put(t_vvector *vv, void *data)
{
	if (!data)
		return (-1);
	if (vv->size == vv->capacity
		&& vvector_realloc(vv, vv->size << 1) == -1)
		return (-1);
	vv->arr[vv->size++] = data;
	return (0);
}

int	vvector_erase(t_vvector *vv, unsigned int index, void (*free_s)(void *))
{
	if (index >= vv->size || !free_s)
		return (-1);
	free_s(vv->arr[index]);
	if (--vv->size)
		vv->arr[index] = vv->arr[vv->size];
	return (0);
}
