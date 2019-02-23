/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   diffuse.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: axbal <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/23 16:05:31 by axbal             #+#    #+#             */
/*   Updated: 2019/02/23 14:40:10 by axbal            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"
#include <math.h>

t_vec	change_norm(t_dot inter, t_diffuse s, t_data *d, t_obj *o)
{
	if (d->img->d == 1 || o->d1 == 1)
	{
			s.normale.x /= cosf(sinf(1 - inter.x - inter.y - inter.z));
			s.normale.y /= cosf(sinf(1 - inter.x - inter.y - inter.z));
			s.normale.z /= cosf(sinf(1 - inter.x - inter.y - inter.z));
	}
	if (d->img->d == 2 || o->d2 == 1)
	{
			s.normale.y *= 1 + (sinf(inter.x + 1.1)) / (cosf(inter.x + 0.1));
			s.normale.z *= 1 + (sinf(inter.x + 1.1)) / (cosf(inter.x + 0.1));
			s.normale.x *= 1 + (sinf(inter.y + 1.1)) / (cosf(inter.y + 0.1));
			s.normale.z *= 1 + (sinf(inter.y + 1.1)) / (cosf(inter.y + 0.1));
			s.normale.x *= 1 + (sinf(inter.z + 1.1)) / (cosf(inter.z + 0.1));
			s.normale.y *= 1 + (sinf(inter.z + 1.1)) / (cosf(inter.z + 0.1));
	}
	return (s.normale);
}

t_color		diffuse_sphere(t_color c, t_dot inter, t_obj *o, t_data *d)
{
	t_diffuse	s;

	s.normale = two_point_vector(o->pos, inter);
	norm_vec(&(s.normale));
	s.normale = change_norm(inter, s, d, o);
	s.lo = two_point_vector(o->pos, d->light[d->l]->pos);
	norm_vec(&(s.lo));
	s.angle = fabs(scalar(&(s.normale), &(s.lo)));
	c = apply_color(c, o, d, s.angle);
	return (c);
}

t_color		diffuse_plane(t_color c, t_dot inter, t_obj *o, t_data *d)
{
	t_diffuse	s;

	s.normale = *(o->v);
	norm_vec(&(s.normale));
	s.normale = change_norm(inter, s, d, o);
	s.lo = two_point_vector(d->light[d->l]->pos, inter);
	norm_vec(&(s.lo));
	s.angle = fabs(scalar(&(s.normale), &(s.lo)));
	c = apply_color(c, o, d, s.angle);
	return (c);
}

t_color		diffuse_cone(t_color c, t_dot inter, t_obj *o, t_data *d)
{
	t_diffuse	s;

	s.lo = new_vec(d->light[d->l]->pos.x, d->light[d->l]->pos.y, d->light[d->l]->pos.z);
	s.lo = trans_vec(s.lo, o->pos.x, o->pos.y, o->pos.z);
	s.lo = rot_vec(s.lo, o->rx, o->ry, 0);
	s.a_dot = new_vec(inter.x, inter.y, inter.z);
	s.a_dot = trans_vec(s.a_dot, o->pos.x, o->pos.y, o->pos.z);
	s.a_dot = rot_vec(s.a_dot, o->rx, o->ry, 0);
	s.affixe = new_dot(0, 0, s.a_dot.z);
	s.normale = two_point_vector(s.affixe,
		new_dot(s.a_dot.x, s.a_dot.y, s.a_dot.z));
	norm_vec(&(s.normale));
	s.normale = change_norm(inter, s, d, o);
	s.lo = two_point_vector(s.affixe, new_dot(s.lo.x, s.lo.y, s.lo.z));
	norm_vec(&(s.lo));
	s.angle = fabs(scalar(&(s.normale), &(s.lo)));
	c = apply_color(c, o, d, s.angle);
	return (c);
}

t_color		diffuse_cylinder(t_color c, t_dot inter, t_obj *o, t_data *d)
{
	t_diffuse	s;

	s.lo = new_vec(d->light[d->l]->pos.x, d->light[d->l]->pos.y, d->light[d->l]->pos.z);
	s.lo = trans_vec(s.lo, o->pos.x, o->pos.y, o->pos.z);
	s.lo = rot_vec(s.lo, o->rx, o->ry, 0);
	s.a_dot = new_vec(inter.x, inter.y, inter.z);
	s.a_dot = trans_vec(s.a_dot, o->pos.x, o->pos.y, o->pos.z);
	s.a_dot = rot_vec(s.a_dot, o->rx, o->ry, 0);
	s.affixe = new_dot(0, 0, s.a_dot.z);
	s.normale = two_point_vector(s.affixe,
		new_dot(s.a_dot.x, s.a_dot.y, s.a_dot.z));
	norm_vec(&(s.normale));
	s.normale = change_norm(inter, s, d, o);
	s.lo = two_point_vector(s.affixe, new_dot(s.lo.x, s.lo.y, s.lo.z));
	norm_vec(&(s.lo));
	s.angle = fabs(scalar(&(s.normale), &(s.lo)));
	c = apply_color(c, o, d, s.angle);
	return (c);
}

t_color		find_diffuse(t_color c, t_dot inter, t_obj *obj, t_data *d)
{
	if (obj->type == SPHERE)
		c = diffuse_sphere(c, inter, obj, d);
	else if (obj->type == PLANE)
		c = diffuse_plane(c, inter, obj, d);
	else if (obj->type == CONE)
		c = diffuse_cone(c, inter, obj, d);
	else if (obj->type == CYLINDER)
		c = diffuse_cylinder(c, inter, obj, d);
	return (c);
}
