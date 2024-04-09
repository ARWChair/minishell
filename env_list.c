/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_list.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yatabay <yatabay@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/09 12:46:14 by jkatzenb          #+#    #+#             */
/*   Updated: 2023/06/21 17:13:22 by yatabay          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*	create new env with data as first node	*/
t_env	*env_new(char *var)
{
	t_env	*new;

	new = malloc(sizeof(t_env));
	if (!new)
		return (NULL);
	new->var = malloc(sizeof(char) * (ft_strlen(var) + 1));
	if (!new->var)
		return (NULL);
	ft_strlcpy(new->var, var, ft_strlen(var) + 1);
	new->next = NULL;
	return (new);
}

/*	add var to end of env	*/
void	env_add_back(t_env **env, char *var)
{
	t_env	*temp;

	if (!*env)
	{
		*env = env_new(var);
		return ;
	}
	temp = *env;
	while (temp->next)
		temp = temp->next;
	temp->next = env_new(var);
	return ;
}

/*	add var to beginning of env	*/
void	env_add_front(t_env **env, char *var)
{
	t_env	*new;

	if (!*env)
	{
		*env = env_new(var);
		return ;
	}
	new = env_new(var);
	new->next = *env;
	*env = new;
	return ;
}

/*	count length of env	*/
int	env_length(t_env *env)
{
	t_env	*temp;
	int		i;

	temp = env;
	i = 0;
	while (temp)
	{
		temp = temp->next;
		i++;
	}
	return (i);
}

/*	frees the env	*/
void	free_env(t_env *env)
{
	if (!(env->next == NULL))
		free_env(env->next);
	free (env->var);
	free (env);
	env = NULL;
	return ;
}
