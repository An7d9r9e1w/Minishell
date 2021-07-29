#include <readline/readline.h>
#include <readline/history.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/errno.h>//TEST

#include <token.h>
#include <string_utils.h>//TEST

void	paused(void)//TEST
{
	char	c[2];

	printf("Press enter...");
	fgets(c, 2, stdin);
}

char	*rl_gets(void)
{
	char	*line_read;

	line_read = readline("msh-1.0$ ");
	if (line_read && *line_read)
		add_history(line_read);
	return (line_read);
}

void	test_parser(t_token **tokens) //TEST
{
	char	*line_read;
	char	*line_begin;
	int		i;

	line_read = rl_gets();
	if (!line_read)//TEST
		return ;//TEST
	line_begin = line_read;
	//printf("line=%s\n", line_read);//TEST
	*tokens = get_token(&line_read);
	i = 0;
	//printf("%2d. %s %p\n", i, line_read, *tokens);//TEST
	while (tokens[i++])
	{
		//printf("token=%s %d\n", tokens[i]->value, tokens[i]->kind);//TEST
		tokens[i] = get_token(&line_read);
		//printf("%2d. %s\n", i, line_read);//TEST
	}
	//tokens[i] = 0;
	free(line_begin);
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

int	main(int argc, char *argv[], char *envp[])
{
	t_token	*tokens[256];
	(void)argc;
	(void)argv;
	(void)envp;

	//while (1)
	//{
		test_parser(tokens); //TEST
		for (int i = 0; tokens[i]; i++)//TEST
		{
			token_print(tokens[i]);//TEST
			token_free(tokens[i]);//TEST
		}
	//}
	paused();
	return (0);
}
