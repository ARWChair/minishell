/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_expand.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkatzenb <jkatzenb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/11 14:34:28 by jkatzenb          #+#    #+#             */
/*   Updated: 2023/10/20 18:34:00 by jkatzenb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern int	g_exit_status;

/*	replaces variable found by cmd_find_var with corresponding value
	and places it between pre (everything in the string before the variable)
	and post (everything after the variable)	*/
int	replace_var(char *var, char **cmd, int j, int k)
{
	char	*s[3];
	int		i;

	s[0] = ft_substr(*cmd, 0, j - 1);
	if (!s[0])
		return (-1);
	i = ft_strlen(*cmd);
	s[1] = ft_substr(*cmd, k, i - k);
	if (search_free(s[1], s[0], 1) != 0)
		return (-1);
	s[2] = ft_strjoin(s[0], var);
	if (search_free(s[2], s[0], 1) != 0 && search_free(s[1], s[1], 1) != 0)
		return (-1);
	free(s[0]);
	s[0] = ft_strjoin(s[2], s[1]);
	if (search_free(s[0], s[1], 1) != 0 && search_free(s[0], s[2], 1) != 0)
		return (-1);
	free(*cmd);
	*cmd = ft_strdup(s[0]);
	free(s[0]);
	free(s[1]);
	free(s[2]);
	if (!*cmd)
		return (-1);
	return (0);
}

int	char_loopup(char search, char **exp, char *var, int *k)
{
	int	returning;

	returning = 0;
	if (!search)
	{
		*exp = ft_strdup("$");
		if (search_free(*exp, var, 1) != 0)
			returning = -1;
		(*k)++;
	}
	if (search == '?')
	{
		*exp = ft_itoa(g_exit_status);
		if (search_free(*exp, var, 1) != 0)
			returning = -1;
		(*k)++;
	}
	return (returning);
}

/*	uses substring to take variable out of string	*/
int	cmd_find_var(char **cmd, char **exp, int *counter, t_env *env)
{
	int		k;
	char	*var;

	k = ++counter[1];
	while (ft_isalnum(cmd[counter[0]][k]))
		k++;
	var = ft_substr(cmd[counter[0]], counter[1], k - counter[1]);
	if (!var)
		return (-1);
	*exp = mini_getenv(var, env);
	if (char_loopup(cmd[counter[0]][counter[1]], exp, var, &k) != 0)
		return (-1);
	if (*exp == NULL)
		*exp = "";
	if (replace_var(*exp, &cmd[counter[0]], counter[1], k) != 0)
	{
		free(var);
		return (-1);
	}
	free(var);
	return (counter[1]);
}

char	**wack_concatinate_function(char **cmd)
{
	char	*strings[2];
	char	**wacker;
	int		i;
	int		words;

	i = 1;
	strings[0] = ft_strdup(cmd[0]);
	if (!strings[0])
	{
		matrix_free(cmd);
		return (NULL);
	}
	while (cmd[i])
	{
		strings[1] = ft_strjoin(strings[0], " ");
		free(strings[0]);
		strings[0] = ft_strjoin(strings[1], cmd[i++]);
		free(strings[1]);
	}
	matrix_free(cmd);
	words = alloc_words(strings[0]);
	wacker = ft_calloc(words + 1, sizeof(char *));
	cmd_split(&*wacker, strings[0], words);
	free(strings[0]);
	return (wacker);
}

/*	expands variables and home path(~)	*/
char	**cmd_expand(char **s, t_env *env)
{
	int		*i;
	char	*exp;

	i = (int *)malloc(sizeof(int) * 3);
	if (!i)
		return (NULL);
	i[0] = 0;
	i[2] = 0;
	exp = NULL;
	while (s[i[0]])
	{
		i[1] = 0;
		while (s[i[0]][i[1]])
		{
			if (cmd_expand_filter(s, i, exp, env) != 0)
				return (NULL);
			i[1]++;
		}
		i[0]++;
	}
	free(i);
	s = wack_concatinate_function(s);
	if (!s)
		return (NULL);
	return (s);
}
