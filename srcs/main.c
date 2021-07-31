/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nnamor <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/31 10:03:01 by nnamor            #+#    #+#             */
/*   Updated: 2021/07/31 10:03:03 by nnamor           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <sys/errno.h>//TEST

#include <token_stream.h>
#include <string_utils.h>//TEST

void	paused(void)//TEST
{
	char	c[2];

	printf("Press enter...");
	fgets(c, 2, stdin);
}

void	token_print(t_token *token)//TEST
{
	static const char *kinds[] = {"ERROR", "WORD", "QUOTE", "DQUOTE", "GREAT", "DGREAT",
		"LESS", "DLESS", "PIPE", "ENV", "AND", "OR", "WILDCARD", 0};
	static const char *values[] = {"ERROR", 0, "'", "\"", ">", ">>",
		"<", "<<", "|", "$", "&&", "||", "*", 0};

	printf("%s\t\t%s\n", kinds[token->kind],
		(token->kind == WORD) ? token->value : values[token->kind]);
}

int	test_parser(t_token_stream *ts) //TEST
{
	t_token	*token;
	int		token_stat;

	if (ts_read(ts) == -1) //TEST
		return (0);
	token_stat = ts_get_token(ts, &token);
	while (!token_stat)
	{
		token_print(token);
		token_free(token);
		token_stat = ts_get_token(ts, &token);
	}
	if (token_stat == -1)
		perror("TOKEN");
	ts_free(ts);
	return (token_stat);
}

int	main(int argc, char *argv[], char *envp[])
{
	t_token_stream	*ts;
//	t_token	*tokens[256];
	(void)argc;
	(void)argv;
	(void)envp;

	ts = ts_create("msh-1.0$ ");
	if (!ts)
	{
		perror("Token_stream:");//TEST
		return (1);
	}
	//while (1)
	//{
		if (test_parser(ts) == -1)//TEST
			perror("TEST"); //TEST
	//}
	paused();
	return (0);
}
