/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcard.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nnamor <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/13 16:59:21 by nnamor            #+#    #+#             */
/*   Updated: 2021/08/14 08:11:03 by nnamor           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <wildcard.h>

static int	matchstar(char *pattern, char *str)
{
	while (1)
	{
		if (match(pattern, str))
			return (1);
		if (!*str++)
			break ;
	}
	return (0);
}

int	match(char *pattern, char *str)
{
	while (1)
	{
		if (!*pattern)
			return (1);
		if (*pattern == '*')
			return (matchstar(pattern + 1, str));
		if (*pattern++ != *str++)
			break ;
	}
	return (0);
}
