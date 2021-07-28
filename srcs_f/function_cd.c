#include "function_cd.h"

int	msh_cd(char **args)
{
	char *err;

	if (args[1] == NULL)
		write(2, "msh: ожидается аргумент для \"cd\"\n", 53);
	else
	{
		if (chdir(args[1]) != 0)
		{
			err = strerror(errno);
			write(2, err, ft_strlen(err));
			write(2, "\n", 1);
		}
	}
	return (1);
}