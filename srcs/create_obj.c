#include "rt.h"

t_obj		*create_object2(t_obj *new)
{
	new->neg = 0;
	new->mirror = -1;
	new->holes = -1;
	new->d1 = 0;
	new->d2 = 0;
	new->d3 = 0;
	new->color = new_color(255, 255, 255, 0);
	new->rf = 0;
	new->trsp = 0;
	return (new);
}

t_obj		*create_object(t_data *data)
{
	t_obj	*new;

	if (!(new = (t_obj *)malloc(sizeof(t_obj))))
		ft_fail("Error: Could not allocate memory.", data);
	new->type = 0;
	new->pos_c = 0;
	new->type_c = 0;
	new->radius_c = 0;
	new->vector_c = 0;
	new->size_c = 0;
	new->angle_c = 0;
	new->rotation_c = 0;
	new->lim_x_c = 0;
	new->lim_y_c = 0;
	new->lim_z_c = 0;
	new->rlim_x_c = 0;
	new->rlim_y_c = 0;
	new->rlim_z_c = 0;
	new->shiny = 0;
	return (create_object2(new));
}
