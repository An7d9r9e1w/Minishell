/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nnamor <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/13 16:38:14 by nnamor            #+#    #+#             */
/*   Updated: 2021/08/14 08:55:10 by nnamor           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIST_H
# define LIST_H

typedef struct s_list
{
	void			*content;
	struct s_list	*next;
}	t_list;

t_list	*list_create(void *content);
void	list_free(t_list *list);
t_list	*get_list(t_list *list, int index);
int		get_list_size(t_list *list);

#endif	/*LIST_H*/
