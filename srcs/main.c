#include "../headers/main.h"
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
int ft_strlen(const char *str);
char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*p;
	size_t	i;
	size_t	l;

	if (!s)
		return (0);
	l = ft_strlen(s);
	if (len > l)
		len = l;
	if (l <= start)
	{
		p = (char *)malloc(1);
		p[0] = 0;
		return (p);
	}
	p = (char *)malloc(len + 1);
	if (!p)
		return (p);
	i = -1;
	while (++i < len)
		p[i] = s[start + i];
	p[i] = 0;
	return (p);
}
static int	count_word(char const *s, char c)
{
	int	flag;
	int	count;

	flag = 0;
	if (*s != c)
		count = 1;
	else
		count = 0;
	while (*s)
	{
		while (*s == c && *s)
		{
			flag = 1;
			s++;
		}
		if (flag && *s)
		{
			flag = 0;
			count++;
		}
		if (!(*s))
			break ;
		s++;
	}
	return (count);
}

static int	len_word(char const *s, char c)
{
	int	i;

	i = 0;
	while (*s == c && *s)
		s++;
	while (*s != c && *s)
	{
		i++;
		s++;
	}
	return (i);
}

static int	freem(char **p, int i)
{
	int	j;

	j = 0;
	while (j < i)
	{
		free(p[j]);
		j++;
	}
	free(p);
	return (1);
}

static const char	*skip(char const *s, char c)
{
	while (*s == c && *s)
		s++;
	return (s);
}

char	**ft_split(char const *s, char c)
{
	char	**p;
	int		i;
	int		l;

	if (!s)
		return (0);
	p = (char **)malloc(sizeof(char *) * (count_word(s, c) + 1));
	if (!p)
		return (p);
	i = 0;
	s = skip(s, c);
	while (*s)
	{
		l = len_word(s, c);
		p[i] = ft_substr(s, 0, l);
		if (!p[i] && freem(p, i))
			return (p);
		s += l;
		i++;
		s = skip(s, c);
	}
	p[i] = 0;
	return (p);
}

int msh_exit(char **args)
{
	(void)args;
	return (0);
}

//// Для cd сделать переключение на HOME,чтобы в env менялись значения
int main(int argc, char **argv, char **env)
{
	t_list *list_env;
	char str[100];
	list_env = get_env(env);
	char **arg;
	(void)argc;
	(void)argv;
	while (1)
	{
		gets (str);
		arg = ft_split(str, ' ');
		if (!ft_strcmp(arg[0], "cd"))
		{
			if (!msh_cd(arg, list_env))
				return (1);
		}
		else if (!ft_strcmp(arg[0], "echo"))
		{
			if (!msh_echo(arg))
				return (1);
		}
		else if (!ft_strcmp(arg[0], "env"))
		{
			if (!msh_env(arg, env))
				return (1);
		}
		else if (!ft_strcmp(arg[0], "export"))
		{
			if (!msh_export(arg, env))
				return (1);
		}
		else if (!ft_strcmp(arg[0], "pwd"))
		{
			if (!msh_pwd(arg))
				return (1);
		}
		else if (!ft_strcmp(arg[0], "unset"))
		{
			if (!msh_unset(arg, env))
				return (1);
		}
		else if (!ft_strcmp(arg[0], "exit"))
		{
			if (!msh_exit(arg))
				return (1);
		}
		else
			printf("Write right command\n");
	}
	return 0;
}