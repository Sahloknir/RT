/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: axbal <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/11 11:50:55 by axbal             #+#    #+#             */
/*   Updated: 2017/11/11 11:50:57 by axbal            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dest, const char *src, size_t size)
{
	size_t		max;
	size_t		len_src;
	size_t		i;

	i = 0;
	max = size - ft_strlen(dest) - 1;
	len_src = ft_strlen(src);
	while (dest[i] && i < size)
		i++;
	len_src += ((i < size) ? i : size);
	if ((int)max > 0)
		ft_strncat(dest, src, size - ft_strlen(dest) - 1);
	return (len_src);
}
