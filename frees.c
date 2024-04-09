/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   frees.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yatabay <yatabay@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/17 14:08:09 by jkatzenb          #+#    #+#             */
/*   Updated: 2023/10/17 16:48:42 by yatabay          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*	frees 2d array	*/
void	matrix_free(char **input)
{
	int	i;

	i = 0;
	if (!input[0])
		return ;
	while (input[i])
	{
		free(input[i]);
		input[i++] = NULL;
	}
	if (input)
	{
		free(input);
		input = NULL;
	}
	return ;
}

/*	frees env variables and clears history	*/
void	free_and_clear(int nl_flag, t_env *env, char **input)
{
	if (nl_flag == 1)
		write(1, "\n", 1);
	if (env)
		free_env(&*env);
	rl_clear_history();
	if (*input)
		free(*input);
	return ;
}

/*	frees the mini list and its content	*/
void	free_mini(t_mini *mini)
{
	t_list	*head;
	t_list	*temp;
	t_cmd	*node;

	head = mini->cmds;
	while (head)
	{
		temp = head;
		head = head->next;
		node = temp->content;
		if (node->infile > 2)
			close(node->infile);
		if (node->outfile > 2)
			close(node->outfile);
		matrix_free(node->cmd);
		free(node->path);
		free(temp->content);
		free(temp);
	}
}

/*	This function searches for a value and frees it.
	it returns on -1 if the void* is not found

	Search:  The item you want to search
	To_free: The item you want to free, if the search is not to be found
	Flag:    0 = search for the value | 1 = Free the to_free pointer*/
int	search_free(char *search, char *to_free, int flag)
{
	if (flag == 0)
		if (!search)
			return (-1);
	if (flag == 1)
	{
		if (!search)
		{
			if (to_free)
				free(to_free);
			return (-1);
		}
	}
	return (0);
}
