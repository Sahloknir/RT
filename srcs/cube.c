/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cube.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: axbal <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/14 15:16:26 by axbal             #+#    #+#             */
/*   Updated: 2019/03/16 14:55:05 by axbal            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void	find_limits(t_obj *o, t_obj *obj)
{
	obj->rlim_x_c = 1;
	obj->rlim_x_neg = -(o->size / 2);
	obj->rlim_x_pos = o->size / 2;
	obj->rlim_y_c = 1;
	obj->rlim_y_neg = -(o->size / 2);
	obj->rlim_y_pos = o->size / 2;
	obj->rlim_z_c = 1;
	obj->rlim_z_neg = -(o->size / 2);
	obj->rlim_z_pos = o->size / 2;
}

t_obj	*apply_effects(t_obj *new, t_obj *src)
{
	new->d1 = src->d1;
	new->d2 = src->d2;
	new->d3 = src->d3;
	new->rf = src->rf;
	new->mirror = src->mirror;
	new->trsp = src->trsp;
	return (new);
}

t_obj	*gen_plane(t_dot d, t_obj *o, t_data *data)
{
	t_obj	*obj;
	t_vec	*v2;
	t_vec	pos;

	if (!(v2 = (t_vec *)malloc(sizeof(t_vec) * 1)))
		ft_fail("Error: Unable to allocate enough memory.\n", data);
	obj = create_object(data);
	obj->type = PLANE;
	obj->type_c = 1;
	pos = new_vec(d.x, d.y, d.z);
	pos = rot_vec(pos, o->rx, o->ry, o->rz);
	d = new_dot(pos.x, pos.y, pos.z);
	obj->pos.x = pos.x + o->pos.x;
	obj->pos.y = pos.y + o->pos.y;
	obj->pos.z = pos.z + o->pos.z;
	obj->pos_c = 1;
	obj->rx = o->rx;
	obj->ry = o->ry;
	obj->rz = o->rz;
	obj->rotation_c = 1;
	*v2 = two_point_vector(new_dot(0, 0, 0), d);
	norm_vec(v2);
	obj->v = v2;
	obj->vector_c = 1;
	obj->color = o->color;
	obj = apply_effects(obj, o);
	find_limits(o, obj);
	return (obj);
}

t_obj	*gen_holes(t_obj *o, t_data *d)
{
	t_obj	*obj;

	obj = create_object(d);
	obj->type = SPHERE;
	obj->type_c = 1;
	obj->pos = o->pos;
	obj->pos_c = 1;
	obj->radius = ((o->size / 2) + (o->size / 10));
	obj->radius_c = 1;
	obj->neg = 1;
	return (obj);
}

int		create_cube(t_data *d, t_obj *obj)
{
	add_obj(d, gen_plane(new_dot(-(obj->size / 2), 0, 0), obj, d));
	add_obj(d, gen_plane(new_dot((obj->size / 2), 0, 0), obj, d));
	add_obj(d, gen_plane(new_dot(0, -(obj->size / 2), 0), obj, d));
	add_obj(d, gen_plane(new_dot(0, (obj->size / 2), 0), obj, d));
	add_obj(d, gen_plane(new_dot(0, 0, -(obj->size / 2)), obj, d));
	add_obj(d, gen_plane(new_dot(0, 0, (obj->size / 2)), obj, d));
	if (obj->holes == 1)
		add_neg(d, gen_holes(obj, d));
	return (1);
}
