//#include <main.h>
//#include <stdio.h>
//#include <string.h>
//#include <stdlib.h>
//#include <string_utils.h>
//#include <vvector.h>
//int	msh_cd(char **args, t_vvector *my_env);
//int msh_echo(char **args);
//int msh_env(char **args, t_vvector *env);
//int msh_export(char **args, t_vvector *env);
//int msh_pwd(char **args);
//int msh_unset(char **args, t_vvector *env);
//t_vvector	*get_environments(char **env);
//
//char	*ft_substr(char const *s, unsigned int start, size_t len)
//{
//	char	*p;
//	size_t	i;
//	size_t	l;
//
//	if (!s)
//		return (0);
//	l = mstrlen(s);
//	if (len > l)
//		len = l;
//	if (l <= start)
//	{
//		p = (char *)malloc(1);
//		p[0] = 0;
//		return (p);
//	}
//	p = (char *)malloc(len + 1);
//	if (!p)
//		return (p);
//	i = -1;
//	while (++i < len)
//		p[i] = s[start + i];
//	p[i] = 0;
//	return (p);
//}
//static int	count_word(char const *s, char c)
//{
//	int	flag;
//	int	count;
//
//	flag = 0;
//	if (*s != c)
//		count = 1;
//	else
//		count = 0;
//	while (*s)
//	{
//		while (*s == c && *s)
//		{
//			flag = 1;
//			s++;
//		}
//		if (flag && *s)
//		{
//			flag = 0;
//			count++;
//		}
//		if (!(*s))
//			break ;
//		s++;
//	}
//	return (count);
//}
//
//static int	len_word(char const *s, char c)
//{
//	int	i;
//
//	i = 0;
//	while (*s == c && *s)
//		s++;
//	while (*s != c && *s)
//	{
//		i++;
//		s++;
//	}
//	return (i);
//}
//
//static int	freem(char **p, int i)
//{
//	int	j;
//
//	j = 0;
//	while (j < i)
//	{
//		free(p[j]);
//		j++;
//	}
//	free(p);
//	return (1);
//}
//
//static const char	*skip(char const *s, char c)
//{
//	while (*s == c && *s)
//		s++;
//	return (s);
//}
//
//char	**ft_split(char const *s, char c)
//{
//	char	**p;
//	int		i;
//	int		l;
//
//	if (!s)
//		return (0);
//	p = (char **)malloc(sizeof(char *) * (count_word(s, c) + 1));
//	if (!p)
//		return (p);
//	i = 0;
//	s = skip(s, c);
//	while (*s)
//	{
//		l = len_word(s, c);
//		p[i] = ft_substr(s, 0, l);
//		if (!p[i] && freem(p, i))
//			return (p);
//		s += l;
//		i++;
//		s = skip(s, c);
//	}
//	p[i] = 0;
//	return (p);
//}
//
//int msh_exit(char **args)
//{
//	(void)args;
//	return (0);
//}
//
//int main(int argc, char **argv, char **env)
//{
//	char str[100];
//	char **arg;
//	(void)argc;
//	(void)argv;
//	t_vvector *my_env;
//	my_env = get_environments(env);
//
//	while (1)
//	{
//		gets (str);
//		arg = ft_split(str, ' ');
//		if (!mstrcmp(arg[0], "cd"))
//		{
//			if (!msh_cd(arg, my_env))
//				return (1);
//		}
//		else if (!mstrcmp(arg[0], "echo"))
//		{
//			if (!msh_echo(arg))
//				return (1);
//		}
//		else if (!mstrcmp(arg[0], "env"))
//		{
//			if (!msh_env(arg, my_env))
//				return (1);
//		}
//		else if (!mstrcmp(arg[0], "export"))
//		{
//			if (!msh_export(arg, my_env))
//				return (1);
//		}
//		else if (!mstrcmp(arg[0], "pwd"))
//		{
//			if (!msh_pwd(arg))
//				return (1);
//		}
//		else if (!mstrcmp(arg[0], "unset"))
//		{
//			if (!msh_unset(arg, my_env))
//				return (1);
//		}
//		else if (!mstrcmp(arg[0], "exit"))
//		{
//			if (!msh_exit(arg))
//				return (1);
//		}
//		else
//			printf("Write right command\n");
//	}
//	return 0;
//}
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
//#include <sys/errno.h>//TEST
#include <string.h>
#include <unistd.h>
#include <signal.h>

