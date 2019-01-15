/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   light_side.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: axbal <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/07 13:59:34 by axbal             #+#    #+#             */
/*   Updated: 2019/01/08 12:01:26 by axbal            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

int			side_light_check(t_dot origin, t_dot inter, t_dot inter2, t_obj *o)
{
	float	d1;
	float	d2;

	d1 = two_point_dist(origin, inter);
	d2 = two_point_dist(origin, inter2);
	if (d1 <= d2)
		return (1);
	if (d2 < d1 && check_lim(o, inter2) == -1)
		return (2);
	return (0);
}

int			call_side_light_check(t_sec_r s, t_obj *obj, t_data *d)
{
	t_dot	d1;
	t_dot	d2;
	t_dot	org;
	int		ret;

	if (obj->type == PLANE)
		return (1);
	org = new_dot(d->light[d->l]->px, d->light[d->l]->py, d->light[d->l]->pz);
	if (d->t[0] != find_right_distance(d, org, s.lo, s.inter))
		fswap(&(d->t[0]), &(d->t[1]));
	d1 = dot_from_light(d->light[d->l], s.lo, d->t[0]);
	d2 = dot_from_light(d->light[d->l], s.lo, d->t[1]);
	ret = side_light_check(org, d1, d2, obj);
	org = new_dot(d->cam->px, d->cam->py, d->cam->pz);
	test_object(d, s.o_ray, obj);
	if (d->t[0] != find_right_distance(d, org, s.o_ray, s.inter))
		fswap(&(d->t[0]), &(d->t[1]));
	d1 = get_hitpoint(s.o_ray, d->t[0], d);
	d2 = get_hitpoint(s.o_ray, d->t[1], d);
	if (ret == 0 || ret != side_light_check(org, d1, d2, obj))
		return (-1);
	return (1);
}
