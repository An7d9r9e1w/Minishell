/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizator_word.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nnamor <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/31 10:03:48 by nnamor            #+#    #+#             */
/*   Updated: 2021/08/14 08:55:39 by nnamor           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

#include <token.h>
#include <string_utils.h>
#include <char_checkers.h>
#include <cvector.h>
#include <error.h>

#ifdef BUFFERSIZE
# undef BUFFERSIZE
#endif

#define BUFFERSIZE 1024

int	get_environment(char **line_read, t_cvector *cv,
		t_vvector *envs, int dquoted);

static int	get_simple_word(char **line_read, t_cvector *cv)
{
	const char	*ch = *line_read;
	char		buf[BUFFERSIZE];
	int			len;

	len = 0;
	while (is_word(*ch) || (*ch && !is_space(*ch) && !is_spec(*ch)))
	{
		if (*ch++ == '*')
			buf[len++] = -1;
		else
			buf[len++] = ch[-1];
		if (len == BUFFERSIZE)
		{
			if (cvector_write(cv, buf, len) == -1)
				return (-1);
			len = 0;
		}
	}
	*line_read = (char *)ch;
	if (!len)
		return (1);
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
	if (*ch != '\'')
		return (error(EQUOTE, "'", 0));
	*line_read = (char *)ch + 1;
	return (-(len && cvector_write(cv, buf, len) == -1));
}

static int	get_dquoted_word(char **line_read, t_cvector *cv, t_vvector *envs)
{
	char	*ch;

	ch = *line_read;
	while (*ch && *ch != '"')
	{
		if (*ch == '$')
		{
			ch++;
			if (get_environment(&ch, cv, envs, 1))
				return (-1);
		}
		else if (cvector_write(cv, (char *)ch++, 1) == -1)
			return (-1);
	}
	if (*ch != '"')
		return (error(EQUOTE, "\"", 0));
	*line_read = (char *)ch + 1;
	return (0);
}

static int	get_sequence(char **line_read, t_cvector *cv, t_vvector *envs)
{
	const char	ch = *(*line_read)++;

	if (ch == '$')
		return (get_environment(line_read, cv, envs, 0));
	if (ch == '"')
		return (get_dquoted_word(line_read, cv, envs));
	if (ch == '\'')
		return (get_quoted_word(line_read, cv));
	(*line_read)--;
	return (get_simple_word(line_read, cv));
}

t_token	*get_word(char **line_read, t_vvector *envs)
{
	t_cvector	*cv;
	t_token		*token;
	int			seq_stat;

	cv = cvector_create();
	if (!cv)
		return (0);
	seq_stat = get_sequence(line_read, cv, envs);
	while (**line_read && !is_space(**line_read) && !seq_stat)
		seq_stat = get_sequence(line_read, cv, envs);
	if (cv->size && seq_stat != -1)
		token = token_create(mstrdup(cv->arr), WORD);
	else
		token = 0;
	cvector_free(cv);
	return (token);
}
