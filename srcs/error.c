/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nnamor <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/31 15:01:41 by nnamor            #+#    #+#             */
/*   Updated: 2021/08/01 07:03:08 by nnamor           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <sys/errno.h>
#include <string.h>

#include <error.h>
#include <string_utils.h>

#define EFULLBUF_M "attempt to put a token to a full buffer"
#define EEND_M "syntax error: unexpected end of file"

static void	error_msg(int err, char *add_msg)
{
	static const char	*msgs[] = {"", EFULLBUF_M, EEND_M, "TEST ERROR"};
	char				*msg;

	if (err == -1)
		msg = strerror(errno);
	else if (err > 0 && err < (int)(sizeof(msgs)))
		msg = msgs[err];
	else
		msg = "Undefined error";
	write(2, "minishell: ", 11);
	write(2, msg, mstrlen(msg));
	if (*add_msg)
		write(2, add_msg, mstrlen(add_msg));
	write(2, "\n", 1);
}

int	error(int err_n, char *add_msg, int print)
{
	static int			err = 0;
	static int			buf[256];

	if (print)
	{
		error_msg(err, buf);
		err = 0;
		*add_msg = 0;
		return (0);
	}
	err = err_n;
	if (additional_msg)
	{
		*buf = ' ';
		mstrlcpy(buf + 1, add_msg, 255);
	}
	return (-1);
}

void	*error_void(int err_n)
{
	error(err_n, 0, 0);
	return (0);
}
