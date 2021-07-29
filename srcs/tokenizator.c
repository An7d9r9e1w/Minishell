#include <stdlib.h>

#include <token.h>
#include <string_utils.h>

int	get_word(char **line_read, t_token **token);

static int	get_operator(char **line_read, t_token **token, char op, char dop)
{
	if (*(*line_read - 1) == **line_read)
	{
		(*line_read)++;
		*token = token_create(0, dop);
		return (-!*token);
	}
	*token = token_create(0, op);
	return (-!*token);
}

int	get_token(char **line_read, t_token **token)
{
	char	ch;

	if (!**line_read)
		return (1);
	drop_blanks(line_read);
	ch = *(*line_read)++;
	if (ch == '<')
		return (get_operator(line_read, token, LESS, DLESS));
	if (ch == '>')
		return (get_operator(line_read, token, GREAT, DGREAT));
	if (ch == '&')
		return (get_operator(line_read, token, ERROR, AND));
	if (ch == '|')
		return (get_operator(line_read, token, PIPE, OR));
	(*line_read)--;
	return (get_word(line_read, token));
//WILDCARD
}
