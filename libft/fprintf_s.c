/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printf_s.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkatzenb <jkatzenb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/24 12:52:30 by jkatzenb          #+#    #+#             */
/*   Updated: 2022/11/14 16:13:47 by jkatzenb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	fprintf_s(va_list args, int count, int fd)
{
	int		i;
	char	*s;

	i = -1;
	s = va_arg(args, char *);
	if (!s)
	{
		count += write(fd, "(null)", 6);
		return (count);
	}
	while (s[++i])
		count += write(fd, &s[i], 1);
	return (count);
}
