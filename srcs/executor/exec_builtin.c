/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_builtin.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nnamor <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/10 15:42:39 by nnamor            #+#    #+#             */
/*   Updated: 2021/08/12 08:15:48 by nnamor           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdio.h>//TEST
#include <stdlib.h>
#include <sys/wait.h>

#include <executor.h>
#include <error.h>
#include <string_utils.h>
#include <builtins.h>

int	set_flows(t_command *command, int *fildes, int *out);

static int	exec_builtin(char **args, t_vvector *envs)
{
	char	*cmd;

	cmd = *args;
	if (!mstrncmp(cmd, "echo", mstrlen("echo") + 1))
		return (msh_echo(args));
	else if (!mstrncmp(cmd, "cd", mstrlen("cd") + 1))
		return (msh_cd(args, envs));
	else if (!mstrncmp(cmd, "pwd", mstrlen("pwd") + 1))
		return (msh_pwd(args));
	else if (!mstrncmp(cmd, "export", mstrlen("export") + 1))
		return (msh_export(args, envs));
	else if (!mstrncmp(cmd, "unset", mstrlen("unset") + 1))
		return (msh_unset(args, envs));
	else if (!mstrncmp(cmd, "env", mstrlen("env") + 1))
		return (msh_env(args, envs));
	else if (!mstrncmp(cmd, "exit", mstrlen("exit") + 1))
		msh_exit(0);
	return (-1);
}

int	try_exec_builtin(t_command *command, t_vvector *envs, int *fildes, int out)
{
	int	stdflows[2];
	int	stat_loc;

	stdflows[0] = dup(STDIN_FILENO);
	stdflows[1] = dup(STDOUT_FILENO);
	if (stdflows[0] == -1 || stdflows[1] == -1
		|| set_flows(command, fildes, &out) == -1
		|| dup2(fildes[0], STDIN_FILENO) == -1
		|| dup2(out, STDOUT_FILENO) == -1)
		return (error(-1, 0, 0));
	stat_loc = exec_builtin(command->args, envs);
	close(fildes[0]);
	close(out);
	if (dup2(stdflows[0], STDIN_FILENO) == -1
		|| dup2(stdflows[1], STDOUT_FILENO) == -1)
		return (error(-1, 0, 0));
	return (-(stat_loc == -1));
}

int	check_for_builtin(t_command *command, t_vvector *envs,
		int *fildes, int out)
{
	char	*name;

	name = *command->args;
	if (!mstrncmp(name, "echo", mstrlen("echo") + 1)
		|| !mstrncmp(name, "cd", mstrlen("cd") + 1)
		|| !mstrncmp(name, "pwd", mstrlen("pwd") + 1)
		|| !mstrncmp(name, "export", mstrlen("export") + 1)
		|| !mstrncmp(name, "unset", mstrlen("unset") + 1)
		|| !mstrncmp(name, "env", mstrlen("env") + 1)
		|| !mstrncmp(name, "exit", mstrlen("exit") + 1))
		return (try_exec_builtin(command, envs, fildes, out));
	return (-2);
}
