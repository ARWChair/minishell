/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printf_check.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkatzenb <jkatzenb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/24 12:53:26 by jkatzenb          #+#    #+#             */
/*   Updated: 2023/09/19 13:33:33 by jkatzenb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	printf_check(char c, va_list args, int count)
{
	if (c == 'c')
		count = printf_c(args, count);
	else if (c == 's')
		count = printf_s(args, count);
	else if (c == 'p')
		count = printf_p(args, count);
	else if (c == 'd' || c == 'i')
		count = printf_d_i(args, count);
	else if (c == 'u')
		count = printf_u(args, count);
	else if (c == 'X')
		count = printf_x(args, count, 0);
	else if (c == 'x')
		count = printf_x(args, count, 1);
	else if (c == '%')
	{
		write(1, "%", 1);
		count++;
	}
	return (count);
}
