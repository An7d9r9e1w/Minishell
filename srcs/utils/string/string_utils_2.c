/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   string_utils_2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nnamor <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/31 10:03:20 by nnamor            #+#    #+#             */
/*   Updated: 2021/08/04 14:45:02 by nnamor           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

#include <string_utils.h>
#include <error.h>

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
		return (error_p(-1));
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

int	mstrcmp(const char *s1, const char *s2)
{
	if (!s1 || !s2)
		return ((int)(s1 - s2));
	while (*s1 && *s1 == *s2)
	{
		s1++;
		s2++;
	}
	return (*s1 - *s2);
}

int	mstrcmpv(const void *v1, const void *v2)
{
	return (mstrcmp(*(const char **)v1, *(const char **)v2));
}

int	mstrncmp(const char *s1, const char *s2, unsigned int n)
{
	if (!s1 || !s2)
		return ((int)(s1 - s2));
	while (--n && *s1 && *s1 == *s2)
	{
		s1++;
		s2++;
	}
	return (*s1 - *s2);
}

int	envcmpv(const void *s1, const void *s2)
{
	const char	*str1 = *(const char **)s1;
	const char	*str2 = s2;

	if (!str1 || !str2)
		return ((int)(str1 - str2));
	while (*str1 && *str1 != '=' && *str1 == *str2)
	{
		str1++;
		str2++;
	}
	return (*str1 - *str2);
}
