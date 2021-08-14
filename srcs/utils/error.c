/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nnamor <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/31 15:01:41 by nnamor            #+#    #+#             */
/*   Updated: 2021/08/14 09:00:03 by nnamor           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <sys/errno.h>
#include <string.h>

#include <error.h>
#include <string_utils.h>

#define EFULLBUF_M "attempt to put a token to a full buffer "
#define EEND_M "syntax error: unexpected end of file "
#define EBADTOKEN_M "syntax error near unexpected token `"
#define EQUOTE_M "unexpected EOF while looking for matching `"
#define ENOCMD_M "command not found"

static void	error_msg(int err, char *add_msg)
{
	static char	*msgs[] = {"", EFULLBUF_M, EEND_M, EBADTOKEN_M, EQUOTE_M,
		ENOCMD_M};
	char		*msg;

	if (err == -1)
		msg = strerror(errno);
	else if (err > 0 && err < (int)(sizeof(msgs)))
		msg = msgs[err];
	else
		msg = "Undefined error";
	write(2, "minishell: ", 11);
	write(2, msg, mstrlen(msg));
	if (*add_msg)
	{
		if (err != EBADTOKEN && err != EQUOTE)
			write(2, ": ", 2);
		write(2, add_msg, mstrlen(add_msg));
	}
	if (err == EBADTOKEN || err == EQUOTE)
		write(2, "'", 1);
	write(2, "\n", 1);
}

int	error(int err_n, char *add_msg, int print)
{
	static int			err = 0;
	static char			buf[256];

	if (err_n < -1)
		return (err);
	if (print)
	{
		if (add_msg)
			mstrlcpy(buf, add_msg, 256);
		if (err_n && err_n > -2)
			error_msg(err_n, buf);
		else
			error_msg(err, buf);
		err = 0;
		*buf = '\0';
		if (errno)
			return (errno);
		return (1);
	}
	err = err_n;
	if (add_msg)
		mstrlcpy(buf, add_msg, 256);
	return (-1);
}

void	*error_p(int err_n)
{
	error(err_n, 0, 0);
	return (0);
}
