#include <readline/readline.h>
#include <readline/history.h>
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

char	*rl_gets(void)
{
	char	*line_read;

	line_read = readline("msh-1.0$ ");
	if (line_read && *line_read)
		add_history(line_read);
	return (line_read);
}

int	test_parser(t_token_stream *ts) //TEST
{
	t_token	*token;
	char	*line_read;
	char	*line_begin;
	int		token_stat;

	line_read = rl_gets();
	if (!line_read)//TEST
		return (0);//TEST
	line_begin = line_read;
	token_stat = ts_get_token(ts, &line_read, &token);
	while (!token_stat)
	{
		token_print(token);
		token_free(token);
		token_stat = ts_get_token(ts, &line_read, &token);
	}
	free(line_begin);
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

	ts = ts_create();
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
