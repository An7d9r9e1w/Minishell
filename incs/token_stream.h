/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_stream.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nnamor <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/31 10:02:34 by nnamor            #+#    #+#             */
/*   Updated: 2021/07/31 16:19:27 by nnamor           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TOKEN_STREAM_H
# define TOKEN_STREAM_H

#include <token.h>

# define EFULLBUF "Fatal: attempt to put a token back to full stream\n"

typedef struct s_token_stream
{
	char	*line_read;
	char	*line_cur;
	char	*prompt;
	t_token	*buffer;
	int		full;
}	t_token_stream;

t_token_stream	*ts_create(char *prompt);
int				ts_read(t_token_stream *ts);
t_token			*ts_get_token(t_token_stream *ts);
int				ts_putback(t_token_stream *ts, t_token *token);
void			ts_free(t_token_stream *ts);

#endif	/*TOKEN_STREAM_H*/
