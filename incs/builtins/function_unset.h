/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   function_unset.h                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ejina <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/04 11:47:26 by ejina             #+#    #+#             */
/*   Updated: 2021/08/04 11:48:31 by nnamor           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FUNCTION_UNSET_H
# define FUNCTION_UNSET_H

# include <unistd.h>
# include <stdio.h>
# include <vvector.h>

int		mstrncmp(const void *s1, const void *s2, int n);
char	*mstrdup(const char *s1);
char	*get_str(char *str);
int		mstrlen(const char *str);

#endif	/*FUNCTION_UNSET_H*/
