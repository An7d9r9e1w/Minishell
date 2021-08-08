/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   function_cd.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ejina <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/04 11:41:10 by ejina             #+#    #+#             */
/*   Updated: 2021/08/04 11:42:49 by nnamor           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FUNCTION_CD_H
# define FUNCTION_CD_H

# include <unistd.h>
# include <string.h>
# include <errno.h>
# include <stdlib.h>
# include <vvector.h>

# ifdef BUFSIZE
#  undef BUFSIZE
# endif	/*BUFSIZE*/

# define BUFSIZE 100

int		mstrlen(const char *str);
int		mstrcmp(const char *s1, const char *s2);
int		mstrncmp(const char *s1, const char *s2, unsigned int n);
char	*mstrjoin(char const *s1, char const *s2);
char	*mstrdup(const char *str);
int		msh_env(char **args, char **env);
int		update_pwd(t_vvector *my_env);
int		update_oldpwd(t_vvector *my_env);

#endif	/*FUNCTION_CD_H*/
