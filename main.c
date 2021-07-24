#include <stdio.h>
#include <unistd.h>

int main()
{
	write(2, "msh: ожидается аргумент для \"cd\"\n", 53);
	return 0;
}

int	msh_cd(char **args)
{
	if (args[1] == NULL)
		write(2, "msh: ожидается аргумент для \"cd\"\n", 53);
	else
	{
		if (chdir(args[1]) != 0)
			perror("msh");
	}
	return (1);
}

int msh_exit(char **args)
{
	return (0);
}

msh_echo(-n), msh_pwd, msh_export, msh_unset, msh_env
