/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nnamor <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/31 10:02:03 by nnamor            #+#    #+#             */
/*   Updated: 2021/07/31 10:02:08 by nnamor           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

#include <command_list.h>

t_command_list	*parse_line_read(t_token_stream *ts, char **line_read);

#endif	/*PARSER_H*/
