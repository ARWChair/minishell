/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_uitoa.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkatzenb <jkatzenb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/06 17:36:53 by jkatzenb          #+#    #+#             */
/*   Updated: 2022/11/14 16:14:47 by jkatzenb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	count_digits(unsigned int n)
{
	int	i;

	i = 0;
	while (n)
	{
		n = n / 10;
		i++;
	}
	return (i);
}

static void	reverse(char *str)
{
	char	temp;
	int		beg;
	int		end;

	beg = 0;
	end = ft_strlen(str) - 1;
	if (str[beg] == '-')
		beg++;
	while (str[beg] && beg < end)
	{
		temp = str[beg];
		str[beg] = str[end];
		str[end] = temp;
		beg++;
		end--;
	}
}

static char	*putnew(char *new, unsigned int n, int i)
{
	while (n)
	{
		new[i++] = (n % 10) + '0';
		n = n / 10;
	}
	new[i] = '\0';
	return (new);
}

char	*ft_uitoa(unsigned int n)
{
	char	*new;
	int		i;

	if (n == 0)
		return (ft_strdup("0"));
	new = (char *)malloc(sizeof(char) * count_digits(n) + 1);
	if (!new)
		return (NULL);
	i = 0;
	putnew(new, n, i);
	reverse(new);
	return (new);
}
