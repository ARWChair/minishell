/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkatzenb <jkatzenb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/17 14:05:58 by jkatzenb          #+#    #+#             */
/*   Updated: 2023/10/20 17:29:19 by jkatzenb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern int	g_exit_status;

char	**env_to_str(t_env *env)
{
	char	**list;
	t_env	*temp;
	int		i;

	list = ft_calloc(env_length(env) + 1, sizeof(char *));
	if (!list)
		return (NULL);
	temp = env;
	i = 0;
	while (temp)
	{
		list[i] = ft_strdup(temp->var);
		if (!list[i++])
		{
			matrix_free(list);
			return (NULL);
		}
		temp = temp->next;
	}
	list[i] = 0;
	return (list);
}

void	execute_child(t_cmd *node, t_env *env, t_mini *mini)
{
	char	**list;

	list = env_to_str(env);
	if (!list)
		return ;
	if (node->infile > 2)
	{
		dup2(node->infile, 0);
		close(node->infile);
	}
	if (node->outfile > 2)
	{
		dup2(node->outfile, 1);
		close(node->outfile);
	}
	execve(node->path, node->cmd, list);
	matrix_free(list);
	free_env(env);
	free_mini(mini);
	free(mini);
	exit(0);
}

static int	fork_child(t_cmd *node, t_cmd *node_next, t_env *env, t_mini *mini)
{
	node->pid = fork();
	if (node->pid < 0)
		return (-1);
	if (node->pid == 0)
	{
		signal_setup(CHILD);
		if (node_next && node_next->infile > 2)
			close(node_next->infile);
		if (!builtin_child_handler(&*node, &*env))
			execute_child(&*node, env, mini);
		free_env(env);
		free_mini(mini);
		free(mini);
		exit(0);
	}
	else
	{
		signal_setup(SLEEP);
		if (node->outfile > 2)
			close(node->outfile);
		if (node->infile > 2)
			close(node->infile);
	}
	return (0);
}

static int	run_program(t_list *cmds, t_env *env, t_mini *mini)
{
	t_cmd	*node;
	t_cmd	*node_next;
	int		ret;

	node = cmds->content;
	node_next = NULL;
	if (cmds->next && node->outfile == 1)
	{
		node_next = cmds->next->content;
		pipe(node->pipe_fd);
		node->outfile = node->pipe_fd[WRITE_END];
		if (node_next->infile < 3)
			node_next->infile = node->pipe_fd[READ_END];
		else
			close(node->pipe_fd[READ_END]);
	}
	ret = builtin_parent_handler(&*node, &*mini->env);
	if (ret == 2 && node->node_id == 0 && !cmds->next)
	{
		free_mini(&*mini);
		return (1);
	}
	if (ret != 0)
		return (0);
	return (fork_child(&*node, &*node_next, &*env, mini));
}

int	execute(t_mini *mini)
{
	t_list	*cmds;
	t_list	*temp;
	t_cmd	*node;
	int		ret;

	cmds = mini->cmds;
	ret = 0;
	while (cmds)
	{
		temp = cmds;
		cmds = cmds->next;
		node = temp->content;
		if (ft_strncmp(node->path, "./", 2) == 0
			&& access(node->path, F_OK) == 0)
			ret = run_program(&*temp, mini->env, &*mini);
		else if (ft_strncmp(node->path, " command not found",
				sizeof(node->path)) == 0
			&& ft_putstr_fd(" command not found\n", 2))
			g_exit_status = 127;
		else
			ret = run_program(&*temp, mini->env, &*mini);
		if (ret == 1)
			return (1);
	}
	return (wait_child(&*mini));
}
