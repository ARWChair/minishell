/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_save_split_utils.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkatzenb <jkatzenb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/17 15:14:35 by yatabay           #+#    #+#             */
/*   Updated: 2023/10/18 18:59:45 by jkatzenb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*	fills temp with splitted version of cmd and adds pipes & redirs
	when neccessary	*/
int	fill_string(char **cmd, char **temp, int *i)
{
	if (i[2] != 0)
	{
		temp[i[0]] = ft_substr(cmd[i[3]], i[1], i[2] - i[1]);
		if (!temp[i[0]++])
			return (-1);
	}
	i[0] = place_symbol(cmd[i[3]], &i[2], temp, i[0]);
	if (!i[0])
		return (-1);
	i[1] = i[2];
	return (0);
}

/*	saves the symbol given by place_symbol in str and returns str
	(to temp[lines])	*/
char	*which_symbol(char *symbol, int *end, int flag)
{
	char	*str;

	str = ft_strdup(symbol);
	if (!str)
		return (NULL);
	if (flag == 1)
		(*end)++;
	return (str);
}

/*	this function looks, if the first argument of every block is an exit	*/
int	check_for_exit(t_cmd *cmds, t_list *list)
{
	int	index;

	index = 0;
	while (cmds->cmd[index])
	{
		if (!ft_strncmp(cmds->cmd[index], "exit\0", 5))
		{
			execute_exit(cmds);
			matrix_free(cmds->cmd);
			free(cmds);
			free(list);
			return (-1);
		}
		index++;
	}
	return (0);
}

/*	creates and returns a temp cmd	*/
t_cmd	*create_temp_cmd(t_list *temp)
{
	t_cmd	*return_cmd;

	while (1)
	{
		return_cmd = temp->content;
		if (cmd_kill_quotes(return_cmd->cmd) != 0)
			return (NULL);
		if (temp->next)
			temp = temp->next;
		else
			break ;
	}
	return (return_cmd);
}

/*	look for string and use matrix free on maximum 3 double pointers	*/
char	*dup_and_free(char *todup, char **m1, char **m2, char **m3)
{
	char	*new;

	new = ft_strdup(todup);
	if (!new)
	{
		if (m1 != NULL)
			matrix_free(m1);
		if (m2 != NULL)
			matrix_free(m2);
		if (m3 != NULL)
			matrix_free(m3);
		return (NULL);
	}
	return (new);
}
