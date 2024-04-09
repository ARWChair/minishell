/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_variables.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkatzenb <jkatzenb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/07 13:18:51 by jkatzenb          #+#    #+#             */
/*   Updated: 2023/10/19 18:54:09 by jkatzenb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern int	g_exit_status;

/*	imitates bash env	*/
void	mini_env(t_env *env, int outfile)
{
	t_env	*temp;

	if (!env)
		return ;
	temp = env;
	while (temp)
	{
		ft_putstr_fd(temp->var, outfile);
		ft_putstr_fd("\n", outfile);
		if (temp->next)
			temp = temp->next;
		else
			return ;
	}
	return ;
}

/*	finds variable in list, returns pointer to that variables node	*/
t_env	*find_var(t_env *env, char *var)
{
	int		i;
	t_env	*temp;

	i = 0;
	temp = env;
	while (temp)
	{
		i = 0;
		while (temp->var[i] != '=' && temp->var[i])
			i++;
		if (((ft_strncmp(temp->var, var, i) == 0))
			&& ((var[i] == '=') || (!var[i])))
			return (temp);
		if (temp->next)
			temp = temp->next;
		else
			return (NULL);
	}
	return (NULL);
}

/*	imitates bash export	*/
int	mini_export(t_cmd *node, t_env *env)
{
	t_env	*temp;

	if (!node->cmd[1])
		return (ft_putstr_fd(" undefined behaviour\n", 2));
	temp = find_var(env, node->cmd[1]);
	if (export_errors(node) == -1 && !temp)
		return (-1);
	if (temp == NULL)
		env_add_back(&env, node->cmd[1]);
	else
	{
		free(temp->var);
		temp->var = malloc(sizeof(char) * (ft_strlen(node->cmd[1]) + 1));
		if (!temp->var)
			return (-1);
		ft_strlcpy(temp->var, node->cmd[1], ft_strlen(node->cmd[1]) + 1);
	}
	return (0);
}

/*	mini_unset helper because line limit*/
static void	mini_unset_help(t_cmd *node, t_env *temp, t_env *prev, t_env *env)
{
	int	i;

	while (temp)
	{
		i = 0;
		while (temp->var[i] != '=' && temp->var[i])
			i++;
		if ((ft_strncmp(temp->var, node->cmd[1], i) == 0)
			&& (!node->cmd[1][i]))
		{
			if (!prev)
				env = env_delete_first(&*env);
			else if (!temp->next)
				env_delete_last(&*env);
			else
				env_delete_middle(&*env, temp);
			return ;
		}
		prev = temp;
		if (temp->next)
			temp = temp->next;
		else
			return ;
	}
}

/*	imitates bash unset	*/
void	mini_unset(t_cmd *node, t_env *env)
{
	t_env	*temp;
	t_env	*prev;

	if (!node->cmd[1])
		return ;
	temp = env;
	prev = NULL;
	if (ft_strchr(node->cmd[1], '=') != 0)
	{
		g_exit_status = 1;
		ft_putstr_fd(" not a valid identifier\n", 2);
		return ;
	}
	if (ft_strncmp(node->cmd[1], "PATH", 4) == 0
		|| ft_strncmp(node->cmd[1], "SHELL", 5) == 0)
	{
		g_exit_status = 0;
		return ;
	}
	mini_unset_help(&*node, &*temp, &*prev, &*env);
	return ;
}
