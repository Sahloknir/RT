/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memccpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: axbal <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/10 12:38:57 by axbal             #+#    #+#             */
/*   Updated: 2017/11/10 13:31:10 by axbal            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memccpy(void *dst, const void *src, int c, size_t n)
{
	unsigned char	*a;
	unsigned char	*b;
	int				i;

	i = 0;
	a = (unsigned char *)src;
	b = (unsigned char *)dst;
	while (i < (int)n)
	{
		b[i] = a[i];
		if (b[i] == (unsigned char)c)
			return (b + i + 1);
		i++;
	}
	return (NULL);
}
