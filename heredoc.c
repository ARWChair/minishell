/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkatzenb <jkatzenb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/24 14:55:33 by jkatzenb          #+#    #+#             */
/*   Updated: 2023/10/20 18:48:39 by jkatzenb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*	replaces variables with its value	*/
char	*heredoc_replace_var(char *var, char *input, int i, int j)
{
	char	*strings[4];
	int		k;

	strings[3] = ft_strdup(input);
	if (!strings[3])
		return (NULL);
	strings[0] = ft_substr(strings[3], 0, i - 1);
	if (!strings[0])
		return (NULL);
	k = ft_strlen(strings[3]);
	strings[1] = ft_substr(strings[3], j, k - j);
	free(strings[3]);
	if (search_free(strings[1], strings[0], 1) == 1)
		return (NULL);
	strings[2] = ft_strjoin(strings[0], var);
	free(strings[0]);
	if (search_free(strings[2], strings[1], 1) == 1)
		return (NULL);
	strings[3] = ft_strjoin(strings[2], strings[1]);
	free(strings[1]);
	free(strings[2]);
	if (!strings[3])
		return (NULL);
	return (strings[3]);
}

char	*heredoc_helper(char *input, int *j, int *i, t_env *env)
{
	char	*expanded;
	char	*var;
	char	*exp;

	expanded = NULL;
	while (ft_isalnum(input[*j]))
		*j += 1;
	var = ft_substr(input, *i, *j - *i);
	if (!var)
		return (NULL);
	exp = mini_getenv(var, env);
	free(var);
	if (exp == NULL)
	{
		exp = ft_strdup("");
		if (!exp)
			return (NULL);
	}
	if (expanded)
	{
		free(expanded);
		expanded = NULL;
	}
	expanded = heredoc_replace_var(exp, input, *i, *j);
	return (expanded);
}

char	*heredoc_expand(char *input, t_env *env)
{
	int		i;
	int		j;
	char	*expanded;

	i = -1;
	expanded = NULL;
	while (input[++i])
	{
		if (input[i] == '$')
		{
			j = ++i;
			expanded = heredoc_helper(input, &j, &i, env);
			if (!expanded)
				break ;
		}
	}
	if (expanded == NULL)
		expanded = ft_strdup(input);
	return (expanded);
}

static void	heredoc_main(char *delim, t_env *env, char *input, int fd)
{
	char	*expanded;

	while (1)
	{
		while (1)
		{
			input = readline(" > ");
			if (input == NULL)
			{
				ft_putstr_fd("Heredoc deliminated with end-of-file.\n", 2);
				free(input);
				input = ft_strdup(delim);
			}
			break ;
		}
		if (ft_strncmp(input, delim, sizeof(input)) == 0)
			break ;
		expanded = heredoc_expand(&*input, env);
		free(input);
		if (!expanded)
			return ;
		write(fd, expanded, ft_strlen(expanded));
		write(fd, "\n", 1);
		free(expanded);
	}
}

int	find_heredoc_fd(char *delim, t_env *env)
{
	int			fd;
	char		*input;
	char		*filename;
	static int	number;

	signal_setup(HEREDOC);
	input = ft_itoa(number++);
	if (!input)
		return (-1);
	filename = ft_strjoin(".heredoc", input);
	if (!filename)
		return (-999999);
	fd = open(filename, O_CREAT | O_WRONLY | O_TRUNC, 0000644);
	heredoc_main(delim, env, input, fd);
	free(input);
	close(fd);
	fd = open(filename, O_RDONLY);
	if (fd > 2)
		unlink(filename);
	free(filename);
	return (fd);
}
