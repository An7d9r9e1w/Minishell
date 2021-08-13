/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nnamor <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/12 15:15:16 by nnamor            #+#    #+#             */
/*   Updated: 2021/08/13 08:27:29 by nnamor           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <signal.h>
#include <readline/readline.h>

#include <token_stream.h>
#include <string_utils.h>
#include <cmd_assembler.h>
#include <command_list.h>
#include <error.h>
#include <parser.h>
#include <environment.h>
#include <executor.h>
#include <signal_handlers.h>

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

int	init_asmr_ts_envs(t_cmd_assembler **asmr, t_token_stream **ts,
		t_vvector **envs, char **envp)
{
	signal(SIGINT, signal_handler);
	signal(SIGQUIT, signal_handler);
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

void	msh_exit(char **args)
{
	extern int	rl_end;
	int			i;

	if (error(-2, 0, 0) == -1)
		exit(error(0, 0, 1));
	else if (args)
	{
		i = mstrlen(*args) + rl_end;
		printf("\e[A");
		while (i--)
			printf("\e[C");
		printf("exit\n");
	}
	exit(0);
}

void	free_asmr_ts_envs(t_cmd_assembler *asmr, t_token_stream *ts,
		t_vvector *envs)
{
	ts_free(ts);
	vvector_free(envs);
	cmd_assembler_free(asmr);
}
