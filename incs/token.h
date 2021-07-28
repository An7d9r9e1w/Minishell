#ifndef TOKEN_H
# define TOKEN_H

typedef enum e_kind
{
	ERROR,
	WORD,
	QUOTE,
	DQUOTE,
	GREAT,
	DGREAT,
	LESS,
	DLESS,
	PIPE,
	ENV,
	AND,
	OR,
	WILDCARD
}	t_kind;

typedef struct s_token
{
	char	*value;
	t_kind	kind;
}	t_token;

t_token	*get_token(char **line_read);//TEST
t_token *token_create(char *value, t_kind kind);
void	token_free(t_token *token);

#endif	/*TOKEN_H*/
