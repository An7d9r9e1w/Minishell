#include "../incs/function_env.h"
#include "../incs/vvector.h"

int msh_env(char **args, t_vvector *env)
{
	(void)args;
	unsigned int i;

	mqsort(env->arr, env->size, sizeof(void *), ft_strcmp);
	i = 0;
	while (i < env->size)
	{
		printf("%s\n", (char *)env->arr[i]);
		i++;
	}
	return (1);
}