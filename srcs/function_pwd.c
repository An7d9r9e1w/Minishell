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

#include <function_pwd.h>

int msh_pwd(char **args)
{
	char str[BUFSIZE];
	char *err;
	(void)(args);

	if (getcwd(str, BUFSIZE) == NULL)
	{
		err = strerror(errno);
		write(2, err, ft_strlen(err));
		write(2, "\n", 1);
	}
	else
		printf("%s\n", str);
	return (1);
}
