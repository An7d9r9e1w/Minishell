#include <stdlib.h>
#include <sys/errno.h>
#include <stdio.h>//TEST

#include <token.h>
#include <string_utils.h>
#include <char_checkers.h>
#include <cvector.h>

static int	get_simple_word(char **line_read, t_cvector *cv)
{
	char		*ch;

	ch = *line_read;
	while (is_word(*ch) || (*ch && !is_space(*ch) && !is_spec(*ch)))
		if (cvector_write(cv, ch++, 1) == -1)
			return (-1);
	*line_read = ch;
	return (0);
}

static char	*get_env_value(char *env)//TEST
{
	return (mstrcat(mstrcat(mstrdup("\"VALUE_OF_"), env, mstrlen(env)), "\"", 1));
}

static int	get_environment(char **line_read, t_cvector *cv)//TEST
{
	t_cvector	*cv_env;
	char		*ch;

	ch = *line_read;
	if (*ch >= '0' && *ch <= '9')
	{
		(*line_read)++;
		return (0);
	}
	cv_env = cvector_create();
	if (!cv_env)
		return (-1);
	while (is_word(*ch))
	{
		if (cvector_write(cv_env, ch++, 1) == -1)
		{
			cvector_free(cv_env);
			return (-1);
		}
	}
	*line_read = ch;
	ch = get_env_value(cv_env->arr);//TEST
	cvector_free(cv_env);
	int	test = cvector_write(cv, ch, mstrlen(ch));//TEST
	free(ch);//TEST
	return (test);//TEST
	//return (cvector_write(cv, ch, mstrlen(ch)));
}

static int	get_quoted_word(char **line_read, t_cvector *cv)
{
	char		*ch;

	ch = *line_read;
	while (*ch && *ch != '\'')
		if (cvector_write(cv, ch++, 1) == -1)
			return (-1);
	*line_read = ch + (*ch == '\''); // remake for checking correct token
	return (0);
}

static int	get_dquoted_word(char **line_read, t_cvector *cv)
{
	char		*ch;

	ch = *line_read;
	while (*ch && *ch != '"')
	{
		if (*ch == '$')
		{
			ch++;
			if (get_environment(&ch, cv) == -1)
				return (-1);
		}
		else if (cvector_write(cv, ch++, 1) == -1)
			return (-1);
	}
	*line_read = ch + (*ch == '"'); // remake too
	return (0);
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

/*
 *	1. Add buffer, bufsize
 *	2. Pass to get_seq cv, buf, bufsize
 *	3. get_seq and get_*word* must return int
 */

//t_token	*get_word(char **line_read)
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
