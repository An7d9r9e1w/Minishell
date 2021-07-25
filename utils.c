#include "utils.h"

int	ft_strcmp(const char *s1, const char *s2)
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