/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_stream.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nnamor <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/31 10:03:36 by nnamor            #+#    #+#             */
/*   Updated: 2021/08/01 07:02:41 by nnamor           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <readline/readline.h>
#include <readline/history.h>
#include <stdlib.h>
#include <unistd.h>

#include <token_stream.h>
#include <string_utils.h>
#include <error.h>

t_token_stream	*ts_create(char *prompt)
{
	t_token_stream	*ts;

	ts = malloc(sizeof(t_token_stream));
	if (!ts)
		return (error_p(-1));
	ts->line_read = 0;
	ts->line_cur = 0;
	ts->prompt = prompt;
	ts->buffer = 0;
	ts->full = 0;
	return (ts);
}

int	ts_read(t_token_stream *ts)
{
	if (ts->line_read)
		free(ts->line_read);
	ts->line_read = readline(ts->prompt);
	if (ts->line_read && *ts->line_read)
		add_history(ts->line_read);
	ts->line_cur = ts->line_read;
	return (-!ts->line_read);
}

void	ts_free(t_token_stream *ts)
{
	if (ts)
	{
		if (ts->line_read)
			free(ts->line_read);
		if (ts->full)
			free(ts->buffer);
		free(ts);
	}
}

int	ts_putback(t_token_stream *ts, t_token *token)
{
	if (ts->full)
		return (error(EFULLBUF));
	ts->buffer = token;
	ts->full = 1;
	return (0);
}

t_token	*ts_get_token(t_token_stream *ts)
{
	if (ts->full)
	{
		ts->full = 0;
		return (ts->buffer);
	}
	return (get_token(&ts->line_cur));
}
