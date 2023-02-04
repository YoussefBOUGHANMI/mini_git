/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage_dollar_2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pschemit <pschemit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/04 16:09:40 by pschemit          #+#    #+#             */
/*   Updated: 2023/02/04 17:45:40 by pschemit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"../minishell.h"

void	initial_vars(int *i, int *ii, char *new_cmd)
{
	*i = 0;
	*ii = 0;
	new_cmd = NULL;
}

void	manage_dollar_interog(t_data_mini *data)
{
	int		i;
	int		ii;
	int		iii;
	char	*new_cmd;
	char	*nb;

	i = 0;
	ii = 0;
	new_cmd = malloc((ft_strlen(data->cmd) * 2 + 1) * sizeof(char));
	while (data->cmd[i])
	{
		if (data->cmd[i] == '$' && data->cmd[i + 1] == '?')
		{
			iii = 0;
			i = i + 2;
			nb = ft_itoa(data->dollar);
			while (nb[iii])
			new_cmd[ii++] = nb[iii++];
			free(nb);
		}
		new_cmd[ii++] = data->cmd[i++];
	}
	new_cmd[ii] = 0;
	free(data->cmd);
	data->cmd = new_cmd;
}

void	end_manage_dollar(t_data_mini *data, char *tmp, char *new_cmd, int ii)
{
	char	*res;

	tmp[ii] = '\0';
	res = ft_strjoin(new_cmd, tmp);
	free(tmp);
	free(new_cmd);
	free(data->cmd);
	data->cmd = res;
}

void	manage_dollar(t_data_mini *data)
{
	int		i;
	int		ii;
	char	*new_cmd;
	char	*tmp;

	i = 0;
	ii = 0;
	new_cmd = NULL;
	manage_dollar_interog(data);
	tmp = malloc((ft_strlen(data->cmd) + 1) * sizeof(char));
	initial_vars(&i, &ii, new_cmd);
	while (data->cmd[i])
	{
		if (data->cmd[i] == '$' )
		{
			tmp[ii] = '\0';
			ii = 0;
			new_cmd = ft_strjoin_33(new_cmd, tmp, \
				get_new_value(get_var(&data->cmd[i], &i), data->env));
		}
		else
			tmp[ii++] = data->cmd[i];
		i++;
	}
	end_manage_dollar(data, tmp, new_cmd, ii);
}
