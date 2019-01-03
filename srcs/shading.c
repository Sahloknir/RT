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

float		find_right_distance2(t_data *d, t_dot light, t_vec vec, t_dot inter)
{
	float	dist;
	float	sum1;
	float	sum2;

	if (d->t[0] < 0 && d->t[1] < 0)
		return (2000);
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

float		find_right_distance(t_data *d, t_obj *obj, t_vec ray, t_dot inter)
{
	float	dist;
	int		d1;
	int		d2;
	t_dot	dot;
	t_dot	light;

	light = new_dot(d->light[d->l]->px, d->light[d->l]->py, d->light[d->l]->pz);
	if (obj->lim_x_c || obj->lim_y_c || obj->lim_z_c)
	{
		dot = new_dot(light.x + ray.x * d->t[0], light.y + ray.y * d->t[0],
			light.z + ray.z * d->t[0]);
		d1 = check_lim(obj, dot);
		dot = new_dot(light.x + ray.x * d->t[1], light.y + ray.y * d->t[1],
			light.z + ray.z * d->t[1]);
		d2 = check_lim(obj, dot);
		dist = d->t[0];
		if (d1 == -1 && d2)
			dist = d->t[1];
		if (d2 == 1 && d1 == 1)
			dist = find_right_distance2(d, light, ray, inter);
	}
	else
		dist = find_right_distance2(d, light, ray, inter);
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
	t_dot	dot2;
	int		ret;

	while (++s.i < d->objects)
	{
		if ((ret = test_light(d, d->light[d->l], s, d->obj[s.i])) == 2)
		{
			dot = dot_from_light(d->light[d->l], s.lo, d->t[0]);
			dot2 = dot_from_light(d->light[d->l], s.lo, d->t[1]);
			if ((d->t[0] > 0 && d->t[0] < s.dist && !(cmp_dot(s.inter, dot))) ||
			(d->t[1] > 0 && d->t[1] < s.dist && !(cmp_dot(s.inter, dot2))))
				break ;
		}
		dot = dot_from_light(d->light[d->l], s.lo, d->t[0]);
		dot2 = dot_from_light(d->light[d->l], s.lo, d->t[1]);
		if (ret >= 1)
		{
			if ((d->t[0] > 0 && d->t[0] < s.dist && check_lim(obj, dot))
				|| (d->t[1] > 0 && d->t[1] < s.dist && check_lim(obj, dot2)))
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
