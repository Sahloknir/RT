/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_rlim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: axbal <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/12 14:25:18 by axbal             #+#    #+#             */
/*   Updated: 2019/02/21 18:35:34 by axbal            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

int		rel_x_lim(t_obj *o, t_dot d)
{
	if (o->rlim_x_c == 1)
	{
		if (d.x < o->rlim_x_neg || d.x > o->rlim_x_pos)
			return (-1);
	}
	return (1);
}

int		rel_y_lim(t_obj *o, t_dot d)
{
	if (o->rlim_y_c == 1)
	{
		if (d.y < o->rlim_y_neg || d.y > o->rlim_y_pos)
		{
			ft_putnbr(d.y);
			ft_putchar('\n');
			return (-1);
		}
	}
	return (1);
}

int		rel_z_lim(t_obj *o, t_dot d)
{
	if (o->rlim_z_c == 1)
	{
		if (d.z < o->rlim_z_neg || d.z > o->rlim_z_pos)
			return (-1);
	}
	return (1);
}

int		rel_lim(t_obj *o, t_dot d)
{
	t_vec	rel;
	float	dist;

/*	rel = two_point_vector(o->pos, d);
	rel = rot_vec(rel, o->rx, o->ry, 0);
	d = get_hitpoint(new_dot(0, 0, 0), rel, dist);
*/	rel = new_vec(d.x, d.y, d.z);
	rel = trans_vec(rel, o->pos.x, o->pos.y, o->pos.z);
	rel = rot_vec(rel, o->rx, o->ry, 0);
	dist = two_point_dist(o->pos, d);
	d = get_hitpoint(new_dot(0, 0, 0), rel, dist);
//	d = new_dot(rel.x, rel.y, rel.z);
	if (rel_x_lim(o, d) == 1 && rel_y_lim(o, d) == 1 && rel_z_lim(o, d) == 1)
		return (1);
	return (-1);
}

int		double_rel_lim(t_obj *o, t_dot d1, t_dot d2)
{
	int		r1;
	int		r2;

	r1 = rel_lim(o, d1);
	r2 = rel_lim(o, d2);
	if (r1 == 1 && r2 == 1)
		return (3);
	else if (r1 == 1)
		return (1);
	else if (r2 == 1)
		return (2);
	return (-1);
}
