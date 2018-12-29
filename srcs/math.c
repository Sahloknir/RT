/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   math.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: axbal <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/13 13:02:44 by axbal             #+#    #+#             */
/*   Updated: 2018/11/20 16:21:45 by axbal            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

float		ft_clamp(float to_clamp, float min, float max)
{
	if (to_clamp > max)
		return (max);
	if (to_clamp < min)
		return (min);
	return (to_clamp);
}

float		two_point_dist(t_dot p1, t_dot p2)
{
	float	dist;

	dist = pow(p2.x - p1.x, 2) + pow(p2.y - p2.y, 2) + pow(p2.z - p2.z, 2);
	return (dist);
}

t_color		color_interp(t_color c1, t_color c2, float factor)
{
	t_color	result;
	int		r;
	int		g;
	int		b;

	factor = (factor - 0.99) * 100;
	r = ft_clamp(c1.r + (c2.r - c1.r) * factor, c1.r, 255);
	g = ft_clamp(c1.g + (c2.g - c1.g) * factor, c1.g, 255);
	b = ft_clamp(c1.b + (c2.b - c1.b) * factor, c1.b, 255);
	result = new_color(r, g, b, 0);
	return (result);
}

float		degree_to_radian(float degree)
{
	return (degree * M_PI / 180.0);
}

int		cmp_dot(t_dot d1, t_dot d2)
{
	if (floor(d1.x) != floor(d2.x))
		return (0);
	if (floor(d1.y) != floor(d2.y))
		return (0);
	if (floor(d1.z) != floor(d2.z))
		return (0);
	return (1);
}


