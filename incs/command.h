#ifndef COMMAND_H
# define COMMAND_H

typedef struct s_command
{
	char	*name;
	char	**args;
	char	*in;
	char	*out;
}	t_command;

typedef struct s_pipe_line
{
	t_command	*cmds;
}	t_pipe_line;

typedef struct s_command_list
{
	t_pipe_line				*pl;
	struct s_command_list	*cl;
	int						lp;
}	t_command_list;

#endif	/*COMMAND_H*/
