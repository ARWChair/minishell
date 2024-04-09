/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkatzenb <jkatzenb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/07 13:13:59 by jkatzenb          #+#    #+#             */
/*   Updated: 2023/10/18 20:19:56 by jkatzenb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern int	g_exit_status;

/*	prints current directory	*/
void	print_dir(int outfile)
{
	char	*cwd;

	cwd = getcwd(NULL, 0);
	ft_putstr_fd(cwd, outfile);
	ft_putstr_fd("\n", outfile);
	free(cwd);
}

/*	imitates bash echo	*/
void	mini_echo(t_cmd *node)
{
	int	i;
	int	nl_check;

	i = 1;
	nl_check = 0;
	if (!node->cmd[i])
		return ;
	if (ft_strncmp(node->cmd[i], "-n", sizeof(node->cmd[i])) == 0)
		nl_check = i++;
	if (node->cmd[i])
	{
		while (node->cmd[i])
		{
			if ((nl_check == 0 && i != 1) || (nl_check == 1 && i != 2))
				ft_putstr_fd(" ", 1);
			ft_putstr_fd(node->cmd[i++], 1);
		}
	}
	if (nl_check == 0)
		ft_putstr_fd("\n", 1);
	g_exit_status = 0;
	return ;
}

/*	imitates bash cd	*/
void	mini_cd(char **input, t_env *env)
{
	int		i;
	char	*path;

	i = 1;
	path = NULL;
	if (!input[i])
	{
		mini_cd_home(&*path, "/", &*env);
		return ;
	}
	if (input[i + 1])
	{
		g_exit_status = 1;
		ft_putstr_fd(" too many arguments\n", 2);
		return ;
	}
	if ((chdir(input[i])) == -1)
	{
		g_exit_status = 1;
		ft_putstr_fd(" No such file or directory\n", 2);
	}
	else
		update_pwd(&*env);
	return ;
}

/*	executes builtins for the parent	*/
int	builtin_parent_handler(t_cmd *node, t_env *env)
{
	if (ft_strncmp(node->path, "cd", sizeof(node->path)) == 0)
		mini_cd(node->cmd, &*env);
	else if (ft_strncmp(node->path, "export", sizeof(node->path)) == 0)
		mini_export(&*node, &*env);
	else if (ft_strncmp(node->path, "unset", sizeof(node->path)) == 0)
		mini_unset(&*node, &*env);
	else
		return (0);
	return (1);
}

/*	executes bultins for childs	*/
int	builtin_child_handler(t_cmd *node, t_env *env)
{
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
	if (ft_strncmp(node->path, "$?", sizeof(node->path)) == 0)
		mini_echo(&*node);
	else if (ft_strncmp(node->path, "echo", sizeof(node->path)) == 0)
		mini_echo(&*node);
	else if (ft_strncmp(node->path, "pwd", sizeof(node->path)) == 0)
		print_dir(1);
	else if (ft_strncmp(node->path, "env", sizeof(node->path)) == 0)
		mini_env(&*env, 1);
	else
		return (0);
	return (1);
}
