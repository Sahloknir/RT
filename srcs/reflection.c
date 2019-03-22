/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reflection.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: axbal <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/04 15:55:34 by axbal             #+#    #+#             */
/*   Updated: 2019/03/22 14:43:11 by ceugene          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

t_vec	reflect_ray(t_vec *inc, t_vec *norm)
{
	t_vec	reflect;
	float	scal;

	scal = -2 * scalar(norm, inc);
	reflect.x = (scal * norm->x) + inc->x;
	reflect.y = (scal * norm->y) + inc->y;
	reflect.z = (scal * norm->z) + inc->z;
	return (reflect);
}

float	compare_dist(float dist, t_data *d, t_obj **o, t_sec_r *s)
{
	if ((d->t[0] > 0.01 || d->t[1] > 0.01))
	{
		if (d->t[0] > 0.01 && (dist == -1 || dist > d->t[0])
			&& check_lim(d->obj[d->i],
				get_hitpoint(s->inter, s->o_ray, d->t[0]),
					newdir(s->inter, s->o_ray), d))
		{
			dist = d->t[0];
			*o = d->obj[d->i];
		}
		if (d->t[1] > 0.01 && (dist == -1 || dist > d->t[1])
			&& check_lim(d->obj[d->i],
				get_hitpoint(s->inter, s->o_ray, d->t[1]),
					newdir(s->inter, s->o_ray), d))
		{
			dist = d->t[1];
			*o = d->obj[d->i];
		}
	}
	return (dist);
}

t_obj	*find_dists(t_sec_r *s, t_obj *obj, t_data *d)
{
	t_obj	*o;
	float	dist;

	d->i = -1;
	dist = -1;
	o = NULL;
	while (++d->i <= d->objects - 1)
	{
		if (d->obj[d->i] != obj
			&& test_object(d, s->o_ray, d->obj[d->i], s->inter) > 0)
			dist = compare_dist(dist, d, &o, s);
	}
	s->inter = get_hitpoint(s->inter, s->o_ray, dist);
	return (o);
}

t_color	find_reflection(t_color c, t_sec_r s, t_obj *obj, t_data *d)
{
	t_obj	*o;
	t_vec	norm;
	t_color	color;

	d->miter++;
	color = c;
	norm = (obj->type == PLANE ? *(obj->v) : obj->norm(obj, s.inter));
	if (obj->mirror > 0)
	{
		s.o_ray = reflect_ray(&(s.o_ray), &norm);
		o = find_dists(&s, obj, d);
		if (o == NULL || d->miter > 25)
		{
			d->miter = 0;
			return (real_lerp(color, init_c(d, obj), obj->mirror));
		}
		color = real_lerp(color, secondary_rays(s.inter, d, o, s.o_ray),
			obj->mirror);
	}
	d->miter = 0;
	return (color);
}
