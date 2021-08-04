#include "../incs/vvector.h"
char	*mstrdup(const char *str);

t_vvector *get_env(char **env)
{
	t_vvector *my_env;
	int i;
	char *str;

	i = 0;
	my_env = vvector_create();
	while (env[i])
	{
		str = mstrdup(env[i]);
		vvector_put(my_env, str);
		i++;
	}
	return (my_env);
}