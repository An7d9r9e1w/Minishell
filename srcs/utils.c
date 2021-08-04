/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ejina <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/04 11:58:08 by ejina             #+#    #+#             */
/*   Updated: 2021/08/04 11:58:27 by nnamor           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

int	ft_strcmp(const void *s1, const void *s2)
{
	unsigned char	*s;
	unsigned char	*r;

	s = (unsigned char *)s1;
	r = (unsigned char *)s2;
	while (*s || *r)
	{
		if (*s != *r)
			return (*s - *r);
		s++;
		r++;
	}
	return (0);
}

int ft_strlen(const char *str)
{
	int i;

	i = 0;
	while(str[i])
		i++;
	return (i);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*p;
	int		i;

	if (!s1 || !s2)
		return (0);
	p = (char *)malloc(ft_strlen(s1) + ft_strlen(s2) + 1);
	if (!p)
		return (p);
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

int	ft_strncmp(const void *s1, const void *s2, int n)
{
	int				i;
	unsigned char	*s;
	unsigned char	*r;

	i = 0;
	s = (unsigned char *)s1;
	r = (unsigned char *)s2;
	while ((*s || *r) && i < n)
	{
		if (*s != *r)
			return (*s - *r);
		s++;
		r++;
		i++;
	}
	return (0);
}

char	*ft_strdup(const char *s1)
{
	char	*p;
	int		i;

	p = (char *)malloc(sizeof(char) * (ft_strlen(s1) + 1));
	if (!p)
		return (p);
	i = 0;
	while (s1[i])
	{
		p[i] = s1[i];
		i++;
	}
	p[i] = 0;
	return (p);
}
