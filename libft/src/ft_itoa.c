/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: axbal <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/14 12:44:19 by axbal             #+#    #+#             */
/*   Updated: 2017/11/14 12:47:20 by axbal            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	*ft_isneg(int isneg, char *str)
{
	if (isneg == 1)
		str[0] = '-';
	return (str);
}

static int	ft_itoa_count(int a)
{
	int		i;

	i = 0;
	while (a)
	{
		a /= 10;
		i++;
	}
	return (i);
}

char		*ft_itoa(int n)
{
	int		i;
	char	*str;
	int		isneg;

	if (n == 0 || n == -2147483648)
		return ((n == 0) ? ft_strdup("0") : ft_strdup("-2147483648"));
	i = 0;
	isneg = 0;
	if (n < 0)
	{
		i++;
		isneg = 1;
		n = n * (-1);
	}
	i = ft_itoa_count(n) + i;
	str = malloc(sizeof(char) * i + 1);
	if (!str)
		return (NULL);
	str[i] = '\0';
	while (n)
	{
		str[--i] = (n % 10) + '0';
		n = n / 10;
	}
	return (ft_isneg(isneg, str));
}
