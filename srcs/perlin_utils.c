/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   perlin_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: axbal <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/21 14:28:55 by axbal             #+#    #+#             */
/*   Updated: 2019/03/21 14:28:56 by axbal            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

float	p_fade(float t)
{
	return (t * t * t * (t * (t * 6 - 15) + 10));
}

float	p_lerp(float t, float a, float b)
{
	return (a + (t) * (b - a));
}

float	p_grad(int hash, float x, float y, float z)
{
	int		h;
	float	u;
	float	v;

	h = hash & 15;
	u = h < 8 ? x : y;
	v = z;
	if (h < 4)
		v = y;
	else if (h == 12 || h == 14)
		v = x;
	u = (h & 1) == 0 ? u : -u;
	v = (h & 2) == 0 ? v : -v;
	return (u + v);
}

int		return_permutation(int x, int *p)
{
	x = x % 255;
	return (p[x]);
}

void	gen_permutation(int *tab)
{
	int		i;

	i = -1;
	while (++i < 256)
		tab[i] = rand() % 255;
	i = -1;
	while (++i < 255)
	{
		if (tab[i] >= tab[i + 1] - 3 && tab[i] <= tab[i + 1] + 3)
		{
			tab[i] = rand() % 255;
			i = -1;
		}
	}
}
