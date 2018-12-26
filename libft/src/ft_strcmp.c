/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: axbal <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/11 12:57:07 by axbal             #+#    #+#             */
/*   Updated: 2017/11/16 15:32:21 by axbal            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_strcmp(const char *s1, const char *s2)
{
	int		len;

	len = ft_strlen(s1) > ft_strlen(s2) ? ft_strlen(s1) : ft_strlen(s2);
	return (ft_strncmp(s1, s2, len));
}
