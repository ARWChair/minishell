/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fprintf_check.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkatzenb <jkatzenb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/24 12:53:26 by jkatzenb          #+#    #+#             */
/*   Updated: 2023/09/19 15:17:46 by jkatzenb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	fprintf_check(char c, va_list args, int count, int fd)
{
	if (c == 'c')
		count = fprintf_c(args, count, fd);
	else if (c == 's')
		count = fprintf_s(args, count, fd);
	else if (c == 'p')
		count = fprintf_p(args, count, fd);
	else if (c == 'd' || c == 'i')
		count = fprintf_d_i(args, count, fd);
	else if (c == 'u')
		count = fprintf_u(args, count, fd);
	else if (c == 'X')
		count = fprintf_x(args, count, 0, fd);
	else if (c == 'x')
		count = fprintf_x(args, count, 1, fd);
	else if (c == '%')
	{
		write(fd, "%", 1);
		count++;
	}
	return (count);
}
