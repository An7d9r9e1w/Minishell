/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nnamor <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/08 13:59:48 by nnamor            #+#    #+#             */
/*   Updated: 2021/08/12 14:56:04 by nnamor           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdio.h>//TEST
#include <stdlib.h>
#include <sys/wait.h>
#include <signal.h>

#include <token_stream.h>
#include <executor.h>
#include <error.h>
#include <environment.h>

int		set_flows(int size, t_command *command, int *fildes);
void	try_exec(t_command *command, t_vvector *envs, int *fildes);
int		check_for_builtin(t_command *command, t_vvector *envs, int *fildes);

//TEST
/*void print_command_list(t_command_list *command_list)//TEST
{
	printf(" P  C\n");
	for (int i = 0; i < command_list->size; ++i)//TEST
	{
		t_pipe_line *pipe = command_list->pipes + i;
		for (int j = 0; j < pipe->size; ++j)
		{
			t_command *command = pipe->commands + j;
			printf("%2d %2d ", i, j);
			if (command->args)
				for (char **str = command->args; *str; ++str)
					printf("%s ", *str);//TEST
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
}*/
//TEST

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

	if (waitpid(pid, &stat_loc, 0) == -1)
		exit(error(-1, 0, 1));
	while (wait(NULL) != -1)
		;
	return (stat_loc);
}

int	only_builtin(t_command *command, t_vvector *envs, int *fildes, int *stat)
{
	*stat  = check_for_builtin(command, envs, fildes);
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
	while (size--)
	{
		set_flows(size, command, fildes);
		if (!size && only_builtin(command, envs, fildes, &stat))
			return (stat);
		if (!try_fork(pids))
			try_exec(command, envs, fildes);
		if (fildes[0] > 2)
			close(fildes[0]);
		if (fildes[2] > 2)
			close(fildes[2]);
		fildes[2] = fildes[1];
		--command;
	}
	return (recent_command_return(*pids));
}

int	executor(t_command_list *command_list, t_vvector *envs)
{
	//print_command_list(command_list);//TEST
	int	pipe_stat;
	int	i;

	signal(SIGINT, signal_handler_sub);
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
	return (pipe_stat);
}
