/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cvector.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nnamor <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/31 10:01:58 by nnamor            #+#    #+#             */
/*   Updated: 2021/07/31 10:02:00 by nnamor           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CVECTOR_H
# define CVECTOR_H

typedef struct s_cvector
{
	char			*arr;
	unsigned int	capacity;
	unsigned int	size;
}	t_cvector;

t_cvector		*cvector_create(void);
void			cvector_free(t_cvector *cv);
int				cvector_write(t_cvector *cv, char *str, unsigned int length);

#endif	/*CVECTOR_H*/
