/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage_redir_in_2.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pschemit <pschemit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/04 17:50:36 by pschemit          #+#    #+#             */
/*   Updated: 2023/02/04 18:17:58 by pschemit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_op_cl_p_red(t_cmd *cmd, int i, int nb_cmd)
{
	if (nb_cmd == 1)
		close_all_pipe(cmd, i);
	if (cmd->redir_out == 1)
		dup2(cmd->fd_out, 1);
	if (cmd->redir_in == 1)
		dup2(cmd->fd_in, 0);
}

void	ft_open_close_pipe_red(t_cmd *cmd, int i, int nb_cmd)
{
	ft_op_cl_p_red(cmd, i, nb_cmd);
	if (i == 0 && nb_cmd != 1)
	{
		if (cmd->redir_out != 1)
			dup2(cmd->fd[1], 1);
		close_all_pipe(cmd, i);
	}
	else if (i == nb_cmd - 1)
	{
		if (cmd->redir_in != 1)
			dup2(cmd->before->fd[0], 0);
		close_all_pipe(cmd, i);
	}
	else if (nb_cmd != 1)
	{
		if (cmd->redir_in != 1)
			dup2(cmd->before->fd[0], 0);
		if (cmd->redir_out != 1)
			dup2(cmd->fd[1], 1);
		close_all_pipe(cmd, i);
	}
}
