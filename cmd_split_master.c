/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_split_master.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkatzenb <jkatzenb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/08 16:50:03 by jkatzenb          #+#    #+#             */
/*   Updated: 2023/10/20 16:38:19 by jkatzenb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*	counts number of words(substrings) for malloc*/
int	alloc_words(char *input)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (input[i] && (input[i] == ' ' || input[i] == '\t'))
		i++;
	if (!input[i])
		return (0);
	while (input[i])
	{
		quote_skip('"', input, &i, &j);
		quote_skip('\'', input, &i, &j);
		while (input[i] == ' ' || input[i] == '\t')
			i++;
		if (input[i] != '\0')
			j++;
		while (input[i] && input[i] != ' ' && input[i] != '\t')
		{
			quote_skip('"', input, &i, NULL);
			quote_skip('\'', input, &i, NULL);
			i++;
		}
	}
	return (j);
}

/*	splits string at outer quotes and spaces	*/
char	**cmd_split(char **cmd, char *input, int words)
{
	int		i;
	int		j;
	int		word;

	i = 0;
	j = 0;
	word = 0;
	while (word < words)
	{
		while (input[i] == ' ' || input[i] == '\t')
			i++;
		if (input[i])
			i = cmd_split_help(&*input, i, &j);
		cmd[word] = ft_substr(input, j, i - j);
		if (!cmd[word])
			return (NULL);
		word++;
	}
	cmd[word] = 0;
	return (cmd);
}

char	*free_dict(char *input, char *next)
{
	char	*new;

	new = ft_strjoin(input, next);
	free(next);
	if (!new)
		return (NULL);
	return (new);
}

int	prepare_cmds_for_master(char **cmd_old, t_mini *mini, int words)
{
	char	**cmd_new;

	cmd_new = cmd_pipe_split(cmd_old, words);
	matrix_free(cmd_old);
	if (!cmd_new)
		return (-1);
	mini->cmds = cmd_save_list(&*cmd_new, mini->env);
	matrix_free(cmd_new);
	if (!mini->cmds)
	{
		free_mini(&*mini);
		return (-1);
	}
	path_save_list(&*mini);
	if (execute(&*mini) == 1)
		return (-1);
	free_mini(&*mini);
	return (0);
}

/*	allocates substrings for prompt
	and calls all other input parser functions	*/
int	cmd_split_master(char *input, t_mini *mini)
{
	int		words;
	char	**cmd;

	if (!input || !input[0] || validate_input(input))
		return (0);
	words = alloc_words(input);
	if (words == 0)
		return (0);
	cmd = ft_calloc(words + 1, sizeof(char *));
	if (!cmd)
		return (-1);
	cmd = cmd_split(cmd, input, words);
	if (!cmd)
		return (-1);
	cmd = cmd_expand(cmd, mini->env);
	if (!cmd)
		return (-1);
	if (!cmd[0] || cmd[0][0] == 0)
		return (ft_putstr_fd(" command not found\n", 2) && 0);
	if (prepare_cmds_for_master(cmd, mini, words) == -1)
		return (-1);
	return (0);
}
