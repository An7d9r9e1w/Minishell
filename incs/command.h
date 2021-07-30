#ifndef COMMAND_H
# define COMMAND_H

# define LOGIC_OR 0
# define LOGIC_AND 1

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
	t_pipe_line				*current_cmd;
	struct s_command_list	*next_cmd;
	int						logic_operator;
}	t_command_list;

#endif	/*COMMAND_H*/
