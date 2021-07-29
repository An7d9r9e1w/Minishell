#include <stdlib.h>

#include <token.h>
#include <string_utils.h>
#include <char_checkers.h>
#include <cvector.h>

#ifdef BUFFERSIZE
# undef BUFFERSIZE
#endif

#define BUFFERSIZE 1024

int	get_environment(char **line_read, t_cvector *cv);//TEST

static int	get_simple_word(char **line_read, t_cvector *cv)
{
	const char	*ch = *line_read;
	char		buf[BUFFERSIZE];
	int			len;

	len = 0;
	while (is_word(*ch) || (*ch && !is_space(*ch) && !is_spec(*ch)))
	{
		buf[len++] = *ch++;
		if (len == BUFFERSIZE)
		{
			if (cvector_write(cv, buf, len) == -1)
				return (-1);
			len = 0;
		}
	}
	*line_read = (char *)ch;
	return (-(len && cvector_write(cv, buf, len) == -1));
}

static int	get_quoted_word(char **line_read, t_cvector *cv)
{
	const char	*ch = *line_read;
	char		buf[BUFFERSIZE];
	int			len;

	len = 0;
	while (*ch && *ch != '\'')
	{
		buf[len++] = *ch++;
		if (len == BUFFERSIZE)
		{
			if (cvector_write(cv, buf, len) == -1)
				return (-1);
			len = 0;
		}
	}
	*line_read = (char *)ch + (*ch == '\'');//remake for checking correct token
	return (-(len && cvector_write(cv, buf, len) == -1));
}

static int	get_dquoted_word(char **line_read, t_cvector *cv)
{
	const char	*ch = *line_read;
	char		buf[BUFFERSIZE];
	int			len;

	len = 0;
	while (*ch && *ch != '"')
	{
		if (*ch == '$')
		{
			*line_read = (char *)++ch;
			if (cvector_write(cv, buf, len) || get_environment(line_read, cv))
				return (-1);
			len = 0;
			continue ;
		}
		buf[len++] = *ch++;
		if (len == BUFFERSIZE)
		{
			if (cvector_write(cv, buf, len) == -1)
				return (-1);
			len = 0;
		}
	}
	*line_read = (char *)ch + (*ch == '"'); // remake too
	return (-(len && cvector_write(cv, buf, len)));
}

static int	get_sequence(char **line_read, t_cvector *cv)
{
	char	ch;

	ch = *(*line_read)++;
	if (ch == '$')
		return (get_environment(line_read, cv));
	if (ch == '"')
		return (get_dquoted_word(line_read, cv));
	if (ch == '\'')
		return (get_quoted_word(line_read, cv));
	(*line_read)--;
	return (get_simple_word(line_read, cv));
}

int	get_word(char **line_read, t_token **token)
{
	t_cvector	*cv;
	char		*word;

	cv = cvector_create();
	if (!cv)
		return (-1);
	while (**line_read && !is_space(**line_read))
	{
		if (get_sequence(line_read, cv) == -1)
		{
			cvector_free(cv);
			return (-1);
		}
	}
	word = mstrdup(cv->arr);
	cvector_free(cv);
	if (!word)
		return (-1);
	*token = token_create(word, WORD);
	return (-!*token);
}
