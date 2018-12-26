/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_doop.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: axbal <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/17 15:20:07 by axbal             #+#    #+#             */
/*   Updated: 2017/11/17 15:26:13 by axbal            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_doop(int a, int b, char c)
{
	char	*sign;
	int		i;
	int		(*op[5])(int, int);

	op[0] = ft_add;
	op[1] = ft_sub;
	op[2] = ft_mul;
	op[3] = ft_div;
	op[4] = ft_mod;
	sign = "+-*/\%";
	i = 0;
	while (c != sign[i] && i < 5)
		i++;
	if (i == 5)
		return (0);
	return ((*op[i])(a, b));
}
