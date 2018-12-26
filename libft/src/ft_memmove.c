/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: axbal <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/10 00:43:49 by axbal             #+#    #+#             */
/*   Updated: 2017/11/10 12:18:34 by axbal            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	unsigned char	*a;
	unsigned char	*b;
	int				i;

	a = (unsigned char *)src;
	b = (unsigned char *)dst;
	i = 0;
	if (b > a)
	{
		while (len > 0)
		{
			b[len - 1] = a[len - 1];
			len--;
		}
	}
	else
	{
		while (i < (int)len)
		{
			b[i] = a[i];
			i++;
		}
	}
	return (dst);
}
