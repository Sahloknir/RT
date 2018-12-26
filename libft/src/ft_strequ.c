/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strequ.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: axbal <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/12 15:09:15 by axbal             #+#    #+#             */
/*   Updated: 2017/11/16 15:17:15 by axbal            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_strequ(const char *s1, const char *s2)
{
	int		len;

	if (s1 != NULL && s2 != NULL)
	{
		len = ft_strlen(s1) > ft_strlen(s2) ? ft_strlen(s1) : ft_strlen(s2);
		return (ft_strnequ(s1, s2, len));
	}
	return (-1);
}
