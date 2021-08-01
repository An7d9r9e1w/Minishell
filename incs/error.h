/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nnamor <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/31 15:01:47 by nnamor            #+#    #+#             */
/*   Updated: 2021/08/01 07:02:54 by nnamor           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ERROR_H
# define ERROR_H

# define EFULLBUF 1
# define EEND 2

int		error(int err_n, char *additional_msg);
void	*error_p(int err_n);
int		error_msg(void);

#endif	/*ERROR_H*/
