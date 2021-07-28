#include <char_checkers.h>

int	is_space(char c)
{
	return (c == ' ' || (c >= '\t' && c <= '\r'));
}

int	is_spec(char c)
{
	return (c == '<' || c == '>' || c == '|' || c == '&' || c == '"'
		|| c == '\'' || c == '$' || c == '*');
}

int	is_word(char c)
{
	return ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z')
		|| (c >= '0' && c <= '9') || c == '_');
}

