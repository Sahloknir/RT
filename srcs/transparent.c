/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   transparent.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: axbal <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/21 14:30:26 by axbal             #+#    #+#             */
/*   Updated: 2019/03/21 14:30:27 by axbal            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"
#include <math.h>

t_vec		change_vec_sign(t_vec to_change)
{
	to_change.x *= -1;
	to_change.y *= -1;
	to_change.z *= -1;
	return (to_change);
}

t_vec		refract_ray(t_obj *o, t_sec_r s)
{
	t_vec	norm;
	float	sin_n_r;
	float	sin_n_n;
	t_vec	new;

	norm = (o->type == PLANE ? *(o->v) : o->norm(o, s.inter));
	s.o_ray = change_vec_sign(s.o_ray);
	sin_n_r = scalar(&norm, &s.o_ray);
	s.o_ray = change_vec_sign(s.o_ray);
	sin_n_n = sqrt(1 - pow(1 / o->rf, 2) * (1 - pow(sin_n_r, 2)));
	if (sin_n_r < 0)
		sin_n_n *= - 1;
	new.x = 1 / o->rf * s.o_ray.x + (1 / o->rf * sin_n_r
		- sin_n_n) * norm.x;
	new.y = 1 / o->rf * s.o_ray.y + (1 / o->rf * sin_n_r
		- sin_n_n) * norm.y;
	new.z = 1 / o->rf * s.o_ray.z + (1 / o->rf * sin_n_r
		- sin_n_n) * norm.z;
	return (new);
}

float	compare_dists(t_obj **o, t_data *d, float dist, int i)
{

	if (d->t[0] > 0.01 || d->t[1] > 0)
	{
		if (d->t[0] > 0.01 && ((dist == -1 || dist > d->t[0])))
		{
			dist = d->t[0];
			*o = d->obj[i];
		}
		if (d->t[1] > 0.01 && ((dist == -1) || dist > d->t[1]))
		{
			dist = d->t[1];
			*o = d->obj[i];
		}
	}
	return (dist);
}

t_obj	*find_object_behind(t_data *d, t_sec_r *s, t_obj *obj)
{
	t_obj	*o;
	int		i;
	float	dist;

	i = -1;
	o = NULL;
	dist = -1;
	while (++i <= d->objects - 1)
	{
		if (d->obj[i] != obj
			&& test_object(d, s->o_ray, d->obj[i], s->inter) > 0)
			dist = compare_dists(&o, d, dist, i);
	}
	if (dist <= 0.01 || o == NULL || d->titer > 10)
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
		if (o == NULL || o == bfr || d->titer > 10)
			return (real_lerp(col, init_c(d, src), src->trsp));
		d->titer += 1;
		col = (real_lerp(col, secondary_rays(s.inter, d, o,
			two_point_vector(d->cam->pos, s.inter)), src->trsp));
	}
	d->titer = 0;
	return (col);
}
