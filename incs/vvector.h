/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vvector.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nnamor <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/31 10:02:43 by nnamor            #+#    #+#             */
/*   Updated: 2021/07/31 10:02:44 by nnamor           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VVECTOR_H
# define VVECTOR_H

typedef struct s_vvector
{
	void			**arr;
	unsigned int	capacity;
	unsigned int	size;
}	t_vvector;

t_vvector	*vvector_create(void);
void		vvector_free(t_vvector *vv);
int			vvector_put(t_vvector *vv, void *data);
int			vvector_cut(t_vvector *vv);

#endif	/*VVECTOR_H*/