#include <token_stream.h>
#include <string_utils.h>//TEST
#include <cmd_assembler.h>
#include <command_list.h>
#include <error.h>
#include <parser.h>
#include <environment.h>
#include <executor.h>

void	paused(void)//TEST
{
	char	c[2];

	printf("Press enter...");
	fgets(c, 2, stdin);
}

static int	set_shell_level(t_vvector *envs)
{
	char	buf[24];
	char	*p;
	char	*level_str;
	int		index;
	int		level;

	index = get_environment_index(envs, "SHLVL");
	if (index == -1)
		return (vvector_put(envs, mstrdup("SHLVL=1")));
	level = matoi(get_environment_value(envs, "SHLVL")) + 1;
	level_str = mitoa(level);
	if (!level_str)
		return (-1);
	free(envs->arr[index]);
	p = buf + mstrlcpy(buf, "SHLVL=", 6);
	mstrlcpy(p, level_str, mstrlen(level_str));
	free(level_str);
	p = mstrdup(buf);
	if (!p)
		return (-1);
	envs->arr[index] = p;
	return (0);
}

static int	init_asmr_ts_envs(t_cmd_assembler **asmr, t_token_stream **ts,
		t_vvector **envs, char **envp)
{
	signal(SIGINT, signal_handler);
	*ts = ts_create("msh-1.0$ ");
	if (!*ts)
		return (error(-1, 0, 0));
	*envs = get_environments(envp);
	if (!*envs || set_shell_level(*envs) == -1)
	{
		ts_free(*ts);
		return (error(-1, 0, 0));
	}
	*asmr = cmd_assembler_create();
	if (!*asmr)
	{
		ts_free(*ts);
		vvector_free(*envs);
		return (error(-1, 0, 0));
	}
	return (0);
}

void	msh_exit(void)
{
	if (error(-2, 0, 0) == -1)
		exit(error(0, 0, 1));
	else
		printf("exit\n");
	exit(0);
}

static void	free_asmr_ts_envs(t_cmd_assembler *asmr, t_token_stream *ts,
		t_vvector *envs)
{
	ts_free(ts);
	vvector_free(envs);
	cmd_assembler_free(asmr);
}

static void	fatal(t_cmd_assembler *asmr, t_token_stream *ts,
		t_vvector *envs)
{
	free_asmr_ts_envs(asmr, ts, envs);
	exit(error(0, 0, 1));
}

static t_command_list	*parser(t_cmd_assembler *asmr, t_token_stream *ts,
		t_vvector *envs)
{
	t_command_list	*command_list;
	int				read_stat;

	command_list = 0;
	while (!command_list)
	{
		read_stat = ts_read(ts);
		while (!read_stat && !*ts->line_read)
			read_stat = ts_read(ts);
		if (read_stat == -1)
		{
			free_asmr_ts_envs(asmr, ts, envs);
			msh_exit();
		}
		command_list = parse_line_read(asmr, ts, envs);
		if (!command_list)
		{
			if (error(-2, 0, 0) == -1)
				fatal(asmr, ts, envs);
			error(0, 0, 1);
		}
	}
	return (command_list);
}

int	main(int argc, char *argv[], char *envp[])
{
	t_cmd_assembler	*asmr;
	t_token_stream	*ts;
	t_command_list	*command_list;
	t_vvector		*envs;

	(void)argc;
	(void)argv;
	if (init_asmr_ts_envs(&asmr, &ts, &envs, envp) == -1)
		return (error(0, 0, 1));
	while (1)
	{
		command_list = parser(asmr, ts, envs);
		//print_command_list(command_list);//TEST
		executor(command_list, envs);
		command_list_free(command_list);
	}
	return (0);
}
