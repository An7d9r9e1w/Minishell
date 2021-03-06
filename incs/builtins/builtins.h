/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ejina <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/04 11:49:04 by ejina             #+#    #+#             */
/*   Updated: 2021/08/11 07:09:26 by nnamor           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTINS_H
# define BUILTINS_H

# include <vvector.h>

int			msh_unset(char **args, t_vvector *env);
int			msh_env(char **args, t_vvector *env);
int			msh_pwd(char **args);
int			msh_echo(char **args);
int			msh_cd(char **args, t_vvector *env);
int			msh_export(char **args, t_vvector *env);
void		msh_exit(char **args);
/*int			ft_strcmp(const void *s1, const void *s2);*/
/*int			ft_strlen(const char *str);*/

#endif	/*BUILTINS_H*/
