/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_get_path_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkatzenb <jkatzenb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/17 18:39:36 by yatabay           #+#    #+#             */
/*   Updated: 2023/10/18 19:51:13 by jkatzenb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*	This function can duplicate or join a string
	To Dup: input (string, NULL, NULL)
	To Join: input (string, string2, NULL)
	to free and array: (..., ..., to_free)	*/
char	*dup_or_join(char *first, char *second, char **to_free)
{
	char	*new;

	if (!second)
	{
		new = ft_strdup(first);
		if (!new)
		{
			if (to_free)
				matrix_free(to_free);
			return (NULL);
		}
	}
	else
	{
		new = ft_strjoin(first, second);
		if (!new)
		{
			if (to_free && to_free[0])
				matrix_free(to_free);
			return (NULL);
		}
	}
	return (new);
}

/*	extents the get_path function	*/
int	get_path_utils(char **path_check, t_cmd *node, int i)
{
	char	*temp;

	if (i != -1 && i != -2)
	{
		temp = dup_or_join(path_check[i], "/", path_check);
		if (!temp)
			return (-1);
		node->path = dup_or_join(temp, *node->cmd, path_check);
		free(temp);
		if (!node->path)
			return (-1);
	}
	else if (i == -1)
	{
		node->path = dup_or_join(*node->cmd, NULL, path_check);
		if (!node->path)
			return (-1);
	}
	else
	{
		node->path = dup_or_join(" command not found", NULL, path_check);
		if (!node->path)
			return (-1);
	}
	return (0);
}
