#include "rt.h"
#include <math.h>

t_vec	change_norm(t_dot inter, t_diffuse s, t_data *d, t_obj *o)
{
	if (d->img->d == 1 || o->d1 == 1)
	{
			s.normale.x /= cosf(sinf(1 - inter.x - inter.y - inter.z));
			s.normale.y /= cosf(sinf(1 - inter.x - inter.y - inter.z));
			s.normale.z /= cosf(sinf(1 - inter.x - inter.y - inter.z));
	}
	if (d->img->d == 2 || o->d2 == 1)
	{
			s.normale.y *= 1 + (sinf(inter.x + 1.1)) / (cosf(inter.x + 0.1));
			s.normale.z *= 1 + (sinf(inter.x + 1.1)) / (cosf(inter.x + 0.1));
			s.normale.x *= 1 + (sinf(inter.y + 1.1)) / (cosf(inter.y + 0.1));
			s.normale.z *= 1 + (sinf(inter.y + 1.1)) / (cosf(inter.y + 0.1));
			s.normale.x *= 1 + (sinf(inter.z + 1.1)) / (cosf(inter.z + 0.1));
			s.normale.y *= 1 + (sinf(inter.z + 1.1)) / (cosf(inter.z + 0.1));
	}
	return (s.normale);
}

t_color		checkered(t_obj *o, t_dot inter, t_color c1, t_color c2)
{
	float	x;
	float	y;
	float	z;
	float	offset;
	t_vec	v;

	v = new_vec(inter.x, inter.y, inter.z);
	v = trans_vec(v, o->pos.x, o->pos.y, o->pos.z);
	v = rot_vec(v, o->rx, o->ry, o->rz);
	inter = new_dot(v.x, v.y, v.z);
	offset = 3333.33;
	x = (int)((inter.x + offset)) % 2 == 0 ? 1 : 0;
	y = (int)((inter.y + offset)) % 2 == 0 ? 1 : 0;
	z = (int)((inter.z + offset)) % 2 == 0 ? 1 : 0;
	if ((x && y == z) || (y && z == x) || (z && x == y))
		return (c2);
	return (c1);
}

t_color		add_shine(t_sec_r s, t_obj *o, t_color c, t_color b)
{
	float	angle;
	t_color	col;
	t_vec	norm;

	if (o->type != PLANE && o->shiny)
	{
		norm = o->norm(o, s.inter);
		col = new_color(c.r, c.g, c.b, 0);
		angle = fabs(scalar(&norm, &s.lo));
		if (angle >= 0.99)
			col = color_interp(c, new_color(255, 255, 255, 0), angle);
		if (col.r > b.r || col.g > b.g || col.b > b.b)
			return (col);
	}
	return (b);
}
