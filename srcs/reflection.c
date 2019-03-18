/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reflection.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: axbal <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/04 15:55:34 by axbal             #+#    #+#             */
/*   Updated: 2019/03/18 18:18:34 by axbal            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

t_obj	*find_dists(t_sec_r *s, t_obj *obj, t_data *d)
{
	t_obj	*o;
	int		t;
	float	dist;

	t = -1;
	dist = -1;
	o = NULL;
	while (++t <= d->objects - 1)
	{
		if (d->obj[t] != obj
			&& test_object(d, s->o_ray, d->obj[t], s->inter) > 0)
		{
			if ((d->t[0] > 0.01 || d->t[1] > 0.01))
			{
				if (d->t[0] > 0.01 && (dist == -1 || dist > d->t[0]))
				{
					dist = d->t[0];
					o = d->obj[t];
				}
				if (d->t[1] > 0.01 && (dist == -1 || dist > d->t[1]))
				{
					dist = d->t[1];
					o = d->obj[t];
				}
			}
		}
	}
	s->inter = get_hitpoint(s->inter, s->o_ray, dist);
	return (o);
}

t_color		find_reflection(t_color c, t_sec_r s, t_obj *obj, t_data *d)
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
