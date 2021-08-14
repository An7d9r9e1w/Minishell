/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ejina <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/04 11:58:08 by ejina             #+#    #+#             */
/*   Updated: 2021/08/14 14:56:45 by nnamor           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <error.h>
#include <string_utils.h>
#include <char_checkers.h>

char	*mstrjoin(char const *s1, char const *s2)
{
	char	*p;
	int		i;

	if (!s1 || !s2)
		return (0);
	p = (char *)malloc(mstrlen(s1) + mstrlen(s2) + 1);
	if (!p)
		return (error_p(-1));
	i = 0;
	while (*s1)
	{
		p[i] = *s1;
		i++;
		s1++;
	}
	while (*s2)
	{
		p[i] = *s2;
		i++;
		s2++;
	}
	p[i] = 0;
	return (p);
}

int	matoi(char *s1)
{
	int	num;
	int	sign;

	if (!s1)
		return (0);
	while (is_space(*s1))
		++s1;
	sign = 0;
	while (*s1 == '-' || *s1 == '+')
		sign ^= (*s1 == '-');
	num = 0;
	while (*s1 >= '0' && *s1 <= '9')
		num = num * 10 + *s1++ - '0';
	if (sign)
		num = -num;
	return (num);
}

char	*mitoa(int n)
{
	char			buf[16];
	char			*p;
	unsigned int	un;

	if (n < 0)
		un = -n;
	else
		un = n;
	p = buf + 15;
	*p-- = '\0';
	*p = '0';
	while (un)
	{
		*p-- = un % 10 + '0';
		un /= 10;
	}
	if (n < 0)
		*p-- = '-';
	return (mstrdup(p + (n != 0)));
}

int	is_empty(char *str)
{
	while (*str)
		if (!is_space(*str++))
			return (0);
	return (1);
}
