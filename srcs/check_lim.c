/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_lim.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: axbal <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/04 16:14:52 by axbal             #+#    #+#             */
/*   Updated: 2019/01/06 13:06:58 by axbal            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

int		check_x_lim(t_obj *o, t_dot d)
{
	if (o->lim_x_c == 1)
	{
		if (d.x < (o->px + o->lim_x_neg))
			return (-1);
		if (d.x > (o->px + o->lim_x_pos))
			return (-1);
	}
	return (1);
}

int		check_y_lim(t_obj *o, t_dot d)
{
	if (o->lim_y_c == 1)
	{
		if (d.y < o->py + o->lim_y_neg || d.y > o->py + o->lim_y_pos)
			return (-1);
	}
	return (1);
}

int		check_z_lim(t_obj *o, t_dot d)
{
	if (o->lim_z_c == 1)
	{
		if (d.z < o->pz + o->lim_z_neg || d.z > o->pz + o->lim_z_pos)
			return (-1);
	}
	return (1);
}

int		check_lim(t_obj *o, t_dot d)
{
	if (check_x_lim(o, d) == 1 && check_y_lim(o, d) == 1
		&& check_z_lim(o, d) == 1)
		return (1);
	return (-1);
}

int		double_check_lim(t_obj *o, t_dot d1, t_dot d2)
{
	if (check_lim(o, d1) == 1 || check_lim(o, d2) == 1)
		return (1);
	return (-1);
}
