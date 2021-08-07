/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   function_export.h                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ejina <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/04 11:45:02 by ejina             #+#    #+#             */
/*   Updated: 2021/08/04 11:45:57 by nnamor           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FUNCTION_EXPORT_H
# define FUNCTION_EXPORT_H

# include <stdio.h>
# include <unistd.h>
# include <vvector.h>

int		msh_env(char **args, t_vvector *env);
char	*mstrdup(const char *str);
int		mstrlen(const char *str);
int		mstrncmp(const void *s1, const void *s2, int n);

#endif	/*FUNCTION_EXPORT_H*/
