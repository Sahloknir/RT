/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   light_side.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: axbal <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/07 13:59:34 by axbal             #+#    #+#             */
/*   Updated: 2019/03/19 13:10:48 by axbal            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

int			side_light_check(t_dot origin, t_obj *o, t_sec_r s, t_data *d)
{
	float	d1;
	float	d2;
	t_dot	dot1;
	t_dot	dot2;

	dot1 = new_dot(origin.x + d->t[0] * s.o_ray.x, origin.y + d->t[0]
		* s.o_ray.y, origin.z + d->t[0] * s.o_ray.z);
	dot2 = new_dot(origin.x + d->t[1] * s.o_ray.x, origin.y + d->t[1]
		* s.o_ray.y, origin.z + d->t[1] * s.o_ray.z);
	d1 = two_point_dist(origin, dot1);
	d2 = two_point_dist(origin, dot2);
	if (d1 <= d2)
		return (1);
	if (d2 < d1 && check_lim(o, dot2, newdir(origin, s.o_ray), d) == -1)
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
	org = d->light[d->l]->pos;
	if (d->t[0] != find_right_distance(d, org, s.lo, s.inter))
		fswap(&(d->t[0]), &(d->t[1]));
	d1 = get_hitpoint(d->light[d->l]->pos, s.lo, d->t[0]);
	d2 = get_hitpoint(d->light[d->l]->pos, s.lo, d->t[1]);
	ret = side_light_check(org, obj, s, d);
	org = d->cam->pos;
	test_object(d, s.o_ray, obj, d->cam->pos);
	if (d->t[0] != find_right_distance(d, org, s.o_ray, s.inter))
		fswap(&(d->t[0]), &(d->t[1]));
	d1 = get_hitpoint(d->cam->pos, s.o_ray, d->t[0]);
	d2 = get_hitpoint(d->cam->pos, s.o_ray, d->t[1]);
	if (ret == 0 || ret != side_light_check(org, obj, s, d))
		return (-1);
	return (1);
}
