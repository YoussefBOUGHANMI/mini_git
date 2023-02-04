/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   b_echo.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pschemit <pschemit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/04 13:49:54 by pschemit          #+#    #+#             */
/*   Updated: 2023/02/04 20:49:16 by pschemit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"


int	ft_is_flag_n(char *str)
{
	int	i;

	i = 0;
	if (str[i++] != '-')
		return (0);
	while (str[i])
	{
		if (str[i] != 'n')
			return (0);
		i++;
	}
	return (1);
}









void	ft_echo(t_data_mini *data)
{
	int	i;

	i = 1;
	if (data->list_cmd->list_token[i])
	{
		while (data->list_cmd->list_token[i])
		{
			if (i != 1 || ft_is_flag_n(data->list_cmd->list_token[i]) == 0)
			{
				printf("%s", data->list_cmd->list_token[i]);
				if (data->list_cmd->list_token[i + 1])
					printf(" ");
			}
			i++;
		}
		if (ft_is_flag_n(data->list_cmd->list_token[1]) != 0)
			printf("\n");
	}
	else
		printf("\n");
	exit(0);
}
