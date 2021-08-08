/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   function_pwd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ejina <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/04 11:55:49 by ejina             #+#    #+#             */
/*   Updated: 2021/08/08 10:26:16 by nnamor           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <function_pwd.h>
#include <error.h>

int	msh_pwd(char **args)
{
	char	str[BUFSIZE];

	(void)(args);
	if (getcwd(str, BUFSIZE) == NULL)
		return (error(-1, 0, 0));
	else
		printf("%s\n", str);
	return (1);
}
