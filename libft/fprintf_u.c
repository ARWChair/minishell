/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printf_u.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkatzenb <jkatzenb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/24 12:52:51 by jkatzenb          #+#    #+#             */
/*   Updated: 2022/11/14 16:14:09 by jkatzenb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	fprintf_u(va_list args, int count, int fd)
{
	unsigned int	u;
	char			*s;
	int				i;

	u = va_arg(args, int);
	i = -1;
	s = ft_uitoa(u);
	while (s[++i])
		count += write(fd, &s[i], 1);
	free(s);
	return (count);
}
