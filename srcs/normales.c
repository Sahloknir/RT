/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   normales.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: axbal <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/06 15:56:33 by axbal             #+#    #+#             */
/*   Updated: 2019/02/11 17:10:36 by axbal            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"
#include "math.h"

t_vec	sphere_norm(t_obj *o, t_dot inter)
{
	t_vec	norm;

	norm = two_point_vector(new_dot(o->pos.x, o->pos.y, o->pos.z), inter);
	norm_vec(&norm);
	return (norm);
}

t_vec	cylinder_norm(t_obj *o, t_dot inter)
{
	t_vec	norm;
	t_dot	affixe;
	t_vec	r_inter;

	r_inter = new_vec(inter.x, inter.y, inter.z);
	r_inter = trans_vec(r_inter, o->pos.x, o->pos.y, o->pos.z);
	r_inter = rot_vec(r_inter, o->rx, o->ry, 0);
	r_inter = new_vec(0, 0, r_inter.z);
	r_inter = rot_vec(r_inter, -o->rx, -o->ry, 0);
	r_inter = trans_vec(r_inter, -o->pos.x, -o->pos.y, -o->pos.z);
	affixe = new_dot(r_inter.x, r_inter.y, r_inter.z);
	norm = two_point_vector(affixe, inter);
	norm_vec(&norm);
	return (norm);
}

t_vec	cone_norm(t_obj *o, t_dot inter)
{
	t_vec	norm;
	t_vec	r_inter;
	t_dot	affixe;
	float	angle;
	float	len;

	angle = 180 - (90 + o->angle);
	r_inter = new_vec(inter.x, inter.y, inter.z);
	r_inter = trans_vec(r_inter, o->pos.x, o->pos.y, o->pos.z);
	r_inter = rot_vec(r_inter, o->rx, o->ry, 0);
	affixe = new_dot(0, 0, r_inter.z);
	len = two_point_dist(new_dot(r_inter.x, r_inter.y, r_inter.z), new_dot(0, 0, 0));
	r_inter = new_vec(0, 0, len / (sin(angle)));
	r_inter = rot_vec(r_inter, -o->rx, -o->ry, 0);
	r_inter = trans_vec(r_inter, -o->pos.x, -o->pos.y, -o->pos.z);
	affixe = new_dot(r_inter.x, r_inter.y, r_inter.z);
	norm = two_point_vector(affixe, inter);
	norm_vec(&norm);
	return (norm);
}
