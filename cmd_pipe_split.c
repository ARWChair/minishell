/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_pipe_split.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkatzenb <jkatzenb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/11 14:38:11 by jkatzenb          #+#    #+#             */
/*   Updated: 2023/10/20 18:30:19 by jkatzenb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*	iterates through quotes and returns j:
	+	position of character in substring
		where the quote ends in case of
		another quote starting directly after this one
		or when end quote is last character in string
	or
	+	position of character in substring one after the end quote
		in all other cases	*/
int	quote_skipper(char **cmd, int i, int j, int flag)
{
	char	quote;
	int		split;

	split = 0;
	if (flag == 0 && (cmd[i][j] == '\'' || cmd[i][j] == '\"'))
	{
		quote = cmd[i][j++];
		while (cmd[i][j] != quote)
			j++;
		if ((!cmd[i][j + 1]) || (cmd[i][j + 1]
			&& cmd[i][j + 1] != '\"' && cmd[i][j + 1] != '\''))
			j++;
	}
	else if (flag == 1 && (cmd[i][j] == '<' || cmd[i][j] == '>'))
	{
		quote = cmd[i][j];
		if (j > 0 && cmd[i][j - 1] != quote)
			split++;
		if ((cmd[i][j + 1] && cmd[i][j + 1] != quote)
			|| (cmd[i][j + 1] && cmd[i][j + 2]))
			split++;
	}
	if (flag == 1)
		j = split;
	return (j);
}

/*	counts number of pipes and redirections	*/
static int	count_pipe(char **cmd)
{
	int		i[3];

	i[0] = -1;
	i[2] = 0;
	while (cmd[++i[0]])
	{
		i[1] = -1;
		while (cmd[i[0]][++i[1]])
		{
			i[1] = quote_skipper(cmd, i[0], i[1], 0);
			if (!cmd[i[0]][i[1]])
				break ;
			if (cmd[i[0]][i[1]] == '|')
			{
				if (i[1] > 0 && cmd[i[0]][i[1] - 1])
					i[2]++;
				if (cmd[i[0]][i[1] + 1])
					i[2]++;
			}
			i[2] += quote_skipper(cmd, i[0], i[1], 1);
			if (if_double_symbol(cmd, i))
				i[1]++;
		}
	}
	return (i[2]);
}

/*	places pipe and redir symbols in matrix	*/
int	place_symbol(char *cmd, int *end, char**temp, int lines)
{
	if (cmd[(*end)] == '|')
		temp[lines] = which_symbol("|", end, 1);
	else if (cmd[(*end)] == '<' && cmd[(*end) + 1] == '<')
		temp[lines] = which_symbol("<<", end, 0);
	else if (cmd[(*end)] == '>' && cmd[(*end) + 1] == '>')
		temp[lines] = which_symbol(">>", end, 0);
	else if (cmd[(*end)] == '<')
		temp[lines] = which_symbol("<", end, 1);
	else if (cmd[(*end)] == '>')
		temp[lines] = which_symbol(">", end, 1);
	else
		return (lines);
	if (!temp[lines])
		return (-1);
	lines++;
	if ((cmd[(*end)] == '<' && cmd[(*end) + 1] == '<')
		|| (cmd[(*end)] == '>' && cmd[(*end) + 1] == '>'))
		(*end) += 2;
	return (lines);
}

/*	splits input at pipes and redirections	*/
static int	split_pipe(char **cmd, char **temp)
{
	int		i[4];

	i[0] = 0;
	i[3] = -1;
	while (cmd[++i[3]])
	{
		i[2] = 0;
		i[1] = 0;
		while (cmd[i[3]][i[1]])
		{
			while (cmd[i[3]][i[2]])
			{
				i[2] = quote_skipper(cmd, i[3], i[2], 0);
				if (cmd[i[3]][i[2]] && (cmd[i[3]][i[2]] == '|'
					|| cmd[i[3]][i[2]] == '<' || cmd[i[3]][i[2]] == '>'))
					break ;
				i[2]++;
			}
			if (fill_string(&*cmd, &*temp, i) == -1)
				return (-1);
		}
	}
	temp[i[0]] = NULL;
	return (0);
}

/*	allocates substrings for pipes and redirs, calls split pipe	*/
char	**cmd_pipe_split(char **cmd, int words)
{
	int		splits;
	char	**temp;
	int		i;

	splits = count_pipe(&*cmd);
	words = 0;
	while (cmd[words])
		words++;
	temp = ft_calloc((words + splits + 1), sizeof(char *));
	if (!temp)
		return (NULL);
	if (splits == 0)
	{
		i = -1;
		while (cmd[++i])
			temp[i] = ft_strdup(cmd[i]);
		temp[i] = NULL;
		return (temp);
	}
	if (split_pipe(cmd, &*temp) != 0)
	{
		matrix_free(temp);
		return (NULL);
	}
	return (temp);
}
