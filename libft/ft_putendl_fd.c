/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putendl_fd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkatzenb <jkatzenb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/06 17:37:53 by jkatzenb          #+#    #+#             */
/*   Updated: 2023/09/19 14:45:41 by jkatzenb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_putendl_fd(char *s, int fd)
{
	int	i;

	if (!s)
		return (0);
	i = -1;
	while (s[++i])
		ft_putchar_fd(s[i], fd);
	write(fd, "\n", 1);
	return (i + 1);
}
