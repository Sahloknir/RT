#include "rt.h"

void	find_limits(t_obj *o, t_obj *obj)
{
	if (obj->pos.x == o->pos.x)
	{
		obj->lim_x_c = 1;
		obj->lim_x_neg = -(o->size / 2);
		obj->lim_x_pos = o->size / 2;
	}
	if (obj->pos.y == o->pos.y)
	{
		obj->lim_y_c = 1;
		obj->lim_y_neg = -(o->size / 2);
		obj->lim_y_pos = o->size / 2;
	}
	if (obj->pos.z == o->pos.z)
	{
		obj->lim_z_c = 1;
		obj->lim_z_neg = -(o->size / 2);
		obj->lim_z_pos = o->size / 2;
	}
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

t_obj	*gen_plane(t_dot d, t_vec v, t_obj *o, t_data *data)
{
	t_obj	*obj;
	t_vec	*v2;

	if (!(v2 = (t_vec *)malloc(sizeof(t_vec) * 1)))
		ft_fail("Error: Unable to allocate enough memory.\n", data);
	obj = create_object(data);
	obj->type = PLANE;
	obj->type_c = 1;
	obj->pos.x = d.x;
	obj->pos.y = d.y;
	obj->pos.z = d.z;
	obj->pos_c = 1;
	v2->x = v.x;
	v2->y = v.y;
	v2->z = v.z;
	obj->v = v2;
	obj->vector_c = 1;
	obj->color = o->color;
	obj = apply_effects(obj, o);
	find_limits(o, obj);
	return (obj);
}

int		create_cube(t_data *d, t_obj *obj)
{
	add_obj(d, gen_plane(new_dot(obj->pos.x - (obj->size / 2), obj->pos.y,
		obj->pos.z), new_vec(1, 0, 0), obj, d));
	add_obj(d, gen_plane(new_dot(obj->pos.x + (obj->size / 2), obj->pos.y,
		obj->pos.z), new_vec(1, 0, 0), obj, d));
	add_obj(d, gen_plane(new_dot(obj->pos.x, obj->pos.y - (obj->size / 2),
		obj->pos.z), new_vec(0, 1, 0), obj, d));
	add_obj(d, gen_plane(new_dot(obj->pos.x, obj->pos.y + (obj->size / 2),
		obj->pos.z), new_vec(0, 1, 0), obj, d));
	add_obj(d, gen_plane(new_dot(obj->pos.x, obj->pos.y, obj->pos.z
		- (obj->size / 2)), new_vec(0, 0, 1), obj, d));
	add_obj(d, gen_plane(new_dot(obj->pos.x, obj->pos.y, obj->pos.z
		+ (obj->size / 2)), new_vec(0, 0, 1), obj, d));
	return (1);
}
