/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkatzenb <jkatzenb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/17 15:28:30 by jkatzenb          #+#    #+#             */
/*   Updated: 2023/09/19 14:55:10 by jkatzenb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_printf(const char *str, ...)
{
	int		i;
	int		count;
	va_list	args;

	i = 0;
	count = 0;
	va_start (args, str);
	while (str[i])
	{
		if (str[i] == '%')
		{
			i++;
			count = printf_check(str[i], args, count);
			i++;
		}
		if (str[i] && str[i] != '%')
		{
			count += write (1, &str[i], 1);
			i++;
		}
	}
	return (count);
}
