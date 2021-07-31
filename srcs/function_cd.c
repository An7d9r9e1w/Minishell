#include "../headers/function_cd.h"
#include "../headers/parser_env.h"
static int update_oldpwd(t_list *list_env)
{
	char str[BUFSIZE];
	char *oldpwd;
	int i;

	if (!getcwd(str, BUFSIZE))
		return (0);
	oldpwd = ft_strjoin("OLDPWD=", str);
	if (!oldpwd)
		return (0);
	i = 0;
	while (env[i])
	{
		if (!ft_strncmp(env[i], "OLDPWD=", 7))
		{
//			free(env[i]);
			env[i] = NULL;
			env[i] = ft_strdup(oldpwd);
			if (!env[i])
			{
				free(oldpwd);
				oldpwd = NULL;
				return (0);
			}
		}
		i++;
	}
	free(oldpwd);
	oldpwd = NULL;
	return (1);
}

static char *get_path(t_list *list_env, const char *name, int len)
{
	char *path;
	int i;
	int j;

	while (*env)
	{
		if (!ft_strncmp(*env, name, len))
		{
			path = malloc(sizeof(char) * (ft_strlen(*env) - len + 1));
			if (!path)
				return (path);
			i = 0;
			j = 0;
			while ((*env)[i])
			{
				if (i >= len)
				{
					path[j] = (*env)[i];
					j++;
				}
				i++;
			}
			path[j] = 0;
			return (path);
		}
		env++;
	}
	return (NULL);
}

static void change_path(int n, t_list *list_env)
{
	char *need_path;

	need_path = NULL;
	if (n == 0)
	{
		need_path = get_path(env, "HOME=", 5);
		if (!need_path)
		{
			write(2, "msh: cd: HOME not set\n", 22);
			return ;
		}
		update_oldpwd(env);
	}
	else if (n == 1)
	{
		need_path = get_path(env, "OLDPWD=", 7);
		if (!need_path)
		{
			write(2, "msh: cd: OLDPWD not set\n", 24);
			return ;
		}
		update_oldpwd(env);
	}
	if (chdir(need_path) != 0)
	{
		write(2, strerror(errno), ft_strlen(strerror(errno)));
		write(2, "\n", 1);
	}
	free (need_path);
	need_path = NULL;
}

int	msh_cd(char **args, t_list *list_env)
{
	char *err;

	if (args[1] == NULL)
		change_path(0, env);
	else if (!ft_strcmp(args[1], "-"))
		change_path(1, env);
	else
	{
		update_oldpwd(env);
		if (chdir(args[1]) != 0)
		{
			err = strerror(errno);
			write(2, err, ft_strlen(err));
			write(2, "\n", 1);
		}
	}
	return (1);
}