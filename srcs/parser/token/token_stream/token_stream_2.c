/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_stream_2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nnamor <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/07 17:14:21 by nnamor            #+#    #+#             */
/*   Updated: 2021/08/10 12:39:18 by nnamor           ###   ########.fr       */
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

char	*ts_get_prompt(char *new_prompt)
{
	static char	*prompt = 0;

	if (new_prompt)
		prompt = new_prompt;
	return (prompt);
}

void	signal_handler(int sig)
{
	extern int	rl_end;
	int			i;

	if (sig == SIGINT)
	{
		i = mstrlen(ts_get_prompt(0)) + rl_end;
		while (i--)
			printf("\e[C");
		printf("\e[K\n");
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
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

int	ts_putback(t_token_stream *ts, t_token *token)
{
	if (ts->full)
		return (error(EFULLBUF, 0, 0));
	ts->buffer = token;
	ts->full = 1;
	return (0);
}

t_token	*ts_get_token(t_token_stream *ts, t_vvector *envs)
{
	if (ts->full)
	{
		ts->full = 0;
		return (ts->buffer);
	}
	return (get_token(&ts->line_cur, envs));
}
