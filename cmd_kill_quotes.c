/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_kill_quotes.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkatzenb <jkatzenb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/15 17:15:57 by jkatzenb          #+#    #+#             */
/*   Updated: 2023/10/19 19:05:40 by jkatzenb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_var(char *cmd, int *end, char quote)
{
	int		start;
	char	*sub;

	start = ++(*end);
	while (cmd[(*end)] != quote)
		(*end)++;
	(*end)++;
	sub = ft_substr(cmd, start, (*end) - start);
	if (!sub)
		return (NULL);
	return (sub);
}

/*	substrings everything inside quote	*/
char	*get_quote(char *cmd, int *end, char quote)
{
	int		start;
	char	*sub;

	start = ++(*end);
	while (cmd[(*end)] != quote)
		(*end)++;
	sub = ft_substr(cmd, start, (*end) - start);
	if (!sub)
		return (NULL);
	return (sub);
}

/*	substrings everything outside quote	*/
char	*no_quote(char *cmd, int *end)
{
	int		start;
	char	*sub;

	start = (*end);
	while (cmd[(*end)] != '\"' && cmd[(*end)] != '\'' && cmd[(*end)])
		(*end)++;
	(*end)--;
	sub = ft_substr(cmd, start, (*end + 1) - start);
	if (!sub)
		return (NULL);
	return (sub);
}

/*	replaces str with str joined to temp	*/
char	*join_and_free(char **str, char *temp)
{
	char	*new;

	new = ft_strjoin(*str, temp);
	if (!new)
		return (NULL);
	free(*str);
	return (new);
}

/*	gets rid of quotes in matrix ignores quotes within quotes	*/
int	cmd_kill_quotes(char **cmd)
{
	int		line;
	int		end;
	char	*str;

	line = -1;
	while (cmd[++line])
	{
		str = NULL;
		end = -1;
		if (cmd_kill_quotes_loop(cmd, &str, line, end) != 0)
			return (-1);
		free(cmd[line]);
		cmd[line] = ft_strdup(str);
		if (!cmd[line])
		{
			matrix_free(cmd);
			return (-1);
		}
		free(str);
	}
	return (0);
}
