/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fabricated_objects.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: axbal <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/08 12:30:01 by axbal             #+#    #+#             */
/*   Updated: 2019/01/10 15:35:57 by ceugene          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

int		get_object_size(char *f, int s, t_obj *obj)
{
	float	*tab;

	tab = three_values_tab(f, s);
	if (!(f[(int)tab[4]]) || tab[3] != 1 || tab[0] < 0)
	{
		free(tab);
		return (0);
	}
	obj->size = tab[0];
	obj->size_c += 1;
	free(tab);
	return (1);
}

void	find_limits(t_obj *o, t_obj *obj)
{
	if (obj->px == o->px)
	{
		obj->lim_x_c = 1;
		obj->lim_x_neg = -(o->size / 2);
		obj->lim_x_pos = o->size / 2;
	}
	if (obj->py == o->py)
	{
		obj->lim_y_c = 1;
		obj->lim_y_neg = -(o->size / 2);
		obj->lim_y_pos = o->size / 2;
	}
	if (obj->pz == o->pz)
	{
		obj->lim_z_c = 1;
		obj->lim_z_neg = -(o->size / 2);
		obj->lim_z_pos = o->size / 2;
	}
}

t_obj	*gen_plane(t_dot d, t_vec v, t_obj *o, t_data *data)
{
	t_obj	*obj;
	t_vec	*v2;

	if (!(v2 = (t_vec *)malloc(sizeof(t_vec) * 1)))
		ft_fail("Error: Unable to allocate enough memory.\n", data);
	obj = create_object(data);
	obj->type = PLANE;
	obj->type_c = 1;
	obj->px = d.x;
	obj->py = d.y;
	obj->pz = d.z;
	obj->pos_c = 1;
	v2->x = v.x;
	v2->y = v.y;
	v2->z = v.z;
	obj->v = v2;
	obj->vector_c = 1;
	obj->color = o->color;
	find_limits(o, obj);
	return (obj);
}

int		create_cube(t_data *d, t_obj *obj)
{
	add_obj(d, gen_plane(new_dot(obj->px - (obj->size / 2), obj->py, obj->pz),
	new_vec(1, 0, 0), obj, d));
	add_obj(d, gen_plane(new_dot(obj->px + (obj->size / 2), obj->py, obj->pz),
	new_vec(1, 0, 0), obj, d));
	add_obj(d, gen_plane(new_dot(obj->px, obj->py - (obj->size / 2), obj->pz),
	new_vec(0, 1, 0), obj, d));
	add_obj(d, gen_plane(new_dot(obj->px, obj->py + (obj->size / 2), obj->pz),
	new_vec(0, 1, 0), obj, d));
	add_obj(d, gen_plane(new_dot(obj->px, obj->py, obj->pz - (obj->size / 2)),
	new_vec(0, 0, 1), obj, d));
	add_obj(d, gen_plane(new_dot(obj->px, obj->py, obj->pz + (obj->size / 2)),
	new_vec(0, 0, 1), obj, d));
	return (1);
}

void	fabricated_object(t_data *d, t_obj *obj)
{
	if (obj->type == CUBE)
		create_cube(d, obj);
}
