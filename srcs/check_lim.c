/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_lim.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: axbal <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/04 16:14:52 by axbal             #+#    #+#             */
/*   Updated: 2019/03/14 15:02:31 by axbal            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

int		check_x_lim(t_obj *o, t_dot d)
{
	if (o->lim_x_c == 1)
	{
		if (d.x < o->pos.x + o->lim_x_neg || d.x > o->pos.x + o->lim_x_pos)
			return (-1);
	}
	return (1);
}

int		check_y_lim(t_obj *o, t_dot d)
{
	if (o->lim_y_c == 1)
	{
		if (d.y < o->pos.y + o->lim_y_neg || d.y > o->pos.y + o->lim_y_pos)
			return (-1);
	}
	return (1);
}

int		check_z_lim(t_obj *o, t_dot d)
{
	if (o->lim_z_c == 1)
	{
		if (d.z < o->pos.z + o->lim_z_neg || d.z > o->pos.z + o->lim_z_pos)
			return (-1);
	}
	return (1);
}

int		call_lim(t_obj *o, t_dot d)
{
	if (check_x_lim(o, d) == 1 && check_y_lim(o, d) == 1
		&& check_z_lim(o, d) == 1)
		return (1);
	return (-1);
}

int		check_lim(t_obj *o, t_dot d, t_vec ray, t_data *dt)
{
	if (call_lim(o, d) == 1 && rel_lim(o, d) == 1
		&& ((o->neg == 0 && check_neg(d, ray, dt) == 1) || o->neg == 1))
		return (1);
	return (-1);
}

int		double_check_lim(t_obj *o, t_dot d1, t_dot d2, t_vec ray, t_data *d)
{
	int		r1;
	int		r2;

	r1 = check_lim(o, d1, ray, d);
	r2 = check_lim(o, d2, ray, d);
	if (r1 == 1 || r2 == 1)
		return (1);
	return (-1);
}
