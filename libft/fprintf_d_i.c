/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fprintf_d_i.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkatzenb <jkatzenb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/24 12:52:39 by jkatzenb          #+#    #+#             */
/*   Updated: 2023/09/19 15:18:03 by jkatzenb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	fprintf_d_i(va_list args, int count, int fd)
{
	long long	d;
	char		*s;
	int			i;

	i = -1;
	d = va_arg(args, long long);
	s = ft_itoa(d);
	while (s[++i])
		count += write(fd, &s[i], 1);
	free(s);
	return (count);
}
