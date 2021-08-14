/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nnamor <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/13 16:41:28 by nnamor            #+#    #+#             */
/*   Updated: 2021/08/14 08:57:34 by nnamor           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

#include <list.h>
#include <error.h>

t_list	*list_create(void *content)
{
	t_list	*list;

	list = malloc(sizeof(t_list));
	if (!list)
		return (error_p(-1));
	list->content = content;
	list->next = NULL;
	return (list);
}

void	list_free(t_list *list)
{
	t_list	*cur;

	while (list)
	{
		cur = list->next;
		free(list->content);
		free(list);
		list = cur;
	}
}

t_list	*get_list(t_list *list, int index)
{
	while (index-- && list->next)
		list = list->next;
	return (list);
}

int	get_list_size(t_list *list)
{
	int	len;

	len = 0;
	while (list)
	{
		list = list->next;
		++len;
	}
	return (len);
}
