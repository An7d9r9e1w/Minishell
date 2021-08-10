/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   string_utils.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nnamor <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/31 10:02:15 by nnamor            #+#    #+#             */
/*   Updated: 2021/08/10 14:15:40 by nnamor           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRING_UTILS_H
# define STRING_UTILS_H

/*
 *	Part 1
 */
int		mstrlen(const char *str);
int		mstrlcpy(char *dst, const char *src, int dstsize);
char	*mstrdup(const char *str);
char	*mstrcat(char *dst, const char *src, unsigned int srclen);
void	drop_blanks(char **str);

/*
 *	Part 2
 */
char	**convert_into_solid_arr(char **strs, unsigned int len);
int		mstrcmp(const char *s1, const char *s2);
int		mstrcmpv(const void *v1, const void *v2);
int		mstrncmp(const char *s1, const char *s2, unsigned int n);
int		envcmpv(const void *s1, const void *s2);

/*
 *	Part 3
 */
char	*mstrjoin(char const *s1, char const *s2);
char	*matoi(char *s1);
#endif	/*STRING_UTILS_H*/
