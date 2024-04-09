/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkatzenb <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/06 17:36:53 by jkatzenb          #+#    #+#             */
/*   Updated: 2022/10/06 17:36:55 by jkatzenb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	count_digits(int n)
{
	int	i;

	i = 0;
	if (n < 0)
		n *= -1;
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

static int	minus_check(int n)
{
	int	minus;

	if (n < 0)
		minus = 2;
	else
		minus = 1;
	return (minus);
}

static char	*putnew(char *new, int n, int i)
{
	while (n)
	{
		new[i++] = (n % 10) + '0';
		n = n / 10;
	}
	new[i] = '\0';
	return (new);
}

char	*ft_itoa(int n)
{
	char	*new;
	int		i;
	int		minus;

	if (n == 0)
		return (ft_strdup("0"));
	if (n == INT_MIN)
		return (ft_strdup("-2147483648"));
	minus = minus_check(n);
	new = (char *)malloc(sizeof(char) * count_digits(n) + minus);
	if (!new)
		return (NULL);
	i = 0;
	if (n < 0)
	{
		n = -n;
		new[i++] = '-';
	}
	putnew(new, n, i);
	reverse(new);
	return (new);
}
