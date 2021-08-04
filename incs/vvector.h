/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vvector.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nnamor <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/31 10:02:43 by nnamor            #+#    #+#             */
/*   Updated: 2021/08/03 14:03:13 by nnamor           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VVECTOR_H
# define VVECTOR_H

# ifndef VV_CAPACITY
#  define VV_CAPACITY 16
# endif	/*VV_CAPACITY*/
#include <stdlib.h>
typedef struct s_vvector
{
	void			**arr;
	unsigned int	capacity;
	unsigned int	size;
}				t_vvector;

/*
 *	Part 1
 */
t_vvector	*vvector_create(void);
void		vvector_free(t_vvector *vv);
int			vvector_put(t_vvector *vv, void *data);
int			vvector_erase(t_vvector *vv,
				unsigned int index, void (*free_s)(void *));
/*
 *	Part 2
 */
int			vvector_get_index(t_vvector *vv, void *to_find,
				int	(*compare)(const void *, const void *));
int			vvector_get_index_n(t_vvector *vv, void *to_find, int n,
						   int	(*compare)(const void *, const void *, int n));
void		*vvector_find(t_vvector *vv, void *to_find,
				int (*compare)(const void *, const void *));
int			vvector_replace(t_vvector *vv, unsigned int index, void *data);
void		*vvector_export(t_vvector *vv, unsigned int width, int *len);
/*
 *	Part 3
 */
void		*vvector_copy(t_vvector *vv);
int			vvector_clear(t_vvector *vv);

#endif	/*VVECTOR_H*/
