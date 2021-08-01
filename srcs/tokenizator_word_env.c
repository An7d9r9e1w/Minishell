/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizator_word_env.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nnamor <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/31 10:04:01 by nnamor            #+#    #+#             */
/*   Updated: 2021/07/31 16:24:14 by nnamor           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

#include <token.h>
#include <char_checkers.h>
#include <string_utils.h>
#include <cvector.h>
#include <error.h>

static char	*get_env_value(char *env)//TEST
{
	return (mstrcat(mstrcat(mstrdup("\"VALUE_OF_"), env, mstrlen(env)), "\"", 1));
}

static int	error_env(t_cvector *cv)
{
	cvector_free(cv);
	return (-1);
}

int	get_environment(char **line_read, t_cvector *cv)//TEST
{
	t_cvector	*cv_env;
	char		*ch;

	ch = *line_read;
	if (*ch >= '0' && *ch <= '9')
		return (0 & (long)(*line_read)++);
	cv_env = cvector_create();
	if (!cv_env)
		return (-1);
	while (is_word(*ch))
		if (cvector_write(cv_env, ch++, 1) == -1)
			return (error_env(cv_env));
	*line_read = ch;
	ch = get_env_value(cv_env->arr);//TEST
	cvector_free(cv_env);
	int	test = cvector_write(cv, ch, mstrlen(ch));//TEST
	free(ch);//TEST
	return (test);//TEST
	//return (cvector_write(cv, ch, mstrlen(ch)));
}
