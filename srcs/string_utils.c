/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   string_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nnamor <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/31 10:03:14 by nnamor            #+#    #+#             */
/*   Updated: 2021/08/01 07:03:48 by nnamor           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

#include <string_utils.h>
#include <error.h>

int	mstrlen(const char *str)
{
	const char *const	begin = str;

	if (str)
		while (*str)
			str++;
	return (str - begin);
}

char	*mstrdup(const char *str)
{
	char	*dup;
	char	*p;

	dup = malloc(mstrlen(str) + 1);
	if (!dup)
		return (error_p(-1));
	p = dup;
	if (str)
		while (*str)
			*p++ = *str++;
	*p = 0;
	return (dup);
}

int		mstrlcpy(char *dst, const char *src, int dstsize)
{
	int	srcsize;

	if (!dst || !src)
		return (0);
	srcsize = mstrlen(src);
	if (dstsize > 0)
	{
		if (dstsize > srcsize + 1)
			dstsize = srcsize + 1;
		while (dstsize--)
			*dst++ = *src++;
		*dst = 0;
	}
	return (srcsize);
}

void	drop_blanks(char **str)
{
	char	*cur;

	if (str && *str)
	{
		cur = *str;
		while (*cur == ' ' || (*cur >= '\t' && *cur <= '\r'))
			cur++;
		*str = cur;
	}
}

char	*mstrcat(char *dst, const char *src, unsigned int srclen)
{
	char			*str;
	char			*str_cur;
	unsigned int	dstlen;

	if ((!src || !srclen) && dst)
		return (dst);
	if (dst)
		dstlen = mstrlen(dst);
	else
		dstlen = 0;
	str = malloc(sizeof(char) * (dstlen + srclen + 1));
	if (!str)
		return (error_p(-1));
	str_cur = str;
	if (dst)
		while (*dst)
			*str_cur++ = *dst++;
	dst -= str_cur - str;
	while (*src)
		*str_cur++ = *src++;
	*str_cur = 0;
	if (dst)
		free(dst);
	return (str);
}
