#include "../headers/parser_env.h"

t_list	*ft_lstnew(char *content)
{
	t_list	*list;

	list = (t_list *)malloc(sizeof(t_list));
	if (!list)
		return (0);
	list->content = content;
	list->next = 0;
	return (list);
}

t_list *get_env(char **env)
{
	t_list *list;
	int i;

	i = 1;
	list = ft_lstnew(env[0]);
	if (!list)
		return (0);
	while (env[i])
	{
		list->next = ft_lstnew(env[i]);
		if (!list->next)
			return (0);
		list = list->next;
	}
	return (t_list);
}