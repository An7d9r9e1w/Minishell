/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_stream_2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nnamor <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/07 17:14:21 by nnamor            #+#    #+#             */
/*   Updated: 2021/08/14 14:57:19 by nnamor           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <stdlib.h>

#include <token_stream.h>
#include <string_utils.h>
#include <error.h>
#include <vvector.h>

int	ts_push_token(t_token_stream *ts, t_token *token);

char	*ts_get_prompt(char *new_prompt)
{
	static char	*prompt = 0;

	if (new_prompt)
		prompt = new_prompt;
	return (prompt);
}

int	ts_read(t_token_stream *ts)
{
	if (ts->line_read)
		free(ts->line_read);
	ts->line_read = readline(ts->prompt);
	if (ts->line_read && !is_empty(ts->line_read))
		add_history(ts->line_read);
	ts->line_cur = ts->line_read;
	return (-!ts->line_read);
}

int	ts_putback(t_token_stream *ts, t_token *token)
{
	return (ts_push_token(ts, token));
}
