#ifndef MAIN_H
#define MAIN_H
#include "../incs/vvector.h"
int msh_unset(char **args, t_vvector *env);
int msh_env(char **args, t_vvector *env);
int msh_pwd(char **args);
int msh_echo(char **args);
int	msh_cd(char **args, t_vvector *env);
int msh_export(char **args, t_vvector *env);
int msh_exit(char **args);
int	ft_strcmp(const void *s1, const void *s2);
int ft_strlen(const char *str);

t_vvector *get_env(char **env);
#endif