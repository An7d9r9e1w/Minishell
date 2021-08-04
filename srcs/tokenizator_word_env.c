/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizator_word_env.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nnamor <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/31 10:04:01 by nnamor            #+#    #+#             */
/*   Updated: 2021/08/04 15:26:01 by nnamor           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <token.h>
#include <char_checkers.h>
#include <string_utils.h>
#include <cvector.h>
#include <error.h>
#include <environment.h>

static int	error_env(t_cvector *cv)
{
	cvector_free(cv);
	return (-1);
}

int	get_environment(char **line_read, t_cvector *cv,
		t_vvector *envs, int dquoted)
{
	t_cvector	*cv_env;
	char		*ch;

	ch = *line_read;
	if (!*ch || is_space(*ch))
		return (cvector_write(cv, "$", 1));
	if (*ch == '"')
		return (-(dquoted && cvector_write(cv, "$", 1) == -1));
	if (*ch >= '0' && *ch <= '9')
		return (0 & (long)(*line_read)++);
	cv_env = cvector_create();
	if (!cv_env)
		return (-1);
	while (is_word(*ch))
		if (cvector_write(cv_env, ch++, 1) == -1)
			return (error_env(cv_env));
	*line_read = ch;
	ch = get_environment_value(envs, cv_env->arr);
	cvector_free(cv_env);
	return (cvector_write(cv, ch, mstrlen(ch)));
}
