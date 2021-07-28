#ifndef TOKEN_H
# define TOKEN_H

# define WORD 'w'
# define QUOTE '\''
# define DQUOTE '"'
# define GREAT '>'
# define DGREAT 'G'
# define LESS '<'
# define DLESS 'L'
# define PIPE '|'
# define ENV '$'
# define AND 'A'
# define OR 'O'
# define WILDCARD '*'

typedef struct s_token
{
	char	*value;
	char	kind;
}	t_token;

t_token	get_token(char **line_read);

#endif	/*TOKEN_H*/
