#include <stdlib.h>
#include <sys/errno.h>
#include <stdio.h>//TEST

#include <token.h>
#include <string_utils.h>
#include <char_checkers.h>
#include <cvector.h>

static int	is_simple_word(char ch)
{
	return (is_word(ch) || (ch && !is_space(ch) && !is_spec(ch)));
}

static char	*get_simple_word(char **line_read)
{
	t_cvector	*cv;
	char		*ch;
	int			cv_stat;

	cv = cvector_create();
	if (!cv)
		return (0);
	ch = *line_read;
	while (is_simple_word(*ch))
	{
		cv_stat = cvector_write(cv, ch, 1);
		if (cv_stat == -1)
			break ;
		ch++;
	}
	*line_read = ch;
	if (cv_stat == -1)
		ch = 0;
	else
		ch = mstrdup(cv->arr);
	cvector_free(cv);
	return (ch);
}

static char	*get_env_value(char *env)//TEST
{
	return (mstrcat(mstrcat(mstrdup("\"VALUE_OF_"), env, mstrlen(env)), "\"", 1));
}

static char	*get_environment(char **line_read)//TEST
{
	t_cvector	*cv;
	char		*ch;
	int			cv_stat;

	ch = *line_read;
	if (*ch >= '0' && *ch <= '9')
	{
		(*line_read)++;
		return (0);
	}
	cv = cvector_create();
	if (!cv)
		return (0);
	while (is_word(*ch))
	{
		cv_stat = cvector_write(cv, ch, 1);
		if (cv_stat == -1)
			break ;
		ch++;
	}
	*line_read = ch;
	if (cv_stat == -1)
		ch = 0;
	else
		ch = get_env_value(cv->arr);
	cvector_free(cv);
	return (ch);
}

static char	*get_quoted_word(char **line_read)
{
	t_cvector	*cv;
	char		*ch;
	int			cv_stat;

	cv = cvector_create();
	if (!cv)
		return (0);
	ch = *line_read;
	while (*ch && *ch != '\'')
	{
		cv_stat = cvector_write(cv, ch, 1);
		if (cv_stat == -1)
			break ;
		ch++;
	}
	*line_read = ch + (*ch == '\''); // remake for checking correct token
	if (cv_stat == -1)
		ch = 0;
	else
		ch = mstrdup(cv->arr);
	cvector_free(cv);
	return (ch);
}

static char	*get_dquoted_word(char **line_read)
{
	t_cvector	*cv;
	char		*ch;
	char		*env;
	int			cv_stat;

	cv = cvector_create();
	if (!cv)
		return (0);
	ch = *line_read;
	while (*ch && *ch != '"')
	{
		if (*ch == '$')
		{
			ch++;
			env = get_environment(&ch);
			ch--;
			cv_stat = cvector_write(cv, env, mstrlen(env));
			free(env);
		}
		else
			cv_stat = cvector_write(cv, ch, 1);
		if (cv_stat == -1)
			break ;
		ch++;
	}
	*line_read = ch + (*ch == '"'); // remake too
	if (cv_stat == -1)
		ch = 0;
	else
		ch = mstrdup(cv->arr);
	cvector_free(cv);
	return (ch);
}

static char	*get_sequence(char **line_read)
{
	char	ch;

	ch = *(*line_read)++;
	if (ch == '$')
		return (get_environment(line_read));
	if (ch == '"')
		return (get_dquoted_word(line_read));
	if (ch == '\'')
		return (get_quoted_word(line_read));
	(*line_read)--;
	return (get_simple_word(line_read));
}

/*
 *	1. Add buffer, bufsize
 *	2. Pass to get_seq cv, buf, bufsize
 *	3. get_seq and get_*word* must return int
 */

t_token	*get_word(char **line_read)
{
	t_cvector	*cv;
	char		*word;
	int			cv_stat;

	cv = cvector_create();
	if (!cv)
		return (0);
	word = get_sequence(line_read);
	while (word)
	{
		cv_stat = cvector_write(cv, word, mstrlen(word));
		free(word);
		if (cv_stat == -1 || !**line_read || is_space(**line_read))
			break ;
		word = get_sequence(line_read);
	}
	if (cv_stat == -1)
		word = 0;
	else
		word = mstrdup(cv->arr);
	cvector_free(cv);
	if (!word)
		return (0);
	return (token_create(word, WORD));
}
