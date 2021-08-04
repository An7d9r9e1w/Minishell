/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   function_pwd.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ejina <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/04 11:46:08 by ejina             #+#    #+#             */
/*   Updated: 2021/08/04 11:47:11 by nnamor           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FUNCTION_PWD_H
# define FUNCTION_PWD_H

# include <sys/errno.h>
# include <stdio.h>
# include <unistd.h>
# include <string.h>

# ifdef BUFSIZE
#  undef BUFSIZE
# endif	/*BUFSIZE*/

# define BUFSIZE 100

int	ft_strlen(const char *str);

#endif	/*FUNCTION_PWD_H*/
