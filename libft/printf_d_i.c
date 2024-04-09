/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printf_d_i.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkatzenb <jkatzenb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/24 12:52:39 by jkatzenb          #+#    #+#             */
/*   Updated: 2023/09/19 14:51:58 by jkatzenb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	printf_d_i(va_list args, int count)
{
	long long	d;
	char		*s;
	int			i;

	i = -1;
	d = va_arg(args, long long);
	s = ft_itoa(d);
	while (s[++i])
		count += write(1, &s[i], 1);
	free(s);
	return (count);
}
