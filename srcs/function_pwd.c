/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   function_pwd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ejina <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/04 11:55:49 by ejina             #+#    #+#             */
/*   Updated: 2021/08/04 11:55:59 by nnamor           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/function_pwd.h"
#include "../incs/error.h"

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
