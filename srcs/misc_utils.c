/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   misc_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: axbal <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/07 14:05:21 by axbal             #+#    #+#             */
/*   Updated: 2019/01/07 14:20:06 by axbal            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

t_dot	get_hitpoint(t_vec vector, float d, t_data *data)
{
	t_dot	dot;

	dot.x = data->cam->px + vector.x * d;
	dot.y = data->cam->py + vector.y * d;
	dot.z = data->cam->pz + vector.z * d;
	return (dot);
}

t_dot	dot_from_light(t_light *l, t_vec vec, float dist)
{
	t_dot	dot;

	dot.x = l->px + (float)(vec.x * dist);
	dot.y = l->py + (float)(vec.y * dist);
	dot.z = l->pz + (float)(vec.z * dist);
	return (dot);
}

float	pick_a_side(float dm, t_vec ray, t_obj *o, t_data *d)
{
	int		d1;
	int		d2;

	d1 = check_lim(o, get_hitpoint(ray, d->t[0], d));
	d2 = check_lim(o, get_hitpoint(ray, d->t[1], d));
	if (dm == -1 && ((d->t[0] > 0 && d1 == 1) || (d->t[1] > 0 && d2 == 1)))
	{
		if (d->t[0] > 0 && d1 == 1)
			dm = d->t[0];
		if (d->t[1] > 0 && d2 == 1 && (dm == -1 || dm > d->t[1]))
			dm = d->t[1];
	}
	else
	{
		if (d->t[0] >= 0 && d->t[0] < dm && d1 == 1)
			dm = d->t[0];
		if (d->t[1] >= 0 && d->t[1] < dm && d2 == 1)
			dm = d->t[1];
	}
	return (dm);
}

float	find_right_distance(t_data *d, t_dot light, t_vec vec, t_dot inter)
{
	float	dist;
	float	sum1;
	float	sum2;

	if (d->t[0] < 0)
		return (d->t[1]);
	else if (d->t[1] < 0)
		return (d->t[0]);
	sum1 = fabs(inter.x - (light.x + (vec.x * d->t[0])))
	+ fabs(inter.y - (light.y + (vec.y * d->t[0])))
	+ fabs(inter.z - (light.z + (vec.z * d->t[0])));
	sum2 = fabs(inter.x - (light.x + (vec.x * d->t[1])))
	+ fabs(inter.y - (light.y + (vec.y * d->t[1])))
	+ fabs(inter.z - (light.z + (vec.z * d->t[1])));
	dist = sum1 < sum2 ? d->t[0] : d->t[1];
	return (dist);
}

void	fswap(float *f1, float *f2)
{
	float	tmp;

	tmp = *f1;
	*f1 = *f2;
	*f2 = tmp;
}
