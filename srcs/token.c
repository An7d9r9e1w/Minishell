/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nnamor <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/31 10:03:26 by nnamor            #+#    #+#             */
/*   Updated: 2021/07/31 15:32:46 by nnamor           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

#include <token.h>
#include <error.h>

t_token	*token_create(char *value, t_kind kind)
{
	t_token	*token;

	token = malloc(sizeof(t_token));
	if (!token)
	{
		if (value)
			free(value);
		return (error_p(-1));
	}
	token->value = value;
	token->kind = kind;
	return (token);
}

void	token_free(t_token *token)
{
	if (token)
	{
		if (token->value)
			free(token->value);
		free(token);
	}
}
