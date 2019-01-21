/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   diffuse.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: axbal <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/23 16:05:31 by axbal             #+#    #+#             */
/*   Updated: 2019/01/10 15:38:23 by ceugene          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"
#include <math.h>

t_color		diffuse_sphere(t_color c, t_dot inter, t_obj *o, t_data *d)
{
	t_diffuse	s;

	d->stop = 1;
	s.lc = new_dot(d->light[d->l]->px, d->light[d->l]->py, d->light[d->l]->pz);
	s.obj_center = new_dot(o->px, o->py, o->pz);
	s.normale = two_point_vector(s.obj_center, inter);
	norm_vec(&(s.normale));
	s.lo = two_point_vector(s.obj_center, s.lc);
	norm_vec(&(s.lo));
	s.angle = fabs(scalar(&(s.normale), &(s.lo)));
	c.r += (int)ft_clamp(((o->color.r / d->lights) * s.angle), 0, o->color.r);
	c.g += (int)ft_clamp(((o->color.g / d->lights) * s.angle), 0, o->color.g);
	c.b += (int)ft_clamp(((o->color.b / d->lights) * s.angle), 0, o->color.b);
//	if (o->shiny && s.angle >= 0.99)
//	{
///		return (color_interp(new_color(o->color.r, o->color.g, o->color.b, 0),
//			new_color(255, 255, 255, 0), s.angle));
//	}
	d->stop = 0;
	return (c);
}

t_color		diffuse_plane(t_color c, t_dot inter, t_obj *obj, t_data *d)
{
	t_diffuse	s;

	d->stop = 1;
	s.lc = new_dot(d->light[d->l]->px, d->light[d->l]->py, d->light[d->l]->pz);
	s.normale = *(obj->v);
	norm_vec(&(s.normale));
	s.lo = two_point_vector(s.lc, inter);
	norm_vec(&(s.lo));
	s.angle = fabs(scalar(&(s.normale), &(s.lo)));
	c.r += ft_clamp(((obj->color.r / d->lights) * s.angle), 0, obj->color.r);
	c.g += ft_clamp(((obj->color.g / d->lights) * s.angle), 0, obj->color.g);
	c.b += ft_clamp(((obj->color.b / d->lights) * s.angle), 0, obj->color.b);
	d->stop = 0;
	return (c);
}

t_color		diffuse_cone(t_color c, t_dot inter, t_obj *o, t_data *d)
{
	t_diffuse	s;

	d->stop = 1;
	s.lo = new_vec(d->light[d->l]->px, d->light[d->l]->py, d->light[d->l]->pz);
	s.lo = trans_vec(s.lo, o->px, o->py, o->pz);
	s.lo = rot_vec(s.lo, o->rx, o->ry, 0);
	s.a_dot = new_vec(inter.x, inter.y, inter.z);
	s.a_dot = trans_vec(s.a_dot, o->px, o->py, o->pz);
	s.a_dot = rot_vec(s.a_dot, o->rx, o->ry, 0);
	s.affixe = new_dot(0, 0, s.a_dot.z);
	s.normale = two_point_vector(s.affixe,
		new_dot(s.a_dot.x, s.a_dot.y, s.a_dot.z));
	norm_vec(&(s.normale));
	s.lo = two_point_vector(s.affixe, new_dot(s.lo.x, s.lo.y, s.lo.z));
	norm_vec(&(s.lo));
	s.angle = fabs(scalar(&(s.normale), &(s.lo)));
	c = apply_color(c, o, d, s.angle);
//	if (o->shiny && s.angle > 0.99)
//	{
//		return (color_interp(new_color(o->color.r, o->color.g, o->color.b, 0),
//			new_color(255, 255, 255, 0), s.angle));
//	}
	d->stop = 0;
	return (c);
}

t_color		diffuse_cylinder(t_color c, t_dot inter, t_obj *o, t_data *d)
{
	t_diffuse	s;

	d->stop = 1;
	s.lo = new_vec(d->light[d->l]->px, d->light[d->l]->py, d->light[d->l]->pz);
	s.lo = trans_vec(s.lo, o->px, o->py, o->pz);
	s.lo = rot_vec(s.lo, o->rx, o->ry, 0);
	s.a_dot = new_vec(inter.x, inter.y, inter.z);
	s.a_dot = trans_vec(s.a_dot, o->px, o->py, o->pz);
	s.a_dot = rot_vec(s.a_dot, o->rx, o->ry, 0);
	s.affixe = new_dot(0, 0, s.a_dot.z);
	s.normale = two_point_vector(s.affixe,
		new_dot(s.a_dot.x, s.a_dot.y, s.a_dot.z));
	norm_vec(&(s.normale));
	s.lo = two_point_vector(s.affixe, new_dot(s.lo.x, s.lo.y, s.lo.z));
	norm_vec(&(s.lo));
	s.angle = fabs(scalar(&(s.normale), &(s.lo)));
	c = apply_color(c, o, d, s.angle);
//	if (o->shiny && s.angle > 0.99)
//	{
//		return (color_interp(new_color(o->color.r, o->color.g, o->color.b, 0),
//			new_color(255, 255, 255, 0), s.angle));
//	}
	d->stop = 0;
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
