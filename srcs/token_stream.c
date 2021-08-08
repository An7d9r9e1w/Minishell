/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_stream.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nnamor <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/31 10:03:36 by nnamor            #+#    #+#             */
/*   Updated: 2021/08/08 07:57:39 by nnamor           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

#include <token_stream.h>
#include <error.h>

char	*ts_get_prompt(char *new_prompt);

t_token_stream	*ts_create(char *prompt)
{
	t_token_stream	*ts;

	ts = malloc(sizeof(t_token_stream));
	if (!ts)
		return (error_p(-1));
	ts->line_read = 0;
	ts->line_cur = 0;
	ts->prompt = prompt;
	ts_get_prompt(prompt);
	ts->buffer = 0;
	ts->full = 0;
	return (ts);
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
