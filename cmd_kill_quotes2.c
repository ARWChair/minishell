/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_kill_quotes2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yatabay <yatabay@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/17 20:02:02 by yatabay           #+#    #+#             */
/*   Updated: 2023/10/17 20:05:33 by yatabay          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_str(char *str, char *temp)
{
	if (!str)
	{
		str = ft_strdup(temp);
		if (search_free(str, temp, 1) != 0)
			return (-1);
	}
	else
	{
		str = join_and_free(&str, temp);
		if (search_free(str, temp, 1) != 0)
			return (-1);
	}
	return (0);
}

char	*create_temp(char **cmd, char *str, int line, int *end)
{
	char	*temp;

	if (cmd[line][*end] == '\"')
	{
		temp = get_quote(cmd[line], end, '\"');
		if (search_free(temp, str, 1) != 0)
			return (NULL);
	}
	else if (cmd[line][*end] == '\'')
	{
		temp = get_quote(cmd[line], end, '\'');
		if (search_free(temp, str, 1) != 0)
			return (NULL);
	}
	else
	{
		temp = no_quote(cmd[line], end);
		if (search_free(temp, str, 1) != 0)
			return (NULL);
	}
	return (temp);
}

int	dfree(char **cmd, int *line, char *str)
{
	free(cmd[*line]);
	cmd[*line] = ft_strdup(str);
	if (!cmd[*line])
	{
		matrix_free(cmd);
		return (-1);
	}
	free(str);
	return (0);
}

int	cmd_kill_quotes_loop(char **cmd, char **str, int line, int end)
{
	char	*temp;

	while (cmd[line][++end])
	{
		temp = create_temp(cmd, *str, line, &end);
		if (!*str)
		{
			*str = ft_strdup(temp);
			if (search_free(*str, temp, 1) != 0)
				return (-1);
		}
		else
		{
			*str = join_and_free(str, temp);
			if (search_free(*str, temp, 1) != 0)
				return (-1);
		}
		if (temp)
			free(temp);
		if (!cmd[line][end])
			break ;
	}
	return (0);
}
