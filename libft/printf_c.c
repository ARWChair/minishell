/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printf_c.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkatzenb <jkatzenb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/24 12:51:49 by jkatzenb          #+#    #+#             */
/*   Updated: 2023/09/19 13:32:42 by jkatzenb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	printf_c(va_list args, int count)
{
	int	c;

	c = (char)va_arg(args, int);
	write(1, &c, 1);
	count++;
	return (count);
}
