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

float		find_right_distance(t_data *d, t_obj *obj, t_vec ray)
{
	float	dist;
	int		d1;
	int		d2;

	d1 = check_lim(obj, get_hitpoint(ray, d->t[0], d));
	d2 = check_lim(obj, get_hitpoint(ray, d->t[1], d));
	dist = d->t[0];
	if ((d->t[1] < d->t[0] && d->t[1] > 0 && d2 == 1) || d1 != 1)
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
	while (++s.i < d->objects)
	{
		if (test_light(d, d->light[d->l], s, d->obj[s.i]) == 1)
		{
			if ((d->t[0] > 0 && d->t[0] < s.dist &&
				check_lim(d->obj[s.i], get_hitpoint(s.lo, d->t[0], d)) == 1) ||
				(d->t[1] > 0 && d->t[1] < s.dist &&
				check_lim(d->obj[s.i], get_hitpoint(s.lo, d->t[1], d)) == 1))
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
	while (++(d->l) < d->lights && d->stop == 0)
	{
		s.ld = new_dot(d->light[d->l]->px, d->light[d->l]->py,
			d->light[d->l]->pz);
		s.lo = two_point_vector(s.ld, s.inter);
		test_light(d, d->light[d->l], s, obj);
		s.dist = find_right_distance(d, obj, ray);
		s.i = -1;
		c = find_c(s, c, obj, d);
	}
	return (c);
}
