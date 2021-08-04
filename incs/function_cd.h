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

# ifdef BUFSIZE
#  undef BUFSIZE
# endif	/*BUFSIZE*/

# define BUFSIZE 100

int		ft_strlen(const char *str);
int		ft_strcmp(const char *s1, const char *s2);
int		ft_strncmp(const char *s1, const char *s2, int n);
char	*ft_strjoin(char const *s1, char const *s2);
char	*ft_strdup(const char *s1);
int		msh_env(char **args, char **env);

#endif	/*FUNCTION_CD_H*/
