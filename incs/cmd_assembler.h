/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_assembler.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nnamor <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/03 14:02:41 by nnamor            #+#    #+#             */
/*   Updated: 2021/08/03 14:02:43 by nnamor           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CMD_ASSEMBLER_H
# define CMD_ASSEMBLER_H

# include <command_list.h>
# include <token.h>
# include <vvector.h>

typedef struct s_cmd_assembler
{
	t_vvector	*pipes;
	t_vvector	*commands;
	t_vvector	*args;
	t_vvector	*in;
	t_vvector	*out;
}	t_cmd_assembler;

t_cmd_assembler	*cmd_assembler_create(void);
int				cmd_assembler_cmd_edit(t_cmd_assembler *asmr, t_token *token);
int				cmd_assembler_cmd_new(t_cmd_assembler *asmr);
int				cmd_assembler_pipeline_new(t_cmd_assembler *asmr);
t_command_list	*cmd_assembler_make(t_cmd_assembler *asmr);
void			cmd_assembler_free(t_cmd_assembler *asmr);

#endif	/*CMD_ASSEMBLER_H*/
