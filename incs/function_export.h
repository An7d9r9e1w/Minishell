#ifndef FUNCTION_EXPORT_H
#define FUNCTION_EXPORT_H
#include <stdio.h>
#include <unistd.h>
#include "../incs/vvector.h"

int msh_env(char **args, t_vvector *env);
char	*mstrdup(const char *str);
int	mstrlen(const char *str);
int	ft_strncmp(const void *s1, const void *s2, int n);
#endif