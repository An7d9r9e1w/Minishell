/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   string_utils.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nnamor <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/31 10:02:15 by nnamor            #+#    #+#             */
/*   Updated: 2021/07/31 10:02:16 by nnamor           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRING_UTILS_H
# define STRING_UTILS_H

int		mstrlen(const char *str);
int		mstrlcpy(char *dst, const char *src, int dstsize);
char	*mstrdup(const char *str);
char	*mstrcat(char *dst, const char *src, unsigned int srclen);
void	drop_blanks(char **str);
char	**convert_into_solid_arr(char **strs, unsigned int len);

#endif	/*STRING_UTILS_H*/
