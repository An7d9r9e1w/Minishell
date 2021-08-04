/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizator.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nnamor <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/31 10:03:42 by nnamor            #+#    #+#             */
/*   Updated: 2021/08/03 18:24:15 by nnamor           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

#include <token.h>
#include <string_utils.h>

t_token	*get_word(char **line_read);

static t_token	*get_operator(char **line_read, char op, char dop)
{
	t_token	*token;
	char	*value;

	if (*(*line_read - 1) == **line_read)
	{
		value = mstrcat(0, *line_read - 1, 2);
		(*line_read)++;
		op = dop;
	}
	else
		value = mstrcat(0, *line_read - 1, 1);
	if (!value)
		return (0);
	token = token_create(value, op);
	if (!token)
		free(value);
	return (token);
}

t_token	*get_token(char **line_read)
{
	char	ch;

	if (!**line_read)
		return (0);
	drop_blanks(line_read);
	ch = *(*line_read)++;
	if (ch == '<')
		return (get_operator(line_read, LESS, DLESS));
	if (ch == '>')
		return (get_operator(line_read, GREAT, DGREAT));
	if (ch == '&')
		return (get_operator(line_read, ERROR, AND));
	if (ch == '|')
		return (get_operator(line_read, PIPE, OR));
	(*line_read)--;
	return (get_word(line_read));
//WILDCARD
}
