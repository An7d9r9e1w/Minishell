#ifndef MAIN_H
#define MAIN_H
#include "../headers/parser_env.h"
int msh_unset(char **args, char **env);
int msh_env(char **args, char **env);
int msh_pwd(char **args);
int msh_echo(char **args);
int	msh_cd(char **args, char **env);
int msh_export(char **args, char **env);
int msh_exit(char **args);
int	ft_strcmp(const char *s1, const char *s2);
t_list *get_env(char **env);
#endif