/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yatabay <yatabay@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/13 14:17:50 by jkatzenb          #+#    #+#             */
/*   Updated: 2023/10/16 16:46:22 by yatabay          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern int	g_exit_status;

/*	replaces pwd and old_pwd variables*/
void	update_pwd(t_env *env)
{
	t_env	*pwd;
	t_env	*old;
	char	*temp;

	pwd = find_var(env, "PWD");
	old = find_var(env, "OLDPWD");
	free(old->var);
	temp = ft_strdup(pwd->var);
	old->var = ft_strjoin("OLD", temp);
	free(temp);
	free(pwd->var);
	temp = getcwd(NULL, 0);
	pwd->var = ft_strjoin("PWD=", temp);
	free(temp);
}

void	mini_dollarq(t_cmd *node)
{
	int	status;

	status = g_exit_status;
	if (WIFEXITED(status))
		status = WEXITSTATUS(g_exit_status);
	ft_putnbr_fd(status, node->outfile);
	return ;
}

/*	allows mini cd to use '~'	*/
void	mini_cd_home(char *path, char *append, t_env *env)
{
	path = ft_strjoin(getenv("HOME"), append);
	if ((chdir(path)) == -1)
		ft_putstr_fd(" no such file or directory\n", 2);
	else
		update_pwd(&*env);
	free(path);
	return ;
}

/* executes exit with codes */
int	execute_exit(t_cmd *node)
{
	int	status;
	int	i;

	i = 0;
	status = g_exit_status;
	while (node->cmd[i])
		i++;
	if (node->cmd[1])
		status = ft_atoi(node->cmd[1]);
	if (i > 2 && ft_putstr_fd(" too many arguments\n", 2))
		status = 1;
	if (node->cmd[1] && !ft_isdigit(node->cmd[1][0]) &&
		node->cmd[1][0] != '-' && node->cmd[1][0] != '+' &&
		ft_putstr_fd(" numeric argument required\n", 2))
		status = 2;
	while (status > 255)
		status -= 256;
	while (status < 0)
		status += 256;
	g_exit_status = status;
	return (-1);
}
