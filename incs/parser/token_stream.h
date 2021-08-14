/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_stream.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nnamor <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/31 10:02:34 by nnamor            #+#    #+#             */
/*   Updated: 2021/08/13 17:52:17 by nnamor           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TOKEN_STREAM_H
# define TOKEN_STREAM_H

# include <token.h>
# include <vvector.h>
# include <list.h>

typedef struct s_token_stream
{
	char	*line_read;
	char	*line_cur;
	char	*prompt;
	t_list	*buffer;
	int		size;
}	t_token_stream;

/*
 *	Part 1
 */
t_token_stream	*ts_create(char *prompt);
void			ts_free(t_token_stream *ts);
t_token			*ts_get_token(t_token_stream *ts, t_vvector *envs);

/*
 *	Part 2
 */
int				ts_read(t_token_stream *ts);
int				ts_putback(t_token_stream *ts, t_token *token);
char			*ts_get_prompt(char *new_prompt);

#endif	/*TOKEN_STREAM_H*/
