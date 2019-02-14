#include "rtv1.h"
#include <math.h>
#include <stdlib.h>

float	p_fade(float t)
{
	return (t * t * t * (t * (t * 6 - 15) + 10));
}

float	p_lerp(float t, float a, float b)
{
	return (a + t * (b - a));
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

	ix = (int)floor(x + 0.01) & 255;
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
	return ((ba * bb * (aa * ba - aa - bb)) % 10);
}

int		return_permutation(int x, int *p)
{
	return (p[x]);
}

void	gen_permutation(int *tab)
{
	int		i;

	i = -1;
	while (++i < 256)
		tab[i] = rand() % 255;
}

t_color	perlin(t_data *d, int red, int green, int blue, t_dot pt)
{
	float	noise;
	t_color	color;
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
			noise += (1.0 / level) * fabsf((float)p_noise(level * 0.05 * pt.x,
			level * 0.05 * pt.y, level * 0.05 * pt.z, d->p));
		}
		color.r += ft_clamp(color.r / (15 / noise), 0, 255);
		color.g += ft_clamp(color.g / (15 / noise), 0, 255);
		color.b += ft_clamp(color.b / (15 /noise), 0, 255);
	}
	return (color);
}
