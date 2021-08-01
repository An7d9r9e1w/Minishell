#ifndef FUNCTION_CD_H
#define FUNCTION_CD_H
#include <unistd.h>
#include <string.h>
#include <errno.h>
#include <stdlib.h>
#define BUFSIZE 100
int ft_strlen(const char *str);
int	ft_strcmp(const char *s1, const char *s2);
int	ft_strncmp(const char *s1, const char *s2, int n);
char	*ft_strjoin(char const *s1, char const *s2);
char	*ft_strdup(const char *s1);
int msh_env(char **args, char **env);
#endif