/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helpers.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkatzenb <jkatzenb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/16 21:18:25 by yatabay           #+#    #+#             */
/*   Updated: 2023/10/20 16:33:00 by jkatzenb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern int	g_exit_status;

int	export_errors(t_cmd *node)
{
	int	i;
	int	equal;

	i = 0;
	equal = 0;
	while (node->cmd[1][i])
	{
		if (node->cmd[1][i] == '=')
			equal = 1;
		if (node->cmd[1][0] == '='
			|| (!ft_isalpha(node->cmd[1][i]) && equal == 0))
		{
			g_exit_status = 1;
			ft_putstr_fd(" not a valid identifier\n", 2);
			return (-1);
		}
		i++;
	}
	return (0);
}

/*	counts length of string inside quote	*/
int	quote(char *input, int i, char quote)
{
	while (input[i] != quote)
		i++;
	return (i + 1);
}

/*	Skipps quotes and increments word, if word is not to be null	*/
void	quote_skip(int character, char *string, int *increment, int *word)
{
	if (string[*increment] == character
		&& ft_strchr(&string[++(*increment)], character))
	{
		while (string[*increment] && string[++(*increment)] != character)
			;
		if (word && string[(*increment) + 1])
			(*word)++;
	}
}

/*	helper for cmd_split	*/
int	cmd_split_help(char *input, int i, int *j)
{
	(*j) = i;
	while (input[i])
	{
		if (input[i] == '\"' && ft_strchr(&input[i + 1], '\"'))
			while (input[++i] != '\"')
				continue ;
		if (input[i] == '\'' && ft_strchr(&input[i + 1], '\''))
			while (input[++i] != '\'')
				continue ;
		if (input[i] == ' ' || input[i] == '\t')
			break ;
		i++;
	}
	return (i);
}

/*	This function searches for quote, dollar, backslash and tilda
	It returns -1 on error*/
int	cmd_expand_filter(char **string, int *counters, char *exp, t_env *env)
{
	if (string[counters[0]][counters[1]] == '\''
		&& ft_strchr(&string[counters[0]][counters[1] + 1], '\''))
		while (string[counters[0]][++counters[1]] != '\'')
			continue ;
	if (string[counters[0]][counters[1]] == '$'
		&& string[counters[0]][counters[1] + 1] != '\0'
		&& ft_strchr("\" ", string[counters[0]][counters[1] + 1]) == 0)
	{
		counters[1] = cmd_find_var(&*string, &exp, counters, env);
		if (counters[1] == -1)
			return (-1);
	}
	else if (string[counters[0]][0] == '~' && (!string[counters[0]][1]
		|| string[counters[0]][1] == '/'))
	{
		exp = mini_getenv("HOME", env);
		if (!exp)
			return (-1);
		if (replace_var(exp, &string[counters[0]], 1, 1) != 0)
		{
			free(exp);
			return (-1);
		}
	}
	return (0);
}
