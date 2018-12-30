/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shading.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: axbal <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/13 13:17:13 by axbal             #+#    #+#             */
/*   Updated: 2018/12/28 18:36:16 by axbal            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

float		find_right_distance(t_data *d, t_obj *obj, t_vec ray, t_dot inter)
{
	float	dist;
	int		d1;
	int		d2;
	t_dot	dot;

	dot.x = d->light[d->l]->px + ray.x * d->t[0];
	dot.y = d->light[d->l]->py + ray.y * d->t[0];
	dot.z = d->light[d->l]->pz + ray.z * d->t[0];
	d1 = check_lim(obj, dot);
	dot.x = d->light[d->l]->px + ray.x * d->t[1];
	dot.y = d->light[d->l]->py + ray.y * d->t[1];
	dot.z = d->light[d->l]->pz + ray.z * d->t[1];
	d2 = check_lim(obj, dot);
	dist = d->t[0];
	if (!d1 && d2)
		dist = d->t[1];
	if (d2 && cmp_dot(inter, dot))
		dist = d->t[1];
	return (dist);
}

t_color		find_diffuse(t_color c, t_dot inter, t_obj *obj, t_data *d)
{
	if (!ft_strcmp(obj->type, "sphere"))
		c = diffuse_sphere(c, inter, obj, d);
	else if (!ft_strcmp(obj->type, "plane"))
		c = diffuse_plane(c, inter, obj, d);
	else if (!ft_strcmp(obj->type, "cone"))
		c = diffuse_cone(c, inter, obj, d);
	else if (!ft_strcmp(obj->type, "cylinder"))
		c = diffuse_cylinder(c, inter, obj, d);
	return (c);
}

t_color		find_c(t_sec_r s, t_color c, t_obj *obj, t_data *d)
{
	t_dot	dot;
	int		ret;

	dot.x = d->light[d->l]->px + s.lo.x * d->t[0];
	dot.y = d->light[d->l]->py + s.lo.y * d->t[0];
	dot.z = d->light[d->l]->pz + s.lo.z * d->t[0];
	while (++s.i < d->objects)
	{
		if ((ret = test_light(d, d->light[d->l], s, d->obj[s.i])) == 2)
		{
			if ((d->t[0] > 0 && d->t[0] < s.dist && !(cmp_dot(s.inter, dot))) ||
			(d->t[1] > 0 && d->t[1] < s.dist && (cmp_dot(s.inter, dot))))
				break ;
		}
		else if (ret == 1)
		{
			if ((d->t[0] > 0 && d->t[0] < s.dist)
				|| (d->t[1] > 0 && d->t[1] < s.dist))
				break ;
		}
		if (s.i == d->objects - 1)
			c = find_diffuse(c, s.inter, obj, d);
		if (d->stop != 0)
			break ;
	}
	return (c);
}

t_color		secondary_rays(t_dot inter, t_data *d, t_obj *obj, t_vec ray)
{
	t_sec_r	s;
	t_color	c;

	s.inter = inter;
	d->l = -1;
	c = d->lights > 0 ? new_color(0, 0, 0, 0) :
	new_color(obj->color.r, obj->color.g, obj->color.b, 0);
	d->stop = 0;
	if (check_lim(obj, inter))
	{
		while (++(d->l) < d->lights && d->stop == 0)
		{
			s.ld = new_dot(d->light[d->l]->px, d->light[d->l]->py,
			d->light[d->l]->pz);
			s.lo = ray;
			s.lo = two_point_vector(s.ld, s.inter);
			test_light(d, d->light[d->l], s, obj);
			s.dist = find_right_distance(d, obj, s.lo, inter);
			s.i = -1;
			c = find_c(s, c, obj, d);
		}
	}
	return (c);
}
