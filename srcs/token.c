#include <stdlib.h>

#include <token.h>

t_token	*token_create(char *value, t_kind kind)
{
	t_token	*token;

	token = malloc(sizeof(t_token));
	if (!token)
	{
		if (value)
			free(value);
		return (0);
	}
	token->value = value;
	token->kind = kind;
	return (token);
}

void	token_free(t_token *token)
{
	if (token)
	{
		if (token->value)
			free(token->value);
		free(token);
	}
}
