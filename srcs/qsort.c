/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   qsort.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nnamor <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/01 07:19:13 by nnamor            #+#    #+#             */
/*   Updated: 2021/08/01 07:36:46 by nnamor           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

static void	swapv(void *a1, void *a2, size_t width)
{
	unsigned char	*ac1;
	unsigned char	*ac2;
	unsigned char	tmp;

	ac1 = (unsigned char *)a1;
	ac2 = (unsigned char *)a2;
	while (width--)
	{
		tmp = *ac1;
		*ac1++ = *ac2;
		*ac2++ = tmp;
	}
}

static void	*memdup(void *base, size_t width)
{
	unsigned char	*p;
	unsigned char	*basec;
	unsigned char	*p_cur;
	size_t			i;

	p = (unsigned char *)malloc(width);
	if (!p)
		return (NULL);
	basec = (unsigned char *)base;
	p_cur = p;
	i = -1;
	while (++i < width)
		*p_cur++ = *basec++;
	return ((void *)p);
}

static size_t	partition(void *base, size_t nel, size_t width,
			int (*compare)(const void *, const void *))
{
	void			*pivot;
	size_t			low;
	size_t			high;

	pivot = memdup((void *)(base + (nel >> 1) * width), width);
	if (!pivot)
		return (-1);
	low = 0;
	high = nel * width;
	while (1)
	{
		while (compare((void *)(base + low), pivot) < 0)
			low += width;
		while (compare((void *)(base + high), pivot) > 0)
			high -= width;
		if (low >= high)
		{
			free(pivot);
			return (high / width);
		}
		swapv((void *)(base + low), (void *)(base + high), width);
		low += width;
		high -= width;
	}
}

void	mqsort(void *base, size_t nel, size_t width,
			int (*compar)(const void *, const void *))
{
	size_t	p;

	if (--nel)
	{
		p = partition(base, nel, width, compar);
		if (p == -1)
			return ;
		mqsort(base, p + 1, width, compar);
		mqsort((void *)((unsigned char *)base + (p + 1) * width),
			nel - p, width, compar);
	}
}
