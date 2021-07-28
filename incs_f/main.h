#ifndef MAIN_H
#define MAIN_H
int msh_unset(char **args, char **env);
int msh_env(char **args, char **env);
int msh_pwd(char **args);
int msh_echo(char **args);
int	msh_cd(char **args);
int msh_export(char **args, char **env);
int msh_exit(char **args);
#endif