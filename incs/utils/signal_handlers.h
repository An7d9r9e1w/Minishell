/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_handlers.h                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nnamor <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/12 16:25:37 by nnamor            #+#    #+#             */
/*   Updated: 2021/08/12 16:26:32 by nnamor           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SIGNAL_HANDLERS_H
# define SIGNAL_HANDLERS_H

void	signal_handler_sub(int sig);
void	signal_handler(int sig);
void	signal_quit(int sig);

#endif	/*SIGNAL_HANDLERS_H*/
