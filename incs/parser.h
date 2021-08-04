/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nnamor <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/31 10:02:03 by nnamor            #+#    #+#             */
/*   Updated: 2021/08/03 18:18:07 by nnamor           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

# include <command_list.h>
# include <cmd_assembler.h>
# include <token_stream.h>

t_command_list	*parse_line_read(t_cmd_assembler *asmr, t_token_stream *ts);

#endif	/*PARSER_H*/
