#ifndef FUNCTION_ENV_H
#define FUNCTION_ENV_H
#include <stdio.h>
void	mqsort(void *base, size_t nel, size_t width,
			   int (*compar)(const void *, const void *));
int	ft_strcmp(const void *s1, const void *s2);
#endif