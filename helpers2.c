/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helpers2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkatzenb <jkatzenb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/20 18:30:09 by jkatzenb          #+#    #+#             */
/*   Updated: 2023/10/20 19:00:42 by jkatzenb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	if_double_symbol(char **cmd, int i[])
{
	if ((cmd[i[0]][i[1]] == '<'
		&& cmd[i[0]][i[1] + 1] && cmd[i[0]][i[1] + 1] == '<')
		|| (cmd[i[0]][i[1]] == '>'
		&& cmd[i[0]][i[1] + 1] && cmd[i[0]][i[1] + 1] == '>'))
		return (1);
	return (0);
}

int	validate_pipes(char *str)
{
	int	i;

	i = 0;
	while (str[i] == ' ' || str[i] == '\t')
		i++;
	if (str[i] == '|'
		|| str[ft_strlen(str) - 1] == '|' || str[ft_strlen(str) - 1] == '<'
		|| str[ft_strlen(str) - 1] == '>')
		return (1);
	while (str[++i])
	{
		if (str[i] == '|'
			|| (str[i] == '<' && str[i + 1] && str[i + 1] != '<')
			|| (str[i] == '>' && str[i + 1] && str[i + 1] != '>'))
			while (str[++i] == ' ' || str[i] == '\t')
				;
		if (str[i] == '|'
			|| (str[i] == '<' && str[i - 1] && str[i - 1] != '<'
				&& str[i + 1] && str[i + 1] != '<')
			|| (str[i] == '>' && str[i - 1] && str[i - 1] != '>'
				&& str[i + 1] && str[i + 1] != '>'))
			return (1);
	}
	return (0);
}
