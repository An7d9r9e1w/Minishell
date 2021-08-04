/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   function_env.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ejina <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/04 11:43:54 by ejina             #+#    #+#             */
/*   Updated: 2021/08/04 11:44:37 by nnamor           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FUNCTION_ENV_H
# define FUNCTION_ENV_H

# include <stdio.h>

void	mqsort(void *base, size_t nel, size_t width,
			int (*compar)(const void *, const void *));
int		ft_strcmp(const void *s1, const void *s2);

#endif	/*FUNCTION_ENV_H*/
