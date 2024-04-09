/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_list_2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkatzenb <jkatzenb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/17 13:22:30 by jkatzenb          #+#    #+#             */
/*   Updated: 2023/04/13 14:12:38 by jkatzenb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*	delete first element in list */
t_env	*env_delete_first(t_env *env)
{
	t_env	*temp;

	temp = env;
	env = env->next;
	free(temp->var);
	free(temp);
	return (env);
}

/*	delete last element in list */
void	env_delete_last(t_env *env)
{
	t_env	*temp;

	temp = env;
	while (temp->next)
	{
		env = temp;
		temp = temp->next;
	}
	free(env->next->var);
	free(env->next);
	env->next = NULL;
	return ;
}

/*	delete element in middle of list	*/
void	env_delete_middle(t_env *env, t_env *del)
{
	t_env	*temp;

	temp = env;
	while (temp)
	{
		if (temp->next == del)
		{
			temp->next = temp->next->next;
			free(del->var);
			free(del);
			return ;
		}
		if (temp->next)
			temp = temp->next;
		else
			return ;
	}
}

static char	*get_value(char *var)
{
	int	i;

	i = 0;
	while (var[i] != '=' && var[i])
		i++;
	if (var[i] == '=')
		i++;
	return (&var[i]);
}

/*	finds variable in list, returns its value	*/
char	*mini_getenv(char *name, t_env *env)
{
	int		i;
	t_env	*temp;

	i = 0;
	temp = env;
	if (name[0] == '$')
		name++;
	while (temp)
	{
		i = 0;
		while (temp->var[i] != '=' && temp->var[i])
			i++;
		if (((ft_strncmp(temp->var, name, i) == 0))
			&& ((name[i] == '=') || (!name[i])))
			return (get_value(temp->var));
		if (temp->next)
			temp = temp->next;
		else
			return (NULL);
	}
	return (NULL);
}
