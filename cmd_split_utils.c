/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_split_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkatzenb <jkatzenb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/31 18:20:48 by jkatzenb          #+#    #+#             */
/*   Updated: 2023/10/20 18:30:55 by jkatzenb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern int	g_exit_status;

int	validate_input(char *str)
{
	int	i;
	int	q;

	i = -1;
	q = 0;
	while (str[++i])
	{
		if (q == 0 && (str[i] == '\'' || str[i] == '\"'))
			q = str[i] % 2 + 1;
		else if (q != 0 && (str[i] == '\'' || str[i] == '\"'))
		{
			if (q == str[i] % 2 + 1)
				q = 0;
		}
	}
	q = validate_pipes(str);
	if (q)
		ft_putstr_fd(" incomplete input\n", 2);
	return (q);
}

/*	initializes cmd struct (node in commands list)	*/
t_cmd	*init_cmd(void)
{
	t_cmd	*cmds;

	cmds = malloc(sizeof(t_cmd));
	if (!cmds)
		return (NULL);
	cmds->cmd = NULL;
	cmds->path = NULL;
	cmds->infile = STDIN_FILENO;
	cmds->outfile = STDOUT_FILENO;
	cmds->pid = 0;
	cmds->node_id = 0;
	return (cmds);
}

/*	prints contents of all nodes in list for testing purposes	*/
void	print_list(t_mini *mini)
{
	int		i;
	t_list	*temp;
	t_cmd	*node;

	temp = mini->cmds;
	while (temp->content)
	{
		printf("\n");
		node = temp->content;
		if (!node)
			break ;
		i = 0;
		if (node->cmd && node->cmd[i])
			printf("cmd:\t%s\n", node->cmd[i++]);
		while (node->cmd && node->cmd[i])
			printf("\t%s\n", node->cmd[i++]);
		if (node->path)
			printf("path:\t%s\n", node->path);
		printf("in: %d, out: %d, nid: %d\n",
			node->infile, node->outfile, node->node_id);
		if (temp->next)
			temp = temp->next;
		else
			break ;
	}
}

char	*remq(char *cmd)
{
	char	*new;
	int		start;
	int		end;

	end = 0;
	while (cmd[end])
		end++;
	if (!((cmd[end - 1] == '"' && cmd[0] == '"')
			|| (cmd[end - 1] == '\'' && cmd[0] == '\'')))
		return (cmd);
	new = (char *)malloc(end - 1);
	if (!new)
		return (NULL);
	start = 0;
	while (start < end - 2)
	{
		new[start] = cmd[start + 1];
		start++;
	}
	new[start] = 0;
	return (new);
}

/*	finds file descriptor	*/
int	find_fd(int oldfd, char *cmd, int flag)
{
	int		fd;
	char	*opens;

	opens = remq(cmd);
	fd = 0;
	if (oldfd > 2)
		close(oldfd);
	if (!cmd || !opens)
		return (-999999);
	if (flag == OUT_TRUNC)
		fd = open(opens, O_CREAT | O_WRONLY | O_TRUNC, 0644);
	else if (flag == OUT_APPEND)
		fd = open(opens, O_CREAT | O_WRONLY | O_APPEND, 0644);
	else if (flag == INPUT)
	{
		fd = open(opens, O_RDONLY);
		if (fd < 0)
		{
			g_exit_status = 1;
			ft_putstr_fd(" No such file or directory\n", 2);
		}
	}
	return (fd);
}
