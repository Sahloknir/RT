/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shading.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: axbal <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/13 13:17:13 by axbal             #+#    #+#             */
/*   Updated: 2019/03/17 15:52:50 by axbal            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"
#include <math.h>

t_color		add_shine(t_light *l, t_obj *o, t_color c, t_dot inter, t_color b)
{
	float	angle;
	t_color	col;
	t_vec	norm;
	t_vec	lo;

	if (o->type != PLANE && o->shiny)
	{
		norm = o->norm(o, inter);
		lo = two_point_vector(l->pos, inter);
		col = new_color(c.r, c.g, c.b, 0);
		angle = fabs(scalar(&norm, &lo));
		if (angle >= 0.99)
			col = color_interp(c, new_color(255, 255, 255, 0), angle);
		if (col.r > b.r || col.g > b.g || col.b > b.b)
			return (col);
	}
	return (b);
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

t_color		apply_color_effects(t_color c, t_sec_r s, t_data *d, t_obj *o)
{
	t_color	col;
	int		i;

	if (d->img->d5 > 0)
		c = perlin(d, c.r, c.g, c.b, s.inter);
	if (o->d3)
		c = checkered(o, s.inter, c, new_color(1 + c.r / 2, 1 + c.g / 2, 1
			+ c.b / 2, 0));
	i = -1;
	col = new_color(c.r, c.g, c.b, 0);
	while (++i < s.tab_size)
		col = add_shine(d->light[i], o, c, s.inter, col);
	return (col);
}


t_color		every_lights(t_data *d, t_sec_r s, t_obj *o, t_color c)
{
	while (++(d->l) < d->lights)
	{
		s.lo = two_point_vector(d->light[d->l]->pos, s.inter);
		test_object(d, s.lo, o, d->light[d->l]->pos);
		s.dist = find_right_distance(d, d->light[d->l]->pos, s.lo, s.inter);
		s.i = -1;
		c = find_c(&s, c, o, d);
	}
	c = apply_color_effects(c, s, d, o);
	return (c);
}

t_color		secondary_rays(t_dot inter, t_data *d, t_obj *obj, t_vec ray)
{
	t_sec_r	s;
	t_color	c;
	t_obj	*o;

	s.inter = inter;
	if (!(s.tab = malloc(sizeof(int) * d->lights)))
		ft_fail("Error: Unable to allocate memory.", d);
	d->l = -1;
	s.tab_size = 0;
	c = init_c(d, obj);
	if (obj->mirror == -1)
		o = obj;
	s.o_ray = ray;
	if (!(o = find_reflection(&s, obj, d, 0)))
	{
		free(s.tab);
		return (real_lerp(obj->color, c, obj->mirror));
	}
	c = every_lights(d, s, o, c);
	if (obj->mirror > -1 && obj->mirror < 100)
		c = real_lerp(obj->color, c, obj->mirror);
	if (o->trsp > 0)
		c = real_lerp(c, transparent(c, d, s, o), o->trsp);
	free(s.tab);
	return (c);
}
