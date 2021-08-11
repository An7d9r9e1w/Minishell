/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environment.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nnamor <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/04 14:34:46 by nnamor            #+#    #+#             */
/*   Updated: 2021/08/11 15:02:09 by nnamor           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ENVIRONMENT_H
# define ENVIRONMENT_H

# include <vvector.h>

t_vvector	*get_environments(char **env);
int			get_environment_index(t_vvector *envs, char	*name);
char		*get_environment_value(t_vvector *env, char *name);
int			set_environment(t_vvector *envs, char *name, char *value);

#endif	/*ENVIRONMENT_H*/
