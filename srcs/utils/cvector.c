/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cvector.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nnamor <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/31 10:02:54 by nnamor            #+#    #+#             */
/*   Updated: 2021/08/10 08:48:25 by nnamor           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

#include <cvector.h>
#include <error.h>

static int	cvector_realloc(t_cvector *cv, unsigned int new_size)
{
	char			*arr;
	char			*arr_cur;
	char			*cv_cur;
	unsigned int	count;

	arr = malloc(sizeof(char) * new_size);
	if (!arr)
		return (error(-1, 0, 0));
	if (new_size < cv->size)
		cv->size = new_size;
	count = cv->size;
	arr_cur = arr;
	cv_cur = cv->arr;
	while (count--)
		*arr_cur++ = *cv_cur++;
	free(cv->arr);
	cv->arr = arr;
	cv->capacity = new_size;
	return (0);
}

t_cvector	*cvector_create(void)
{
	t_cvector	*cv;

	cv = malloc(sizeof(t_cvector));
	if (!cv)
		return (error_p(-1));
	cv->capacity = 1024;
	cv->size = 0;
	cv->arr = malloc(sizeof(char) * cv->capacity);
	*cv->arr = 0;
	if (cv->arr)
		return (cv);
	free(cv);
	error(-1, 0, 0);
	return (0);
}

void	cvector_free(t_cvector *cv)
{
	if (cv)
	{
		if (cv->arr)
			free(cv->arr);
		free(cv);
	}
}

int	cvector_write(t_cvector *cv, char *str, unsigned int length)
{
	char			*cv_cur;
	unsigned int	capacity;

	capacity = cv->capacity;
	while (cv->size + 1 + length > capacity)
		capacity <<= 1;
	if (capacity > cv->capacity && cvector_realloc(cv, capacity) == -1)
		return (-1);
	cv_cur = cv->arr + cv->size;
	while (length--)
		*cv_cur++ = *str++;
	*cv_cur = 0;
	cv->size += cv_cur - (cv->arr + cv->size);
	return (0);
}
