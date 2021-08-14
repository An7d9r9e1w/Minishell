/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_sort.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nnamor <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/14 08:39:40 by nnamor            #+#    #+#             */
/*   Updated: 2021/08/14 08:54:33 by nnamor           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <list.h>
#include <token.h>
#include <string_utils.h>

static int	token_cmp(t_token *t1, t_token *t2)
{
	return (mstrcmp(t1->value, t2->value) < 0);
}

static int	token_cmpz(t_token *t1, t_token *t2)
{
	return (mstrcmp(t1->value, t2->value) <= 0);
}

static void	init(t_list **root, t_list **right, t_list **left)
{
	if (token_cmp((*left)->content, (*right)->content))
	{
		*root = *left;
		*left = (*left)->next;
	}
	else
	{
		*root = *right;
		*right = (*right)->next;
	}
}

static t_list	*merge(t_list *left, t_list *right)
{
	t_list	*root;
	t_list	*cur;

	init(&root, &right, &left);
	cur = root;
	while (left && right)
	{
		if (token_cmpz(left->content, right->content))
		{
			cur->next = left;
			left = left->next;
		}
		else
		{
			cur->next = right;
			right = right->next;
		}
		cur = cur->next;
	}
	cur->next = left;
	while (cur->next)
		cur = cur->next;
	cur->next = right;
	return (root);
}

t_list	*mergesort_list(t_list *list)
{
	t_list	*left;
	t_list	*right;

	if (!list || !list->next)
		return (list);
	left = get_list(list, (get_list_size(list) - 1) >> 1);
	right = left->next;
	left->next = 0;
	left = mergesort_list(list);
	right = mergesort_list(right);
	return (merge(left, right));
}
