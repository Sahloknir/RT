/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shading.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: axbal <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/13 13:17:13 by axbal             #+#    #+#             */
/*   Updated: 2019/01/10 15:26:17 by ceugene          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"
#include <math.h>

t_color		add_shine(t_light *l, t_obj *o, t_color c, t_dot inter, t_color b)
{
	float	angle;
	t_color	col;
	t_dot	obj_center;
	t_vec	norm;
	t_vec	lo;
	t_dot	lc;

	obj_center = new_dot(o->px, o->py, o->pz);
	norm = two_point_vector(obj_center, inter);
	norm_vec(&(norm));
	lc = new_dot(l->px, l->py, l->pz);
	lo = two_point_vector(obj_center, lc);
	norm_vec(&(lo));
	col = new_color(c.r, c.g, c.b, 0);
	angle = fabs(scalar(&norm, &lo));
	if (o->shiny && angle >= 0.99)
	{
		col = color_interp(new_color(c.r, c.g, c.b, 0),
			new_color(255, 255, 255, 0), angle);
	}
	if (col.r > b.r || col.g > b.g || col.b > b.b)
		return (col);
	return (b);
}

t_color		find_c(t_sec_r *s, t_color c, t_obj *obj, t_data *d)
{
	t_dot	dot;
	t_dot	dot2;
	int		ret;

	if ((obj->lim_x_c || obj->lim_y_c || obj->lim_z_c) &&
	call_side_light_check(*s, obj, d) == -1)
		return (c);
	while (++(s->i) < d->objects)
	{
		ret = test_light(d, d->light[d->l], *s, d->obj[s->i]);
		dot = dot_from_light(d->light[d->l], s->lo, d->t[0]);
		dot2 = dot_from_light(d->light[d->l], s->lo, d->t[1]);
		if (ret == 1)
		{
			if ((d->t[0] > 0 && d->t[0] < s->dist && check_lim(d->obj[s->i], dot)
				== 1) || (d->t[1] > 0 && d->t[1] < s->dist &&
					check_lim(d->obj[s->i], dot2) == 1))
				break ;
		}
		if (s->i == d->objects - 1)
		{
			c = find_diffuse(c, s->inter, obj, d);
			s->tab[s->tab_size] = d->l;
			s->tab_size++;
		}
	}
	return (c);
}

t_color		checkered(t_dot inter, t_color c1, t_color c2)
{
	float	x;
	float	y;
	float	z;
	int		offset;

	offset = 2000;
	x = (int)((round(inter.x) + offset) / 2) % 2 == 0 ? 1 : 0;
	y = (int)((round(inter.y) + offset) / 2) % 2 == 0 ? 1 : 0;
	z = (int)((round(inter.z) + offset) / 2) % 2 == 0 ? 1 : 0;
	if ((x && y == z) || (y && x == z) || (z && x == y))
		return (c2);
	return (c1);
}

t_color		secondary_rays(t_dot inter, t_data *d, t_obj *obj, t_vec ray)
{
	t_sec_r	s;
	t_color	c;
	t_color	col;
	int		i;

	s.inter = inter;
	if (!(s.tab = malloc(sizeof(int) * d->lights)))
		ft_fail("Error: Unable to allocate memory.", d);
	d->l = -1;
	s.tab_size = 0;
	c = d->lights > 0 ? new_color(d->a.r * (obj->color.r * 0.2)
		/ (d->lights + 2), d->a.g * (obj->color.g * 0.2) / (d->lights + 2),
			d->a.b * (obj->color.b * 0.2) / (d->lights + 2), 0) :
	new_color(obj->color.r, obj->color.g, obj->color.b, 0);
	while (++(d->l) < d->lights)
	{
		s.ld = new_dot(d->light[d->l]->px, d->light[d->l]->py,
		d->light[d->l]->pz);
		s.o_ray = ray;
		s.lo = two_point_vector(s.ld, s.inter);
		test_light(d, d->light[d->l], s, obj);
		s.dist = find_right_distance(d, s.ld, s.lo, inter);
		s.i = -1;
		c = find_c(&s, c, obj, d);
	}
	if (obj->d3)
		c = checkered(inter, c, new_color(1 + c.r / 2, 1 + c.g / 2, 1 + c.b / 2, 0));
	if (d->img->d4)
		c = perlin(d, c.r, c.g, c.b, inter);
	i = -1;
	col = new_color(c.r, c.g, c.b, 0);
	while (++i < s.tab_size)
		col = add_shine(d->light[i], obj, c, inter, col);
	c = new_color(col.r, col.g, col.b, 0);
	free(s.tab);
	return (c);
}
