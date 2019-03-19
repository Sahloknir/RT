/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_rlim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: axbal <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/12 14:25:18 by axbal             #+#    #+#             */
/*   Updated: 2019/03/19 12:31:52 by axbal            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

int		rel_x_lim(t_obj *o, t_dot d)
{
	if (o->rlim_x_c == 1 && (d.x < o->rlim_x_neg || d.x > o->rlim_x_pos))
			return (-1);
	return (1);
}

int		rel_y_lim(t_obj *o, t_dot d)
{
	if (o->rlim_y_c == 1 && (d.y < o->rlim_y_neg || d.y > o->rlim_y_pos))
			return (-1);
	return (1);
}

int		rel_z_lim(t_obj *o, t_dot d)
{
	if (o->rlim_z_c == 1 && (d.z < o->rlim_z_neg || d.z > o->rlim_z_pos))
			return (-1);
	return (1);
}

int		rel_lim(t_obj *o, t_dot d)
{
	t_vec	rel;

	rel = new_vec(d.x, d.y, d.z);
	rel = trans_vec(rel, o->pos.x, o->pos.y, o->pos.z);
	if (o->rotation_c == 1 && o->type == PLANE)
		rel = unrot_vec(rel, o->rx, o->ry, o->rz);
	else if (o->rotation_c == 1)
		rel = rot_vec(rel, o->rx, o->ry, o->rz);
	d = new_dot(rel.x, rel.y, rel.z);
	if (rel_x_lim(o, d) == 1 && rel_y_lim(o, d) == 1 && rel_z_lim(o, d) == 1)
		return (1);
	return (-1);
}
