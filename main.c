#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <dirent.h>

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

int msh_echo(char **args)
{
	int i;

	i = 0;
	while(args[i])
		i++;
	if (i == 1)
		write(2, "msh: ожидается аргумент для \"echo\"\n", 55);
	else if (i == 2)
	{
		if (!strcmp(args[1], "-n"))
			return (0);
		else
			printf("%s\n", args[1]);
	}
	else
	{
		if (!strcmp(args[1], "-n"))
			printf("%s", args[2]);
		else
		{
			perror("msh");
			return (0);
		}
	}
	return (1);
}

int msh_pwd(char **args)
{
	char str[100];

	if (getcwd(str, 100) == NULL)
		perror("msh");
	else
		printf("%s\n", str);
	return (1);
}

//int msh_export(char **args)
//{
//
//}
//int msh_unset(char **args)
//{
//
//}
int msh_env(char **args, char **env)
{
	while (*env)
	{
		printf("%s\n", *env);
		env++;
	}
	return (1);
}

int main(int argc, char **argv, char **env)
{
	msh_env(argv, env);
	(void)argc;
	return 0;
}