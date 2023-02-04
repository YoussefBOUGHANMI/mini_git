/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   b_export.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pschemit <pschemit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/29 14:26:09 by pschemit          #+#    #+#             */
/*   Updated: 2023/01/29 17:10:22 by pschemit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char *get_var_to_add(char   *str)
{
    char *var;
    int i;

    i = 0;
    while(str[i] && str[i]!= '=')
        i++;
    var = malloc((i + 1) * sizeof(char));
    i = 0;
    while(str[i] && str[i]!= '=')
    {
        var[i] = str[i];
        i++;
    }
    var[i] = '\0';
    return(var);
}

char **malloc_new_env_export(char **env , char *var_to_add)
{
    char    **new_env;
    char    *var_to_check;
    int i;
    int top_var_exist;
    
     i = 0;
    while(env[i])
    {
        var_to_check = get_var_to_add(env[i]);
        if(ft_strcmp(var_to_add , var_to_check) == 0)
            top_var_exist = 1;
        free(var_to_check);
        i++;
    }
    if(top_var_exist == 1)
        new_env = malloc((i + 1) * sizeof(char *));
    else 
        new_env = malloc((i + 2) * sizeof(char *));
    return(new_env);
}



int    ft_export_var_bis_1(t_data_mini *data, char **new_env , int *i , char *token)
{
    char    *var_to_add;
    char    *var_to_check;
    int     top_var_exist;


    top_var_exist = 0;
    var_to_add = get_var_to_add(token);
    while(data->env[*i])
    {
        var_to_check = get_var_to_add(data->env[*i]);
        if(ft_strcmp(var_to_add , var_to_check) == 0)
        {
            new_env[*i] = ft_strdup(token);
            top_var_exist = 1;
        }
        else
            new_env[*i] = ft_strdup(data->env[*i]);
        free(var_to_check);
        *i = *i+1;
    }
    free(var_to_add);
    return(top_var_exist);
}

void    ft_export_var_bis_2(int i ,char *token , int top_var_exist , char **new_env)
{
    if(top_var_exist == 0)
    {
        new_env[i] = ft_strdup(token);
        i++;
    }
    new_env[i] = 0;
}


void    ft_export_var(t_data_mini *data ,char *token)
{
    int     i;
    char    *var_to_add;
    char    **new_env;
    int     top_var_exist;

    i = 0;
    var_to_add = get_var_to_add(token);
    new_env = malloc_new_env_export(data->env , var_to_add);
    free(var_to_add);
    top_var_exist = ft_export_var_bis_1(data , new_env , &i , token);
    ft_export_var_bis_2(i , token , top_var_exist , new_env);
    ft_free_tab(data->env);
    data->env = new_env;
}

int  is_valid_char(char c)
{
    if((c >= '0' && c<='9'))
        return(1);
    if((c >= 'a' && c<='z'))
        return(1);    
    if((c >= 'A' && c<='Z'))
        return(1);    
    return(0);
}


int  is_only_digit(char *token)
{
    int i;

    i = 0;
    while(token[i] && token[i] != '=')
    {
        if((token[i] < '0' || token[i] > '9'))
            return(0);
        i++;
    }
    return(1);
}

int verif_token_export(char *token)
{
    int i;

    i = 0;
    if(is_only_digit(token) == 1)
    {
        printf("export: `%s': not a valid identifier \n" , token);
        return(0);
    }
    i = 0;
    while(token[i] && token[i] != '=')
    {
        if(is_valid_char(token[i]) == 0)
        {
            printf("export: `%s': not a valid identifier \n" , token);
            return(0);
        }
        i++;
    }
    return(1);
}

int *init_tab(char **env)
{
    int size;
    int *tab;

    size = 0;
    while(env[size])
        size++;
    tab = malloc((size + 1) * sizeof(int));
    size = 0;
    while(env[size])
    {
        tab[size] = size;
        size++;
    }
    return(tab);
}

int is_sort(int *tab , char **env)
{
    int i;

    i = 0;
    while(env[i] && env[i+1])
    {
        if(ft_strcmp_export(env[tab[i]] , env[tab[i + 1]]) > 0)
            return(0);
        i++;
    }
    return(1);
}

int    *sort_tab(int *tab , char **env)
{
    int i;
    int tmp;

    while(is_sort(tab,env) == 0)
    {
        i = 0;
        while(env[i] && env[i + 1])
        {
            if(ft_strcmp(env[tab[i]] , env[tab[i + 1]]) > 0)
            {
                tmp = tab[i];
                tab[i] = tab[i + 1];
                tab[i + 1] = tmp;
            }
            i++;
        }
    }
    return(tab);
}


void ft_print_var_export(char *str)
{
    int i;
    int key;

    i = 0;
    key = 0;
    printf("declare -x ");
    while(str[i])
    {
        printf("%c" , str[i]);
        if(str[i] == '=' && key == 0)
        {
            key = 1;
            printf("\"");
        }
        i++;
    }
    if(key == 1)
        printf("\"");
}

void    print_export_declare(t_data_mini *data)
{
    int *tab;
    int i;

    i = 0;
    tab = init_tab(data->env);
    tab = sort_tab(tab , data->env);
    while(data->env[i])
    {
       ft_print_var_export(data->env[tab[i]]);
       printf("\n");
       i++;
    }
    free(tab);


}

void    ft_export(t_data_mini *data)
{
    int i = 1;
    if (data->list_cmd->list_token[1] == NULL)
    {
        print_export_declare(data);
        return ;
    }
    while(data->list_cmd->list_token[i])
    {
        if(verif_token_export(data->list_cmd->list_token[i]) == 0 )
        {
            data->dollar = 1;
            return;
        }
        i++;
    }
    i = 1;
    while(data->list_cmd->list_token[i])
    {
        ft_export_var(data , data->list_cmd->list_token[i]);
        i++;
    }
    data->dollar = 0;
}