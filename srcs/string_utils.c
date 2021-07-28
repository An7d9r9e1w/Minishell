#include <string_utils.h>
#include <stdlib.h>

int	mstrlen(const char *str)
{
	const char *const	begin = str;

	if (!str)
		return (-1);
	while (*str)
		str++;
	return (str - begin);
}

char	*mstrdup(const char *str)
{
	char	*dup;
	char	*p;

	dup = malloc(mstrlen(str) + 1);
	if (!dup)
		return (0);
	p = dup;
	if (str)
		while (*str)
			*p++ = *str++;
	*p = 0;
	return (dup);
}

void	drop_blanks(char **str)
{
	char	*cur;

	cur = *str;
	while (*cur == ' ' || (*cur >= '\t' && *cur <= '\r'))
		cur++;
	*str = cur;
}
