/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_list.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nnamor <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/03 14:02:52 by nnamor            #+#    #+#             */
/*   Updated: 2021/08/08 15:52:10 by nnamor           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COMMAND_LIST_H
# define COMMAND_LIST_H

# define LOGIC_AND 0
# define LOGIC_OR 1

// O_WRONLY | O_CREAT | hdflag * O_APPEND | !hdflag * O_TRUNC

typedef enum e_file_mode
{
	TRUNC,
	APPEND,
	READ,
	HERE_DOC
}	t_file_mode;

typedef struct s_file
{
	char		*path;
	t_file_mode	mode;
}	t_file;

typedef struct s_command
{
	char	**args;
	t_file	*in;
	t_file	*out;
	int		in_size;
	int		out_size;
}	t_command;

typedef struct s_pipe_line
{
	t_command	*commands;
	int			size;
	int			logic_operator;
}	t_pipe_line;

typedef struct s_command_list
{
	t_pipe_line	*pipes;
	int			size;
}	t_command_list;

t_command_list	*command_list_create(void);
t_pipe_line		*pipe_line_create(void);
t_command		*command_create(void);
t_file			*file_create(char *path, t_file_mode mode);

void			command_list_free(t_command_list *command_list);
void			pipe_line_free(t_pipe_line *pipe_line);
void			command_free(t_command *command);
void			file_free(t_file *file);

#endif	/*COMMAND_LIST_H*/
