#include <stdlib.h>

#include <token.h>
#include <char_checkers.h>
#include <string_utils.h>
#include <cvector.h>

static char	*get_env_value(char *env)//TEST
{
	return (mstrcat(mstrcat(mstrdup("\"VALUE_OF_"), env, mstrlen(env)), "\"", 1));
}

int	get_environment(char **line_read, t_cvector *cv)//TEST
{
	t_cvector	*cv_env;
	char		*ch;

	ch = *line_read;
	if (*ch >= '0' && *ch <= '9')
	{
		(*line_read)++;
		return (0);
	}
	cv_env = cvector_create();
	if (!cv_env)
		return (-1);
	while (is_word(*ch))
	{
		if (cvector_write(cv_env, ch++, 1) == -1)
		{
			cvector_free(cv_env);
			return (-1);
		}
	}
	*line_read = ch;
	ch = get_env_value(cv_env->arr);//TEST
	cvector_free(cv_env);
	int	test = cvector_write(cv, ch, mstrlen(ch));//TEST
	free(ch);//TEST
	return (test);//TEST
	//return (cvector_write(cv, ch, mstrlen(ch)));
}
