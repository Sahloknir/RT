/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnequ.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: axbal <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/12 15:10:44 by axbal             #+#    #+#             */
/*   Updated: 2017/11/16 15:39:43 by axbal            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_strnequ(const char *s1, const char *s2, size_t n)
{
	size_t	i;

	i = 0;
	if (s1 == NULL || s2 == NULL)
		return (-1);
	if (ft_strlen(s1) == 0 || ft_strlen(s2) == 0 || n == 0)
	{
		if (n == 0)
			return (1);
		return (ft_strlen(s1) == ft_strlen(s2) ? 1 : 0);
	}
	while (i < n && s1[i] != '\0' && s1[i] == s2[i])
		i++;
	if (s1[i] == s2[i] || i == n)
		return (1);
	else
		return (0);
}
