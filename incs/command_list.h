/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_list.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nnamor <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/31 10:01:51 by nnamor            #+#    #+#             */
/*   Updated: 2021/07/31 12:20:08 by nnamor           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COMMAND_LIST_H
# define COMMAND_LIST_H

# define LOGIC_OR 0
# define LOGIC_AND 1

# define BASIC_MODE 0
# define ALT_MODE 1

// O_WRONLY | O_CREAT | hdflag * O_APPEND | !hdflag * O_TRUNC

typedef struct s_file
{
	char	*path;
	int		mode;
}	t_file;

typedef struct s_command
{
	char	*name;
	char	**args;
	t_file	*in;
	t_file	*out;
}	t_command;

typedef struct s_pipe_line
{
	t_command	*cmds;
	int			size;
	int			logic_operator;
}	t_pipe_line;

typedef struct s_command_list
{
	t_pipe_line	*pipes;
	int			size;
}	t_command_list;

#endif	/*COMMAND_LIST_H*/
