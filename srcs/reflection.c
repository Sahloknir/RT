/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reflection.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: axbal <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/04 15:55:34 by axbal             #+#    #+#             */
/*   Updated: 2019/03/16 15:33:50 by axbal            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

t_obj	*find_reflection(t_sec_r *s, t_obj *obj, t_data *d, t_obj *prev)
{
	int		t;
	t_obj	*o;
	t_vec	norm;

	norm = (obj->type == PLANE ? *(obj->v) : obj->norm(obj, s->inter));
	if (obj->mirror > 0)
	{
		t = -1;
		s->o_ray = reflect_ray(&(s->o_ray), &norm);
		s->dist = -1;
		o = NULL;
		while (++t <= d->objects - 1)
		{
			if (d->obj[t] != obj && test_object(d, s->o_ray, d->obj[t], s->inter) > 0)
			{
				if ((d->t[0] > 0.01 || d->t[1] > 0.01))
				{
					if (d->t[0] > 0.01 && (s->dist == -1 || s->dist > d->t[0]))
					{
						s->dist = d->t[0];
						o = d->obj[t];
					}
					if (d->t[1] > 0.01 && (s->dist == -1 || s->dist > d->t[1]))
					{
						s->dist = d->t[1];
						o = d->obj[t];
					}
				}
			}
		}
		if (o == NULL || s->dist == -1 || (prev != NULL && prev == o))
			return (NULL);
		s->inter = get_hitpoint(s->inter, s->o_ray, s->dist);
		if (o != NULL && o->mirror > 0)
			o = find_reflection(s, o, d, obj);
		return (o);
	}
	return (obj);
}
