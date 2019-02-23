#include "rtv1.h"
#include <math.h>
#include <stdlib.h>

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

float	p_noise(float x, float y, float z, int *p)
{
	int		ix;
	int		igrek;
	int		zed;
	int		a;
	int		b;
	int		aa;
	int		ab;
	int		bb;
	int		ba;
	float	u;
	float	v;
	float	w;

	ix = (int)floor(x) & 255;
	igrek = (int)floor(y) & 255;
	zed = (int)floor(z) & 255;
	u = p_fade(x);
	v = p_fade(y);
	w = p_fade(z);
	x -= floor(x);
	y -= floor(y);
	z -= floor(z);
	a = p[ix] + igrek;
	b = p[ix + 1] + igrek;
	aa = (int)(p[a] + zed) % 255;
	ab = (int)(p[a + 1] + zed) % 255;
	ba = (int)(p[b] + zed) % 255;
	bb = (int)(p[b + 1] + zed) % 255;
	return (p_lerp(w, p_lerp(v, p_lerp(u, p_grad(p[aa], x, y, z), p_grad(p[ba], x, y, z)), p_lerp(u, p_grad(p[ab], x, y - 1, z), p_grad(p[bb], x - 1, y - 1, z))),
p_lerp(v, p_lerp(u, p_grad(p[aa + 1], x, y, z - 1), p_grad(p[ba + 1], x - 1, y, z -1)), p_lerp(u, p_grad(p[ab + 1], x, y - 1, z - 1), p_grad(p[bb + 1], x - 1, y - 1, z - 1)))));
}

float	p_mine(float x, float y, float z, int *p)
{
	int		ix;
	int		igrek;
	int		zed;
	int		a;
	int		b;
	int		aa;
	int		ab;
	int		bb;
	int		ba;

	ix = (int)floor(x  + 0.01) & 255;
	igrek = (int)floor(y + 0.01) & 255;
	zed = (int)floor(z + 0.01) & 255;
	x -= floor(x + 0.01);
	y -= floor(y + 0.01);
	z -= floor(z + 0.01);
	a = p[ix] + igrek;
	b = p[ix + 1] + igrek;
	aa = p[a] + zed;
	ab = p[a + 1] + zed;
	ba = p[b] + zed;
	bb = p[b + 1] + zed;
	return ((ba * bb * (aa * ba - aa - bb) % 10));
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
		if (tab[i] >= tab[i + 1] - 5 && tab[i] <= tab[i + 1] + 5)
		{
			tab[i] = rand() % 255;
			i = -1;
		}
	}
}

t_color	perlin(t_data *d, int red, int green, int blue, t_dot pt)
{
	float	noise;
	t_color	color;
	t_color	basic;
	int		level;

	color = new_color(red, green, blue, 0);
	noise = 0.1;
	if (d->perlin == 0)
	{
		gen_permutation(d->p);
		d->perlin = 1;
	}
	level = 0;
	if (d->img->d4)
	{
		while (++level < 10)
		{
			noise += (1.0 / level) * fabsf((float)p_mine(level * 0.05 * pt.x,
			level * 0.05 * pt.y, level * 0.05 * pt.z, d->p));
		}
		color.r += ft_clamp(color.r / (15 / noise), 0, 255);
		color.g += ft_clamp(color.g / (15 / noise), 0, 255);
		color.b += ft_clamp(color.b / (15 / noise), 0, 255);
	}
	noise = cos(p_noise(pt.x, pt.y, pt.z, d->p) + pt.x + pt.y + pt.z);
	if (noise >= -1)
	{
		color.r = ft_clamp(color.r - (color.r / 20 * (1 - noise)), 0, 255);
		color.g = ft_clamp(color.g - (color.g / 20 * (1 - noise)), 0, 255);
		color.b = ft_clamp(color.b - (color.b / 20 * (1 - noise)), 0, 255);
		basic = new_color(red, green, blue, 0);
		real_lerp(basic, color, 60);
	}
	return (color);
}
