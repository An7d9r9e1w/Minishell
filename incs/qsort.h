/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   qsort.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nnamor <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/01 09:35:35 by nnamor            #+#    #+#             */
/*   Updated: 2021/08/01 09:37:39 by nnamor           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef QSORT_H
# define QSORT_H

void	mqsort(void *base, size_t nel, size_t width,
			int (*compar)(const void *, const void *));

#endif	/*QSORT_H*/
