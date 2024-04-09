/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkatzenb <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/06 17:36:44 by jkatzenb          #+#    #+#             */
/*   Updated: 2022/10/06 17:36:45 by jkatzenb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	split_letters(char *s, char c)
{
	int	i;

	i = 0;
	while (s[i])
	{
		if (s[i] == c || s[i] == '\0')
			return (i);
		i++;
	}
	return (i);
}

static int	split_words(char *s, char c)
{
	int	i;
	int	j;
	int	check;

	i = 0;
	j = 0;
	while (s[i])
	{
		check = 0;
		while (s[i] == c && s[i])
			i++;
		while (s[i] != c && s[i])
		{
			i++;
			check = 1;
		}
		if (check == 1)
			j++;
	}
	return (j);
}

static char	**split_allocate(char const *s, char c)
{
	char	**new;
	int		i;
	int		j;

	new = malloc((split_words((char *)s, c) + 1) * sizeof(char *));
	if (new == NULL)
		return (NULL);
	i = -1;
	j = 0;
	while (s[++i])
	{
		if (s[i] != c)
		{
			new[j] = malloc((split_letters((char *)s + i, c) + 1)
					* sizeof(char));
			if (new[j++] == NULL)
				return (NULL);
			while (s[i] != c && s[i] != '\0')
				i++;
		}
		if (s[i] == '\0')
			break ;
	}
	new[j] = 0;
	return (new);
}

static char	**split_iterate(char const *s, char c, int i, int j)
{
	char	**new;
	int		k;

	new = split_allocate(s, c);
	if (!new)
		return (NULL);
	while (s[++i])
	{
		if (s[i] != c)
		{
			k = 0;
			while (s[i] != c && s[i] != '\0')
			{
				new[j][k++] = s[i++];
				if (s[i] == c || s[i] == '\0')
					new[j][k] = '\0';
			}
			j++;
		}
		if (s[i] == '\0')
			break ;
	}
	return (new);
}

char	**ft_split(char const *s, char c)
{
	char	**new;
	int		i;
	int		j;

	i = -1;
	j = 0;
	if (!s)
		return (NULL);
	new = split_iterate(s, c, i, j);
	if (!new)
		return (NULL);
	return (new);
}
