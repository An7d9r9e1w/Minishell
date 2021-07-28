#include <stdlib.h>
#include <stdio.h>//TEST

#include <token.h>
#include <string_utils.h>
#include <char_checkers.h>

#ifdef BUFSIZE
# undef BUFSIZE
#endif

# define BUFSIZE 1024

static t_token	*get_operator(char **line_read, char op, char dop)
{
	if (*(*line_read - 1) == **line_read)
	{
		(*line_read)++;
		return (token_create(0, dop));
	}
	return (token_create(0, op));
}

static int	is_simple_word(char ch)
{
	return (is_word(ch) || (ch && !is_space(ch) && !is_spec(ch)));
}

static t_token	*get_word(char **line_read)
{
	char	buf[BUFSIZE];
	char	*pbuf;
	char	*ch;
	int		len;

	pbuf = buf;
	ch = *line_read;
	len = BUFSIZE;
	while (len-- && is_simple_word(*ch))
		*pbuf++ = *ch++;
	*pbuf = 0;
	*line_read = ch;
	ch = mstrdup(buf);
	if (ch)
		return (token_create(ch, WORD));
	return (0);
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
	else if (ch == '>')
		return (get_operator(line_read, GREAT, DGREAT));
	else if (ch == '&')
		return (get_operator(line_read, ERROR, AND));
	else if (ch == '|')
		return (get_operator(line_read, PIPE, OR));
	/*else if (ch == '\'' || ch == '"')
		return (token_create(0, ch));*/
	(*line_read)--;
	return (get_word(line_read));
//WORD
//ENV
//WILDCARD
}
