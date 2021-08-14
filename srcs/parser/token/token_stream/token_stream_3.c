/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_stream.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nnamor <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/31 10:03:36 by nnamor            #+#    #+#             */
/*   Updated: 2021/08/14 08:59:36 by nnamor           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <dirent.h>

#include <token_stream.h>
#include <list.h>
#include <error.h>
#include <wildcard.h>
#include <environment.h>
#include <string_utils.h>

void	ts_free_buffer(t_token_stream *ts);
t_list	*mergesort_list(t_list *list);

static int	has_wildcard(char *str)
{
	int	i;

	i = 0;
	while (*str)
	{
		if (*str == -1)
		{
			*str = '*';
			++i;
		}
		++str;
	}
	return (i);
}

int	ts_push_token(t_token_stream *ts, t_token *token)
{
	t_list	*list;

	if (!token)
		return (-1);
	if (!ts->buffer)
	{
		ts->buffer = list_create(token);
		if (!ts->buffer)
			token_free(token);
		ts->size += (ts->buffer != NULL);
		return (-!ts->buffer);
	}
	list = ts->buffer;
	while (list->next)
		list = list->next;
	list->next = list_create(token);
	if (!list->next)
		token_free(token);
	ts->size += (list->next != NULL);
	return (-!list->next);
}

int	ts_check_for_wildcard(t_token_stream *ts, t_token *token, t_vvector *envs)
{
	DIR				*dirp;
	struct dirent	*dr;

	if (token->kind != WORD || !has_wildcard(token->value))
		return (0);
	dirp = opendir(get_environment_value(envs, "PWD"));
	if (!dirp)
		return (error(-1, 0, 1));
	dr = readdir(dirp);
	while (dr)
	{
		if ((*token->value == '.' || *dr->d_name != '.')
			&& match(token->value, dr->d_name)
			&& ts_push_token(ts, token_create(mstrdup(dr->d_name), WORD)))
		{
			ts_free_buffer(ts);
			closedir(dirp);
			return (error(-1, 0, 1));
		}
		dr = readdir(dirp);
	}
	closedir(dirp);
	ts->buffer = mergesort_list(ts->buffer);
	return (1);
}

t_token	*ts_pop_token(t_token_stream *ts)
{
	t_list	*tmp;
	t_token	*token;

	if (!ts->size)
		return (0);
	tmp = ts->buffer;
	ts->buffer = tmp->next;
	token = tmp->content;
	free(tmp);
	--ts->size;
	return (token);
}
