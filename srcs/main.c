<<<<<<< HEAD
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
=======
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nnamor <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/31 10:03:01 by nnamor            #+#    #+#             */
/*   Updated: 2021/07/31 16:17:59 by nnamor           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <sys/errno.h>//TEST

#include <token_stream.h>
#include <string_utils.h>//TEST
#include <error.h>

void	paused(void)//TEST
{
	char	c[2];

	printf("Press enter...");
	fgets(c, 2, stdin);
}

void	token_print(t_token *token)//TEST
{
	static const char *kinds[] = {"ERROR", "WORD", "QUOTE", "DQUOTE", "GREAT", "DGREAT",
		"LESS", "DLESS", "PIPE", "ENV", "AND", "OR", "WILDCARD", 0};
	static const char *values[] = {"ERROR", 0, "'", "\"", ">", ">>",
		"<", "<<", "|", "$", "&&", "||", "*", 0};

	printf("%s\t\t%s\n", kinds[token->kind],
		(token->kind == WORD) ? token->value : values[token->kind]);
}

int	test_parser(t_token_stream *ts) //TEST
{
	t_token	*token;
	//int		token_stat;

	if (ts_read(ts) == -1) //TEST
		return (0);
	token = ts_get_token(ts);
	while (token)
	{
		token_print(token);
		token_free(token);
		token = ts_get_token(ts);
	}
	ts_free(ts);//TEST
	return (error(-2));
}

int	main(int argc, char *argv[], char *envp[])
{
	t_token_stream	*ts;
//	t_token	*tokens[256];
	(void)argc;
	(void)argv;
	(void)envp;

	ts = ts_create("msh-1.0$ ");
	if (!ts)
	{
		perror("Token_stream:");//TEST
		return (1);
	}
	//while (1)
	//{
		if (test_parser(ts))//TEST
			error_msg(); //TEST
	//}
	paused();
	return (0);
}
>>>>>>> error_handing
