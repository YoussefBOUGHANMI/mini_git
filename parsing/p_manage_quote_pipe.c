/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   p_manage_quote_pipe.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pschemit <pschemit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/15 15:42:26 by pschemit          #+#    #+#             */
/*   Updated: 2023/02/05 19:02:17 by pschemit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"../minishell.h"

void	manage_quote_err(t_data_mini *data)
{
	static char	*suite = (char *) NULL;
	char		*new_cmd;

	if (suite)
	{
		free(suite);
		suite = (char *) NULL;
	}
	if (data->keypipe == 1)
	{	
		termios(0);
		suite = readline("pipe quote>");
		termios(1);
	}
	else
	{
		termios(0);
		suite = readline("quote>");
		termios(1);
	}
	new_cmd = ft_strjoin_3(data->cmd, "\n", suite);
	free(data->cmd);
	data->cmd = new_cmd;
}

void	manage_pipe(t_data_mini *data)
{
	static char	*suite = (char *) NULL;
	char		*new_cmd;

	if (suite)
	{
		free(suite);
		suite = (char *) NULL;
	}
	termios(0);
	suite = readline("pipe>");
	termios(1);
	new_cmd = ft_strjoin(data->cmd, suite);
	free(data->cmd);
	data->cmd = new_cmd;
	data->keypipe = 1;
}
