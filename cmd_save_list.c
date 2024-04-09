/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_save_list.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkatzenb <jkatzenb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/15 19:09:03 by jkatzenb          #+#    #+#             */
/*   Updated: 2023/10/20 18:51:21 by jkatzenb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern int	g_exit_status;

/*	adds currentl line to node	*/
char	**add_current_line(char *line, char **cmd)
{
	int		i;
	char	**new;

	i = 0;
	while (cmd && cmd[i])
		i++;
	new = (char **)malloc((i + 2) * sizeof(char *));
	if (!new)
		return (NULL);
	i = 0;
	while (cmd && cmd[i])
	{
		new[i] = dup_and_free(cmd[i], cmd, new, NULL);
		if (!new[i])
			return (NULL);
		free(cmd[i]);
		i++;
	}
	free(cmd);
	new[i] = dup_and_free(line, cmd, new, NULL);
	if (!new[i])
		return (NULL);
	new[++i] = 0;
	return (new);
}

/*	finds outfile	*/
int	find_outfile(t_cmd *node, char **cmd, int *i, int redir)
{
	int	fd;

	(*i)++;
	if (redir == OUT_TRUNC)
		fd = find_fd(node->outfile, cmd[*i], OUT_TRUNC);
	else if (redir == OUT_APPEND)
		fd = find_fd(node->outfile, cmd[*i], OUT_APPEND);
	else
		fd = 1;
	return (fd);
}

/*	finds infile	*/
int	find_infile(t_cmd *node, char **cmd, int *i)
{
	int	fd;

	(*i)++;
	fd = find_fd(node->outfile, cmd[*i], INPUT);
	return (fd);
}

/*	fills nodes of linked list	*/
t_cmd	*fill_node(t_cmd *node, char **cmd, int i, t_env *env)
{
	if (cmd[i][0] == '<' && cmd[i][1] == '<')
	{
		node->infile = find_heredoc_fd(cmd[i + 1], env);
		waitpid(-1, &g_exit_status, 0);
	}
	else if (cmd[i][0] == '<')
		node->infile = find_infile(&*node, cmd, &i);
	else if (cmd[i][0] == '>' && cmd[i][1] == '>')
		node->outfile = find_outfile(&*node, cmd, &i, OUT_APPEND);
	else if (cmd[i][0] == '>')
		node->outfile = find_outfile(&*node, cmd, &i, OUT_TRUNC);
	else if (cmd[i][0] && cmd[i][0] != '|' && (i == 0
		|| (cmd[i - 1][0] != '<' && cmd[i - 1][0] != '>')))
	{
		node->cmd = add_current_line(cmd[i], &*node->cmd);
		if (!node->cmd)
			return (NULL);
	}
	if (node->infile == -999999 || node->outfile == -999999)
		return (NULL);
	return (node);
}

/*	saves input into linked list	*/
t_list	*cmd_save_list(char **cmd, t_env *env)
{
	t_list	*cmds[3];
	t_cmd	*check;
	int		i;

	cmds[0] = NULL;
	i = 0;
	while (cmd[i])
	{
		if ((i == 0) || (cmd[i][0] == '|' && cmd[i + 1] && cmd [i + 1][0]))
			ft_lstadd_back(&cmds[0], ft_lstnew(init_cmd()));
		cmds[1] = ft_lstlast(&*cmds[0]);
		if (!cmds[1])
			return (NULL);
		cmds[1]->content = fill_node(cmds[1]->content, cmd, i, env);
		if (!cmds[1]->content)
			return (NULL);
		i++;
	}
	cmds[2] = cmds[0];
	check = create_temp_cmd(cmds[2]);
	if (check == NULL)
		return (NULL);
	if (check_for_exit(check, cmds[2]) != 0)
		return (NULL);
	return (cmds[0]);
}
