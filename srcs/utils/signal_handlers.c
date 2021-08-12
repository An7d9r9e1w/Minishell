/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_handlers.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nnamor <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/12 16:20:51 by nnamor            #+#    #+#             */
/*   Updated: 2021/08/12 17:17:36 by nnamor           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <signal.h>
#include <stdio.h>
#include <unistd.h>

#include <readline/readline.h>
#include <token_stream.h>
#include <string_utils.h>

void	signal_handler_sub(int sig)
{
	extern int	rl_end;
	int			i;

	if (sig == SIGINT)
	{
		i = mstrlen(ts_get_prompt(0)) + rl_end;
		while (i--)
			printf("\e[C");
		printf("\e[K\n");
		rl_replace_line("", 0);
	}
	else if (sig == SIGQUIT)
	{
		if (rl_end)
			exit(0);
		write(1, "\e[K", 3);
		rl_replace_line("", 0);
	}
}

void	signal_handler(int sig)
{
	signal_handler_sub(sig);
	rl_on_new_line();
	rl_redisplay();
}

void	signal_quit(int sig)
{
	if (sig == SIGQUIT)
	{
		write(2, "Quit: 3\n", 8);
		rl_replace_line("", 0);
	}
}
