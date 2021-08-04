/*<<<<<<< HEAD
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
=======*/
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nnamor <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/31 10:03:01 by nnamor            #+#    #+#             */
/*   Updated: 2021/08/03 18:31:50 by nnamor           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <sys/errno.h>//TEST
#include <string.h>
#include <unistd.h>

#include <token_stream.h>
#include <string_utils.h>//TEST
#include <cmd_assembler.h>
#include <command_list.h>
#include <error.h>
#include <parser.h>

void	paused(void)//TEST
{
	char	c[2];

	printf("Press enter...");
	fgets(c, 2, stdin);
}
/*
void	token_print(t_token *token)//TEST
{
	static const char *kinds[] = {"ERROR", "WORD", "GREAT", "DGREAT", "LESS",
		"DLESS", "QUOTE", "DQUOTE", "PIPE", "ENV", "AND", "OR", "WILDCARD", 0};

	printf("%s\t\t%s\n", kinds[token->kind], token->value);
}
*/
/*__attribute__((noreturn))
static void fatal(t_cmd_assembler *asmr, t_token_stream *ts)
{
	//char	*msg;

	printf("FATAL\n");//TEST
	//msg = strerror(errno);
	//write(2, msg, mstrlen(msg));
	cmd_assembler_free(asmr);
	ts_free(ts);
	exit(errno);
}*/

static int	init_asmr_ts(t_cmd_assembler **asmr, t_token_stream **ts)
{
	*ts = ts_create("msh-1.0$ ");
	if (!*ts)
		return (error(-1, 0, 0));
	*asmr = cmd_assembler_create();
	if (!*asmr)
	{
		ts_free(*ts);
		return (error(-1, 0, 0));
	}
	return (0);
}

static t_command_list	*parser(t_cmd_assembler *asmr, t_token_stream *ts)
{
	if (ts_read(ts) == -1)
	{
		printf("\e[D\e[DUSER EXIT\n");//TEST
		ts_free(ts);//TEST
		cmd_assembler_free(asmr);//TEST
		paused();//TEST
		exit(0);//TEST
	}
	if (!*ts->line_read)
	{
		printf("EMPTY LINE\n");//TEST
		ts_free(ts);//TEST
		cmd_assembler_free(asmr);//TEST
		paused();//TEST
		exit(0);//TEST
	}
	return (parse_line_read(asmr, ts));
}

void print_command_list(t_command_list *command_list)
{
	for (int i = 0; i < command_list->size; ++i)//TEST
	{
		t_pipe_line *pipe = command_list->pipes + i;
		for (int j = 0; j < pipe->size; ++j)
		{
			t_command *command = pipe->commands + j;
			printf("%d %d ", i, j);
			if (command->args)
				for (char **str = command->args; *str; ++str)
					printf("%s ", *str);//TEST*/
			printf("\n");
			t_file *file;
			if ((file = command->in))
			{
				printf("\tin: ");
				for (int k = 0; k < command->in_size; ++k, ++file)
					printf("%s,%d ", file->path, file->mode);
				printf("\n");
			}
			if ((file = command->out))
			{
				printf("\tout: ");
				for (int k = 0; k < command->out_size; ++k, ++file)
					printf("%s,%d ", file->path, file->mode);
				printf("\n");
			}
		}
		printf("logic=%d\n", pipe->logic_operator);
	}
}

int	main(void)//int argc, char *argv[], char *envp[])
{
	t_cmd_assembler	*asmr;
	t_token_stream	*ts;
	t_command_list	*command_list;

	if (init_asmr_ts(&asmr, &ts) == -1)
		return (error(0, 0, 1));

	command_list = parser(asmr, ts);
	if (!command_list)
		error(0, 0, 1);
		//fatal(asmr, ts);
	else
		print_command_list(command_list);
/*
	printf("pipes\n");//TEST
	for (unsigned int i = 0; i < asmr->pipes->size; ++i)
		printf("%p\n", asmr->pipes->arr[i]);
	printf("commands\n");//TEST
	for (unsigned int i = 0; i < asmr->commands->size; ++i)
		printf("%p\n", asmr->commands->arr[i]);
	printf("args\n");//TEST
	for (unsigned int i = 0; i < asmr->args->size; ++i)
		printf("%p\n", asmr->args->arr[i]);
	printf("in\n");//TEST
	for (unsigned int i = 0; i < asmr->in->size; ++i)
		printf("%p\n", asmr->in->arr[i]);
	printf("out\n");//TEST
	for (unsigned int i = 0; i < asmr->out->size; ++i)
		printf("%p\n", asmr->out->arr[i]);
*/
	ts_free(ts);//TEST
	cmd_assembler_free(asmr);//TEST
	command_list_free(command_list);//TEST*/
	paused();//TEST
	return (0);
}
>>>>>>> error_handing
