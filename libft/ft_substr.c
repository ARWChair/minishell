/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkatzenb <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/06 17:36:05 by jkatzenb          #+#    #+#             */
/*   Updated: 2022/10/06 17:36:06 by jkatzenb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	*malloc_check(char const *s, unsigned int start, size_t len)
{
	char	*new;

	if (ft_strlen(s) > len)
		new = (char *)malloc(sizeof(s[0]) * (len + 1));
	else
		new = (char *)malloc(sizeof(s[0]) * (ft_strlen(s) - start + 1));
	return (new);
}

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	size_t	i;
	size_t	j;
	size_t	maxlen;
	char	*new;

	i = 0;
	j = 0;
	if (!s)
		return (NULL);
	maxlen = ft_strlen(s);
	if (s == NULL || maxlen < start)
		return (ft_strdup(""));
	new = malloc_check(s, start, len);
	if (!new)
		return (NULL);
	while (s[i])
	{
		if (i >= start && j < len)
		{
			new[j++] = s[i];
		}
		i++;
	}
	new[j] = '\0';
	return (new);
}
