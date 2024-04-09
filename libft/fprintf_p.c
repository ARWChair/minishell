/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printf_p.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkatzenb <jkatzenb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/24 12:53:19 by jkatzenb          #+#    #+#             */
/*   Updated: 2022/11/14 16:14:34 by jkatzenb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	fprint_p_x_help(unsigned long p, int count, int fd)
{
	unsigned long		decimal_number;
	unsigned long		temp;
	int					i;
	int					j;
	char				hexa_number[100];

	count = 0;
	decimal_number = p;
	if (decimal_number == 0)
		count += write(fd, "0", 1);
	i = 1;
	while (decimal_number != 0)
	{
		temp = decimal_number % 16;
		if (temp < 10)
			temp += 48;
		else
			temp += 87;
		hexa_number[i++] = temp;
		decimal_number /= 16;
	}
	j = i - 1;
	while (j > 0)
		count += write(fd, &hexa_number[j--], 1);
	return (count);
}

int	fprintf_p(va_list args, int count, int fd)
{
	unsigned long	p;

	p = va_arg(args, unsigned long);
	if (!p)
	{
		count += write(fd, "(nil)", 5);
		return (count);
	}
	count += write(fd, "0x", 2);
	count += fprint_p_x_help(p, count, fd);
	return (count);
}
