/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nnamor <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/30 19:45:26 by nnamor            #+#    #+#             */
/*   Updated: 2021/08/11 13:04:06 by nnamor           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

#include <get_next_line.h>
#include <string_utils.h>
#include <error.h>

char	*cat(char *dst, const char *src, size_t len)
{
	char	*str;
	size_t	dstlen;
	size_t	i;

	if (!len && dst)
		return (dst);
	if (dst)
		dstlen = mstrlen(dst);
	else
		dstlen = 0;
	str = (char *)malloc(sizeof(char) * (dstlen + len + 1));
	if (str)
	{
		i = -1;
		while (++i < dstlen)
			str[i] = dst[i];
		dstlen = 0;
		while (dstlen < len)
			str[i++] = src[dstlen++];
		str[i] = 0;
	}
	if (dst)
		free(dst);
	return (str);
}

int	init_buf(char **buf, size_t *len)
{
	*buf = (char *)malloc(sizeof(char) * BUFFER_SIZE);
	if (!*buf)
		return (error(-1, 0, 0));
	*len = 0;
	return (0);
}

void	free_buf(char **buf)
{
	free(*buf);
	*buf = 0;
}
