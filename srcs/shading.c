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

t_color		find_c(t_sec_r s, t_color c, t_obj *obj, t_data *d)
{
	t_dot	dot;
	t_dot	dot2;
	int		ret;

	if ((obj->lim_x_c || obj->lim_y_c || obj->lim_z_c) &&
	call_side_light_check(s, obj, d) == -1)
		return (c);
	while (++s.i < d->objects)
	{
		ret = test_light(d, d->light[d->l], s, d->obj[s.i]);
		dot = dot_from_light(d->light[d->l], s.lo, d->t[0]);
		dot2 = dot_from_light(d->light[d->l], s.lo, d->t[1]);
		if (ret == 1)
		{
			if ((d->t[0] > 0 && d->t[0] < s.dist && check_lim(d->obj[s.i], dot)
				== 1) || (d->t[1] > 0 && d->t[1] < s.dist &&
					check_lim(d->obj[s.i], dot2) == 1))
				break ;
		}
		if (s.i == d->objects - 1)
			c = find_diffuse(c, s.inter, obj, d);
		if (d->stop != 0)
			break ;
	}
	return (c);
}

t_color		checkered(t_dot inter, t_color c1, t_color c2)
{
	int		x;
	int		y;
	int		z;
	float	offset;

	offset = 1000;
	x = (int)(1 + (inter.x + offset)) % 2 == 0 ? 1 : 0;
	y = (int)(1 + (inter.y + offset)) % 2 == 0 ? 1 : 0;
	z = (int)(1 + (inter.z + offset)) % 2 == 0 ? 1 : 0;
	if ((x && ((!y && !z) || (y && z))) || (y && ((!x && !z) || (x && z)))
		|| (z && ((!x && !y) || (x && y))))
		return (c2);
	return (c1);
}

t_color		secondary_rays(t_dot inter, t_data *d, t_obj *obj, t_vec ray)
{
	t_sec_r	s;
	t_color	c;

	s.inter = inter;
	d->l = -1;
	c = d->lights > 0 ? new_color(d->a.r * (obj->color.r * 0.2)
		/ (d->lights + 2), d->a.g * (obj->color.g * 0.2) / (d->lights + 2),
			d->a.b * (obj->color.b * 0.2) / (d->lights + 2), 0) :
	new_color(obj->color.r, obj->color.g, obj->color.b, 0);
	d->stop = 0;
	while (++(d->l) < d->lights && d->stop == 0)
	{
		s.ld = new_dot(d->light[d->l]->px, d->light[d->l]->py,
		d->light[d->l]->pz);
		s.o_ray = ray;
		s.lo = two_point_vector(s.ld, s.inter);
		test_light(d, d->light[d->l], s, obj);
		s.dist = find_right_distance(d, s.ld, s.lo, inter);
		s.i = -1;
		c = find_c(s, c, obj, d);
	}
	if (obj->d3)
		c = checkered(inter, c, new_color(1 + c.r / 2, 1 + c.g / 2, 1 + c.b / 2, 0));
	return (c);
}
