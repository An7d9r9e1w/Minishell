/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nnamor <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/31 10:03:01 by nnamor            #+#    #+#             */
/*   Updated: 2021/08/14 14:58:42 by nnamor           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <signal.h>
#include <readline/readline.h>

#include <token_stream.h>
#include <cmd_assembler.h>
#include <command_list.h>
#include <error.h>
#include <parser.h>
#include <environment.h>
#include <executor.h>
#include <char_checkers.h>
#include <string_utils.h>

int		init_asmr_ts_envs(t_cmd_assembler **asmr, t_token_stream **ts,
			t_vvector **envs, char **envp);
void	msh_exit(char **args);
void	free_asmr_ts_envs(t_cmd_assembler *asmr, t_token_stream *ts,
			t_vvector *envs);

static void	fatal(t_cmd_assembler *asmr, t_token_stream *ts, t_vvector *envs)
{
	free_asmr_ts_envs(asmr, ts, envs);
	exit(error(0, 0, 1));
}

static t_command_list	*parser(t_cmd_assembler *asmr, t_token_stream *ts,
		t_vvector *envs)
{
	t_command_list	*command_list;
	char			*prompt;
	int				read_stat;

	command_list = 0;
	while (!command_list)
	{
		read_stat = ts_read(ts);
		while (!read_stat && is_empty(ts->line_read))
			read_stat = ts_read(ts);
		if (read_stat == -1)
		{
			prompt = ts->prompt;
			free_asmr_ts_envs(asmr, ts, envs);
			msh_exit(&prompt);
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
		if (executor(command_list, envs) == -1)
			fatal(asmr, ts, envs);
		command_list_free(command_list);
	}
	return (0);
}
