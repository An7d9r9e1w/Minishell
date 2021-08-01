#include "../headers/function_pwd.h"

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