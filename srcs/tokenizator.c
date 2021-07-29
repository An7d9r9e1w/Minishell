#include <stdlib.h>
#include <stdio.h>//TEST

#include <token.h>
#include <string_utils.h>
#include <char_checkers.h>

t_token	*get_word(char **line_read);

static t_token	*get_operator(char **line_read, char op, char dop)
{
	if (*(*line_read - 1) == **line_read)
	{
		(*line_read)++;
		return (token_create(0, dop));
	}
	return (token_create(0, op));
}

t_token	*get_token(char **line_read)
{
	char	ch;

	if (!**line_read)
		return (0);
	drop_blanks(line_read);
	ch = *(*line_read)++;
	if (ch == '<')
		return (get_operator(line_read, LESS, DLESS));
	if (ch == '>')
		return (get_operator(line_read, GREAT, DGREAT));
	if (ch == '&')
		return (get_operator(line_read, ERROR, AND));
	if (ch == '|')
		return (get_operator(line_read, PIPE, OR));
	(*line_read)--;
	return (get_word(line_read));
//WILDCARD
}
