/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   square.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: axbal <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/14 15:16:26 by axbal             #+#    #+#             */
/*   Updated: 2019/03/15 15:26:24 by axbal            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void	set_lim(t_obj *o, t_obj *obj)
{
	obj->rlim_x_c = 1;
	obj->rlim_x_neg = -(o->size / 2);
	obj->rlim_x_pos = o->size / 2;
	obj->rlim_y_c = 1;
	obj->rlim_y_neg = -(o->size / 2);
	obj->rlim_y_pos = o->size / 2;
}

void	create_square(t_data *d, t_obj *o)
{
	t_obj	*obj;
	t_vec	*v2;

	if (!(v2 = (t_vec *)malloc(sizeof(t_vec) * 1)))
		ft_fail("Error: Unable to allocate enough memory.\n", d);
	obj = create_object(d);
	obj->type = PLANE;
	obj->type_c = 1;
	obj->pos = o->pos;
	obj->pos_c = 1;
	obj->rx = o->rx;
	obj->ry = o->ry;
	obj->rz = o->rz;
	obj->rotation_c = 1;
	*v2 = new_vec(0, 0, 1);
	*v2 = rot_vec(*v2, obj->rx, obj->ry, obj->rz);
	norm_vec(v2);
	obj->v = v2;
	obj->vector_c = 1;
	obj->color = o->color;
	obj->d1 = o->d1;
	obj->d2 = o->d2;
	obj->d3 = o->d3;
	set_lim(o, obj);
	add_obj(d, obj);
}
