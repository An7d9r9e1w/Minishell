/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nnamor <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/31 15:01:47 by nnamor            #+#    #+#             */
/*   Updated: 2021/08/01 12:49:41 by nnamor           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ERROR_H
# define ERROR_H

# define EFULLBUF 1
# define EEND 2
# define EBADTOKEN 3
# define EQUOTE 4

/*
 *	err		-	 -1 = standard error
 *				<-1 = return error value
 *	add_msg	-	put additional error message to buffer, if add_msg isn't NULL
 *	print	-	output error, if print == 1
 *					err and buf reset to zero
 */
int		error(int err_n, char *add_msg, int print);
void	*error_p(int err_n);

#endif	/*ERROR_H*/
