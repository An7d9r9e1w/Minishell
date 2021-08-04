/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vvector_3.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nnamor <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/03 09:17:29 by nnamor            #+#    #+#             */
/*   Updated: 2021/08/03 14:25:13 by nnamor           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

#include <vvector.h>
#include <error.h>

void	*vvector_copy(t_vvector *vv)
{
	void			**arr;
	unsigned int	i;

	if (!vv->size)
		return (0);
	arr = malloc(sizeof(void *) * (vv->size + 1));
	if (!arr)
		return (error_p(-1));
	i = -1;
	while (++i < vv->size)
		*arr++ = vv->arr[i];
	*arr = 0;
	vv->size = 0;
	return (arr - i);
}

int	vvector_clear(t_vvector *vv)
{
	if (!vv->size)
		return (-1);
	while (vv->size--)
		free(vv->arr[vv->size]);
	vv->size = 0;
	return (0);
}
