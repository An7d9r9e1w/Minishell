/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nnamor <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/31 10:03:01 by nnamor            #+#    #+#             */
/*   Updated: 2021/08/11 16:25:54 by nnamor           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
//#include <sys/errno.h>//TEST
#include <string.h>
#include <unistd.h>
#include <signal.h>
#include <readline/readline.h>

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
	char	*level;
	int		env_stat;

	if (get_environment_index(envs, "SHLVL") == -1)
		return (vvector_put(envs, mstrdup("SHLVL=1")));
	level = mitoa(matoi(get_environment_value(envs, "SHLVL")) + 1);
	env_stat = set_environment(envs, "SHLVL", level);
	free(level);
	return (env_stat);
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

/*__attribute__ ((noreturn))*/
void	msh_exit(char **args)
{
	//int	i;

	if (error(-2, 0, 0) == -1)
		exit(error(0, 0, 1));
	else if (args)
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
			msh_exit((void *)1);
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
		executor(command_list, envs);
		command_list_free(command_list);
	}
	return (0);
}
