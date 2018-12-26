/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: axbal <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/09 16:59:00 by axbal             #+#    #+#             */
/*   Updated: 2017/11/10 12:37:22 by axbal            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	int				i;
	unsigned char	*a;
	unsigned char	*b;

	i = 0;
	a = (unsigned char *)src;
	b = (unsigned char *)dst;
	while ((int)n > i)
	{
		b[i] = a[i];
		i++;
	}
	return (dst);
}
