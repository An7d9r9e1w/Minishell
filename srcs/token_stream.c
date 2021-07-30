#include <stdlib.h>
#include <unistd.h>

#include <token_stream.h>
#include <string_utils.h>

t_token_stream	*ts_create(void)
{
	t_token_stream	*ts;

	ts = malloc(sizeof(t_token_stream));
	if (!ts)
		return (0);
	ts->buffer = 0;
	ts->full = 0;
	return (ts);
}

void	ts_free(t_token_stream *ts)
{
	if (ts)
	{
		if (ts->full)
			free(ts->buffer);
		free(ts);
	}
}

int	ts_putback(t_token_stream *ts, t_token *token)
{
	if (ts->full)
	{
		write(2, EFULLBUF, mstrlen(EFULLBUF));
		return (-1);
	}
	ts->buffer = token;
	ts->full = 1;
	return (0);
}

int	ts_get_token(t_token_stream *ts, char **line_read, t_token **token)
{
	if (ts->full)
	{
		ts->full = 0;
		*token = ts->buffer;
		return (0);
	}
	return (get_token(line_read, token));
}
