/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   normales.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: axbal <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/06 15:56:33 by axbal             #+#    #+#             */
/*   Updated: 2019/03/04 15:50:29 by axbal            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"
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
	r_inter = unrot_vec(r_inter, o->rx, o->ry, 0);
	r_inter = trans_vec(r_inter, -o->pos.x, -o->pos.y, -o->pos.z);
	affixe = new_dot(r_inter.x, r_inter.y, r_inter.z);
	norm = two_point_vector(affixe, inter);
	norm_vec(&norm);
	return (norm);
}

t_vec	cone_norm(t_obj *o, t_dot inter)
{
	t_vec	norm;
	t_dot	affixe;
	float	dist;
	t_vec	r_inter;

	dist = two_point_dist(o->pos, inter);
	r_inter = new_vec(inter.x, inter.y, inter.z);
	r_inter = trans_vec(r_inter, o->pos.x, o->pos.y, o->pos.z);
	r_inter = rot_vec(r_inter, o->rx, o->ry, 0);
	r_inter = new_vec(0, 0, r_inter.z + dist);
	r_inter = unrot_vec(r_inter, o->rx, o->ry, 0);
	r_inter = trans_vec(r_inter, -o->pos.x, -o->pos.y, -o->pos.z);
	affixe = new_dot(r_inter.x, r_inter.y, r_inter.z);
	norm = two_point_vector(affixe, inter);

	norm_vec(&norm);
	return (norm);
}
