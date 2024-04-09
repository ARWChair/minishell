/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fprintf_c.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkatzenb <jkatzenb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/24 12:51:49 by jkatzenb          #+#    #+#             */
/*   Updated: 2023/09/19 15:19:45 by jkatzenb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	fprintf_c(va_list args, int count, int fd)
{
	int	c;

	c = (char)va_arg(args, int);
	write(fd, &c, 1);
	count++;
	return (count);
}
