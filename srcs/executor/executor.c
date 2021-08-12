/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nnamor <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/08 13:59:48 by nnamor            #+#    #+#             */
/*   Updated: 2021/08/12 10:25:07 by nnamor           ###   ########.fr       */
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

int		set_flows(t_command *command, int *fildes, int *out);
void	try_exec(t_command *command, t_vvector *envs, int *fildes, int out);
int		check_for_builtin(t_command *command, t_vvector *envs,
		int *fildes, int out);
int		try_exec_builtin(t_command *command, t_vvector *envs,
		int *fildes, int out);

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

/*__attribute__ ((noreturn))*/
void	exec_command(int size, t_command *command, t_vvector *envs)
{
	pid_t	pid;
	int		fildes[2];
	int		out;

	out = STDOUT_FILENO;
	while (size--)
	{
		if (pipe(fildes) == -1)
			exit(error(-1, 0, 1));
		set_flows(command, fildes, &out);
		pid = fork();
		if (pid == -1)
			exit(error(-1, 0, 1));
		if (pid)
			try_exec(command, envs, fildes, out);
		close(fildes[0]);
		if (out > 2)
			close(out);
		out = fildes[1];
		--command;
	}
	fildes[0] = STDIN_FILENO;
	fildes[1] = STDOUT_FILENO;
	set_flows(command, fildes, &out);
	try_exec(command, envs, fildes, out);
}

int	exec_pipe(t_pipe_line *pipe, t_vvector *envs)
{
	pid_t	pid;
	int		stat_loc;
	int		fildes[2];

	if (pipe->size == 1)
	{
		fildes[0] = STDIN_FILENO;
		fildes[1] = STDOUT_FILENO;
		stat_loc = check_for_builtin(pipe->commands, envs,
			fildes, STDOUT_FILENO);
		if (stat_loc > -2)
			return (stat_loc);
	}
	pid = fork();
	if (pid == -1)
		return (error(-1, 0, 0));
	if (!pid)
		exec_command(pipe->size - 1, pipe->commands + pipe->size - 1, envs);
	if (waitpid(pid, &stat_loc, 0) == -1)
		return (error(-1, 0, 0));
	return (stat_loc);
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
		pipe_stat = exec_pipe(command_list->pipes + i, envs);
		if (pipe_stat == -1)
			break ;
		pipe_stat = !!pipe_stat;
		while (i < command_list->size
			&& pipe_stat != command_list->pipes[i].logic_operator)
			++i;
	}
	last_return(pipe_stat, 0);
	signal(SIGINT, signal_handler);
	return (pipe_stat);
}
