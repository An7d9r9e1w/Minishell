/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   try_execute.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nnamor <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/10 11:56:46 by nnamor            #+#    #+#             */
/*   Updated: 2021/08/10 13:10:26 by nnamor           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdio.h>//TEST
#include <stdlib.h>
#include <sys/wait.h>
#include <fcntl.h>

#include <executor.h>
#include <cvector.h>
#include <error.h>
#include <string_utils.h>
#include <environment.h>

int	set_flows(t_command *command, int *fildes, int *out);

static int	get_next_path(t_cvector *cv, char *name, char **path_env)
{
	char	*path_cur;

	path_cur = *path_env;
	cv->size = 0;
	while (*path_cur && *path_cur != ':')
		if (cvector_write(cv, path_cur++, 1) == -1)
			break ;
	if (error(-2, 0, 0) == -1 || cvector_write(cv, "/", 1) == -1
		|| cvector_write(cv, name, mstrlen(name)) == -1)
	{
		cvector_free(cv);
		return (0);
	}
	if (!(path_cur - *path_env))
		return (0);
	*path_env = path_cur + (*path_cur == ':');
	return (1);
}

static int	try_open(char *path)
{
	int	fd;

	fd = open(path, O_RDONLY);
	if (fd == -1)
		return (0);
	close(fd);
	return (1);
}

static int	search_path(t_command *command, t_vvector *envs)
{
	t_cvector	*cv;
	char		*path_env;

	path_env = get_environment_value(envs, "PATH");
	if (path_env)
	{
		cv = cvector_create();
		if (!cv)
			return (-1);
		while (get_next_path(cv, *command->args, &path_env))
		{
			if (try_open(cv->arr))
			{
				free(*command->args);
				*command->args = mstrdup(cv->arr);
				cvector_free(cv);
				return (-!*command->args);
			}
		}
		cvector_free(cv);
		if (error(-2, 0, 0))
			return (-1);
	}
	return (-!(try_open(*command->args)));
}

static void	exec_error(int err, char *msg)
{
	int	stat_loc;

	error(err, msg, 1);
	waitpid(-1, &stat_loc, 0);
	exit(1);
}

/*__attribute__ ((noreturn))*/
void	try_exec(t_command *command, t_vvector *envs, int *fildes, int out)
{
	char	**args_cp;
	char	**envs_cp;
	int		len;

	if (search_path(command, envs) == -1)
		exec_error(ENOCMD, *command->args);
	if (set_flows(command, fildes, &out) == -1)
		exec_error(-1, 0);
	if (dup2(fildes[0], STDIN_FILENO) == -1
		|| dup2(out, STDOUT_FILENO) == -1)
		exec_error(-1, 0);
	len = 0;
	while (command->args[len])
		len++;
	args_cp = convert_into_solid_arr(command->args, len);
	if (!args_cp)
		exec_error(-1, 0);
	envs_cp = convert_into_solid_arr((char **)envs->arr, envs->size);
	if (!envs_cp)
		exec_error(-1, 0);
	for (int i = 0; envs_cp[i]; ++i)//TEST
		dprintf(2, "%s\n", envs_cp[i]);//TEST
	execve(*args_cp, args_cp, NULL);
	exec_error(-1, 0);
}
