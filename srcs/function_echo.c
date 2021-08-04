/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   function_echo.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ejina <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/04 11:53:30 by ejina             #+#    #+#             */
/*   Updated: 2021/08/04 11:53:57 by nnamor           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <function_echo.h>

static void print_arg(char **args, int i)
{
	while (args[i])
	{
		printf("%s", args[i]);
		if (args[i + 1])
			printf(" ");
		i++;
	}
}

int msh_echo(char **args)
{
	int i;

	i = 0;
	while(args[i])
		i++;
	if (i == 1)
		printf("\n");
	else
	{
		i = 1;
		if (!ft_strcmp(args[i], "-n"))
		{
			i++;
			print_arg(args, i);
		}
		else
		{
			print_arg(args, i);
			printf("\n");
		}
	}
	return (1);
}
