/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nnamor <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/08 14:01:22 by nnamor            #+#    #+#             */
/*   Updated: 2021/08/11 16:34:36 by nnamor           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTOR_H
# define EXECUTOR_H

# include <command_list.h>
# include <vvector.h>

int	executor(t_command_list *command_list, t_vvector *envs);

#endif	/*EXECUTOR_H*/
