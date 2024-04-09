/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_get_path.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yatabay <yatabay@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/02 14:50:51 by jkatzenb          #+#    #+#             */
/*   Updated: 2023/10/18 19:16:25 by yatabay          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*	splits path variable into individual parts	*/
static char	**split_path(t_env *env)
{
	return (ft_split(mini_getenv("PATH", env), ':'));
}

/*	verifies if program can be found in path variable	*/
static int	verify_node_path(t_cmd *node, char **path_check)
{
	int		i;
	char	*temp;
	char	*temp2;

	i = -1;
	while (path_check[++i])
	{
		temp = ft_strjoin(path_check[i], "/");
		if (!temp)
			return (-1);
		temp2 = ft_strjoin(temp, *node->cmd);
		if (search_free(temp2, temp, 1) == -1)
			return (-1);
		if (access(temp2, F_OK) == 0)
		{
			free(temp);
			free(temp2);
			return (i);
		}
		free(temp);
		free(temp2);
		if (access(*node->cmd, F_OK) == 0)
			return (-1);
	}
	return (-2);
}

/*	checks if path is bultin	*/
static int	is_builtin(t_cmd	*node)
{
	if ((ft_strncmp(*node->cmd, "exit", sizeof(*node->cmd)) == 0)
		|| (ft_strncmp(*node->cmd, "$?", sizeof(*node->cmd)) == 0)
		|| (ft_strncmp(*node->cmd, "echo", sizeof(*node->cmd)) == 0)
		|| (ft_strncmp(*node->cmd, "cd", sizeof(*node->cmd)) == 0)
		|| (ft_strncmp(*node->cmd, "pwd", sizeof(*node->cmd)) == 0)
		|| (ft_strncmp(*node->cmd, "env", sizeof(*node->cmd)) == 0)
		|| (ft_strncmp(*node->cmd, "export", sizeof(*node->cmd)) == 0)
		|| (ft_strncmp(*node->cmd, "unset", sizeof(*node->cmd)) == 0))
		return (1);
	else
		return (0);
}

/*	finds valid path or builtin	*/
static char	*get_path(t_cmd *node, t_env *env)
{
	char	**path_check;
	int		i;

	path_check = split_path(env);
	if (!path_check[0])
		return (NULL);
	i = verify_node_path(&*node, path_check);
	if (is_builtin(&*node))
	{
		node->path = dup_or_join(*node->cmd, NULL, path_check);
		matrix_free(path_check);
		if (!node->path)
			return (NULL);
		return (node->path);
	}
	if (get_path_utils(path_check, node, i) != 0)
	{
		matrix_free(path_check);
		return (NULL);
	}
	matrix_free(path_check);
	return (node->path);
}

/*	fills out "path" in node*/
int	path_save_list(t_mini *mini)
{
	t_list	*head;
	t_list	*temp;
	t_cmd	*node;
	int		i;

	head = mini->cmds;
	temp = head;
	i = 0;
	while (1)
	{
		if (!temp->content)
			break ;
		node = temp->content;
		node->node_id = i++;
		node->path = get_path(&*node, mini->env);
		if (!node->path)
			return (-1);
		if (temp->next)
			temp = temp->next;
		else
			break ;
	}
	return (0);
}
