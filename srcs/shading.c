/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shading.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: axbal <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/13 13:17:13 by axbal             #+#    #+#             */
/*   Updated: 2019/03/04 16:59:59 by axbal            ###   ########.fr       */
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

t_color		init_c(t_data *d, t_obj *obj)
{
	t_color	c;

	c = d->lights > 0 ? new_color(d->a.r * (obj->color.r * 0.2)
		/ (d->lights + 2), d->a.g * (obj->color.g * 0.2) / (d->lights + 2),
			d->a.b * (obj->color.b * 0.2) / (d->lights + 2), 0) :
	new_color(obj->color.r, obj->color.g, obj->color.b, 0);
	return (c);
}

t_sec_r *init_var_s(t_sec_r *s, t_color c, t_obj *obj, t_data *d)
{
	t_color	col2;

	s->ret = test_object(d, s->lo ,d->obj[s->i], d->light[d->l]->pos);
	s->dot = get_hitpoint(d->light[d->l]->pos, s->lo, d->t[0]);
	s->dot2 = get_hitpoint(d->light[d->l]->pos, s->lo, d->t[1]);
	if (s->ret >= 1)
	{
		if ((d->t[0] > 0 && d->t[0] < s->dist && check_lim(d->obj[s->i], s->dot)
			== 1) || (d->t[1] > 0 && d->t[1] < s->dist &&
				check_lim(d->obj[s->i], s->dot2) == 1))
		{
				if (d->obj[s->i]->trsp <= 0)
					s->lever = 1;
				col2 = real_lerp(c, find_diffuse(s->col, s->inter, obj, d),
					d->obj[s->i]->trsp);
				if ((s->col.r != c.r || s->col.b != c.b || s->col.g != c.g)
					&& (col2.r <= s->col.r || col2.g <= s->col.g
						|| col2.b <= s->col.b))
					s->col = new_color(col2.r, col2.g, col2.b, 0);
				else if (s->col.r == c.r && s->col.b == c.b && s->col.g == c.g)
					s->col = new_color(col2.r, col2.g, col2.b, 0);
		}
	}
	return (s);
}

t_color		find_c(t_sec_r *s, t_color c, t_obj *obj, t_data *d)
{
	if ((obj->lim_x_c || obj->lim_y_c || obj->lim_z_c) &&
	call_side_light_check(*s, obj, d) == -1)
		return (c);
	s->col = new_color(c.r, c.g, c.b, 0);
	s->lever = 0;
	while (++(s->i) < d->objects)
	{
		s = init_var_s(s, c, obj, d);
		if (s->lever == 1)
			break;
		if (s->i == d->objects - 1)
		{
			if (s->col.r != c.r || s->col.g != c.g || s->col.b != c.b)
				return (s->col);
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

t_color		apply_color_effects(t_color c, t_sec_r s, t_data *d, t_obj *o)
{
	t_color	col;
	int		i;

	if (d->img->d5 > 0)
		c = perlin(d, c.r, c.g, c.b, s.inter);
	if (o->d3)
		c = checkered(s.inter, c, new_color(1 + c.r / 2, 1 + c.g / 2, 1
			+ c.b / 2, 0));
	i = -1;
	col = new_color(c.r, c.g, c.b, 0);
	while (++i < s.tab_size)
		col = add_shine(d->light[i], o, c, s.inter, col);
	return (col);
}

t_vec		refract_ray(t_obj *o, t_sec_r s)
{
	t_vec	norm;
	float	refraction;
	float	sin_n_r;
	float	sin_n_n;
	t_vec	new;

	norm = (o->type == PLANE ? *(o->v) : o->norm(o, s.inter));
	refraction = o->rf;
	s.o_ray.x *= -1;
	s.o_ray.y *= -1;
	s.o_ray.z *= -1;
	sin_n_r = scalar(&norm, &s.o_ray);
	s.o_ray.x *= -1;
	s.o_ray.y *= -1;
	s.o_ray.z *= -1;
	sin_n_n = sqrt(1 - pow(1 / refraction, 2) * (1 - pow(sin_n_r, 2)));
	if (sin_n_r >= 0)
	{
		new.x = 1 / refraction * s.o_ray.x + (1 / refraction * sin_n_r
			- sin_n_n) * norm.x;
		new.y = 1 / refraction * s.o_ray.y + (1 / refraction * sin_n_r
			- sin_n_n) * norm.y;
		new.z = 1 / refraction * s.o_ray.z + (1 / refraction * sin_n_r
			- sin_n_n) * norm.z;
	}
	else
	{
		new.x = 1 / refraction * s.o_ray.x + (1 / refraction * sin_n_r
			+ sin_n_n) * norm.x;
		new.y = 1 / refraction * s.o_ray.y + (1 / refraction * sin_n_r
			+ sin_n_n) * norm.y;
		new.z = 1 / refraction * s.o_ray.z + (1 / refraction * sin_n_r
			+ sin_n_n) * norm.z;
	}
	return (new);
}

t_obj	*find_object_behind(t_data *d, t_sec_r *s, t_obj *obj)
{
	t_obj	*o;
	int		i;
	int		dist;

	i = -1;
	o = NULL;
	dist = -1;
	while (++i <= d->objects - 1)
	{
		if (d->obj[i] != obj && test_object(d, s->o_ray, d->obj[i], s->inter) > 0)
		{
			if (d->t[0] > 0 || d->t[1] > 0)
			{
				if (d->t[0] > 0 && ((dist == -1 || dist > d->t[0])))
				{
					dist = d->t[0];
					o = d->obj[i];
				}
				if (d->t[1] > 0 && ((dist == -1) || dist > d->t[1]))
				{
					dist = d->t[1];
					o = d->obj[i];
				}
			}
		}
	}
	if (dist <= 0 || o == NULL || o == d->trspa)
		return (NULL);
	s->inter = get_hitpoint(s->inter, s->o_ray, dist);
	return (o);
}

t_color		transparent(t_color c, t_data *d, t_sec_r s, t_obj *o)
{
	t_color	col;
	t_obj	*src;
	t_obj	*bfr;

	col = find_c(&s, c, o, d);
	bfr = NULL;
	src = o;
	if (o->trsp > 0)
	{
		bfr = o;
		s.o_ray = refract_ray(o, s);
		o = find_object_behind(d, &s, o);
		if (o == NULL || o == bfr)
			return (real_lerp(col, init_c(d, bfr), src->trsp));
		if (o->trsp > 0)
			d->trspa = src;
		return (real_lerp(col, secondary_rays(s.inter, d, o, two_point_vector(d->cam->pos, s.inter)),
			src->trsp));
	}
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
	if (!(o = find_reflection(&s, obj, d, NULL)))
	{
		free(s.tab);
		return (real_lerp(obj->color, c, obj->mirror));
	}
	c = every_lights(d, s, o, c);
	if (obj->mirror > -1 && obj->mirror < 100)
		c = real_lerp(obj->color, c, obj->mirror);
	if (obj->trsp > 0)
		c = real_lerp(c, transparent(c, d, s, obj), obj->trsp);
	free(s.tab);
	return (c);
}
