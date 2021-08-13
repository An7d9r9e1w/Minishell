/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nnamor <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/08 13:59:48 by nnamor            #+#    #+#             */
/*   Updated: 2021/08/13 10:45:16 by nnamor           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <signal.h>

#include <readline/readline.h>
#include <signal_handlers.h>
#include <executor.h>
#include <error.h>
#include <environment.h>

int		set_flows(int size, t_command *command, int *fildes);
void	try_exec(t_command *command, t_vvector *envs, int *fildes);
int		check_for_builtin(t_command *command, t_vvector *envs, int *fildes);
void	close_fildes(int fd1, int fd2, int fd3);

pid_t	try_fork(pid_t *pids)
{
	const int	i = (*pids != 0);

	pids[i] = fork();
	if (pids[i] == -1)
		exit(error(-1, 0, 1));
	return (pids[i]);
}

int	recent_command_return(pid_t pid)
{
	int	stat_loc;

	if (!pid)
		return (1);
	if (waitpid(pid, &stat_loc, 0) == -1)
		exit(error(-1, 0, 1));
	while (wait(NULL) != -1)
		;
	return (stat_loc);
}

int	only_builtin(t_command *command, t_vvector *envs, int *fildes, int *stat)
{
	*stat = check_for_builtin(command, envs, fildes);
	return (*stat > -2);
}

int	exec_pipe(int size, t_command *command, t_vvector *envs)
{
	pid_t	pids[2];
	int		fildes[3];
	int		stat;

	command += size - 1;
	fildes[2] = STDOUT_FILENO;
	pids[0] = 0;
	pids[1] = 0;
	stat = size - 1;
	while (size--)
	{
		if (set_flows(size, command, fildes) != -1 && command->args)
		{
			if (!stat && only_builtin(command, envs, fildes, &stat))
				return (stat);
			if (!try_fork(pids))
				try_exec(command, envs, fildes);
		}
		close_fildes(fildes[0], 0, fildes[2]);
		fildes[2] = fildes[1];
		--command;
	}
	close_fildes(0, 0, fildes[2]);
	return (recent_command_return(*pids));
}

int	executor(t_command_list *command_list, t_vvector *envs)
{
	int	pipe_stat;
	int	i;

	signal(SIGINT, signal_handler_sub);
	signal(SIGQUIT, signal_quit);
	i = -1;
	while (++i < command_list->size)
	{
		pipe_stat = exec_pipe(command_list->pipes[i].size,
				command_list->pipes[i].commands, envs);
		if (pipe_stat == -1)
			break ;
		pipe_stat = !!pipe_stat;
		last_return(pipe_stat, 0);
		while (i < command_list->size
			&& pipe_stat != command_list->pipes[i].logic_operator)
			++i;
	}
	signal(SIGINT, signal_handler);
	signal(SIGQUIT, signal_handler);
	rl_replace_line("", 0);
	rl_redisplay();
	return (pipe_stat);
}
