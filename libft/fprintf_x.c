/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fprintf_x.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkatzenb <jkatzenb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/24 12:53:03 by jkatzenb          #+#    #+#             */
/*   Updated: 2023/09/19 15:19:38 by jkatzenb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	fprintf_x_temp_help(int temp, int case_check)
{
	if (temp < 10)
		temp += 48;
	else
	{
		if (case_check == 0)
			temp += 55;
		else
			temp += 87;
	}
	return (temp);
}

int	fprintf_x(va_list args, int count, int case_check, int fd)
{
	unsigned int		decimal_number;
	unsigned int		temp;
	int					i;
	int					j;
	char				hexa_number[100];

	decimal_number = va_arg(args, int);
	if (decimal_number == 0)
		count += write(fd, "0", 1);
	i = 1;
	while (decimal_number != 0)
	{
		temp = decimal_number % 16;
		temp = fprintf_x_temp_help(temp, case_check);
		hexa_number[i++] = temp;
		decimal_number /= 16;
	}
	j = i - 1;
	while (j > 0)
		count += write(fd, &hexa_number[j--], 1);
	return (count);
}
