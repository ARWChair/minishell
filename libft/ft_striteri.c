/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_striteri.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkatzenb <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/06 17:37:20 by jkatzenb          #+#    #+#             */
/*   Updated: 2022/10/06 17:37:22 by jkatzenb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_striteri(char *s, void (*f)(unsigned int, char *))
{
	unsigned int	i;
	char			*str;

	str = (char *)s;
	if (!s)
		return ;
	i = 0;
	while (str[i])
	{
		f(i, &str[i]);
		i++;
	}
	str[i] = '\0';
	return ;
}
