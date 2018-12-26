/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: axbal <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/10 13:33:31 by axbal             #+#    #+#             */
/*   Updated: 2017/11/10 13:47:56 by axbal            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	int				i;
	unsigned char	*a;

	i = 0;
	a = (unsigned char *)s;
	while (i < (int)n)
	{
		if (a[i] == (unsigned char)c)
			return ((void *)s + i);
		i++;
	}
	return (0);
}
