/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   char_checkers.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nnamor <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/31 10:02:49 by nnamor            #+#    #+#             */
/*   Updated: 2021/08/14 08:55:53 by nnamor           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <char_checkers.h>

int	is_space(char c)
{
	return (c == ' ' || (c >= '\t' && c <= '\r'));
}

int	is_spec(char c)
{
	return (c == '<' || c == '>' || c == '|' || c == '&' || c == '"'
		|| c == '\'' || c == '$');
}

int	is_word(char c)
{
	return ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z')
		|| (c >= '0' && c <= '9') || c == '_');
}
