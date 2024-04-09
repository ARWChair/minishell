/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yatabay <yatabay@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/28 15:13:58 by moth              #+#    #+#             */
/*   Updated: 2023/10/18 19:23:33 by yatabay          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern int	g_exit_status;

static void	check_exits(bool *printed, int status)
{
	int	sig;

	if (WIFEXITED(status))
	{
		if (WEXITSTATUS(status))
			g_exit_status = WEXITSTATUS(status);
	}
	else if (WIFSIGNALED(status))
	{
		sig = WTERMSIG(status);
		if (__WCOREDUMP(status) && *printed)
		{
			ft_putstr_fd("Quit(core dumped)", 2);
			*printed = !(*printed);
		}
		else if (sig == SIGINT && *printed)
		{
			ft_putstr_fd("\n", 1);
			*printed = !(*printed);
		}
		g_exit_status = 128 + sig;
	}
}

/*	verifies if program can be found in path variable	*/
int	verify_path(char **path, t_cmd *node)
{
	int	i;

	i = 0;
	while (path[i])
	{
		if (access(ft_strjoin(ft_strjoin(path[i], "/"),
					node->path), F_OK) == 0 || access(node->path, F_OK) == 0)
			return (i);
		i++;
	}
	return (-1);
}

int	wait_child(t_mini *mini)
{
	t_list	*cmds;
	t_list	*temp;
	t_cmd	*node;
	int		status;
	bool	found;

	cmds = mini->cmds;
	found = true;
	while (cmds)
	{
		temp = cmds;
		cmds = cmds->next;
		node = temp->content;
		if (node->pid != 0)
		{
			if (waitpid(node->pid, &status, 0) == -1)
				perror("Wait-child failed at waitpid");
			check_exits(&found, status);
		}
	}
	return (0);
}
