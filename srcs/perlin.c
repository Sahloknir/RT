/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   perlin.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ceugene <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/27 12:37:50 by ceugene           #+#    #+#             */
/*   Updated: 2019/03/22 14:26:25 by ceugene          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"
#include <math.h>
#include <stdlib.h>

float	p_noise(float x, float y, float z, int *p)
{
	t_perl	s;

	s.ix = (int)floor(x) & 255;
	s.igrek = (int)floor(y) & 255;
	s.zed = (int)floor(z) & 255;
	s.u = p_fade(x);
	s.v = p_fade(y);
	s.w = p_fade(z);
	x -= floor(x);
	y -= floor(y);
	z -= floor(z);
	s.a = p[s.ix] + s.igrek;
	s.b = p[s.ix + 1] + s.igrek;
	s.aa = (int)(p[s.a] + s.zed) % 255;
	s.ab = (int)(p[s.a + 1] + s.zed) % 255;
	s.ba = (int)(p[s.b] + s.zed) % 255;
	s.bb = (int)(p[s.b + 1] + s.zed) % 255;
	return (p_lerp(s.w, p_lerp(s.v, p_lerp(s.u, p_grad(p[s.aa], x, y, z),
		p_grad(p[s.ba], x, y, z)), p_lerp(s.u, p_grad(p[s.ab], x, y - 1, z),
			p_grad(p[s.bb], x - 1, y - 1, z))), p_lerp(s.v, p_lerp(s.u,
				p_grad(p[s.aa + 1], x, y, z - 1), p_grad(p[s.ba + 1],
					x - 1, y, z - 1)), p_lerp(s.u, p_grad(p[s.ab + 1], x, y - 1,
						z - 1), p_grad(p[s.bb + 1], x - 1, y - 1, z - 1)))));
}

float	p_mine(float x, float y, float z, int *p)
{
	t_perl	s;

	s.ix = (int)floor(x + 0.01) & 255;
	s.igrek = (int)floor(y + 0.01) & 255;
	s.zed = (int)floor(z + 0.01) & 255;
	x -= floor(x + 0.01);
	y -= floor(y + 0.01);
	z -= floor(z + 0.01);
	s.a = p[s.ix] + s.igrek;
	s.b = p[s.ix + 1] + s.igrek;
	s.aa = p[s.a] + s.zed;
	s.ab = p[s.a + 1] + s.zed;
	s.ba = p[s.b] + s.zed;
	s.bb = p[s.b + 1] + s.zed;
	return ((s.ba * s.bb * (s.aa * s.ba - s.aa - s.bb) % 10));
}

t_color	minecraft(t_dot pt, t_color c, float noise, t_data *d)
{
	int	level;

	level = 0;
	if (d->img->d4)
	{
		while (++level < 10)
		{
			noise += (1.0 / level) * fabsf((float)p_mine(level * 0.05 * pt.x,
			level * 0.05 * pt.y, level * 0.05 * pt.z, d->p));
		}
		c.r += ft_clamp(c.r / (15 / noise), 0, 255);
		c.g += ft_clamp(c.g / (15 / noise), 0, 255);
		c.b += ft_clamp(c.b / (15 / noise), 0, 255);
	}
	return (c);
}

t_color	perlin(t_data *d, t_color col, t_dot pt)
{
	float	noise;
	t_color	c;
	t_color	basic;

	c = new_color(col.r, col.g, col.b, 0);
	noise = 0.1;
	if (d->perlin == 0)
	{
		gen_permutation(d->p);
		d->perlin = 1;
	}
	c = minecraft(pt, c, noise, d);
	noise = cos(p_noise(pt.x, pt.y, pt.z, d->p) + pt.x + pt.y + pt.z);
	if (noise > -1 && d->img->d5 > 0)
	{
		c.r = ft_clamp(c.r - (c.r / d->img->d5 * (1 - noise)), 0, 255);
		c.g = ft_clamp(c.g - (c.g / d->img->d5 * (1 - noise)), 0, 255);
		c.b = ft_clamp(c.b - (c.b / d->img->d5 * (1 - noise)), 0, 255);
		basic = new_color(col.r, col.g, col.b, 0);
		real_lerp(basic, c, 60);
	}
	return (c);
}
