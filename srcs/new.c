/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   new.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: axbal <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/13 13:04:35 by axbal             #+#    #+#             */
/*   Updated: 2019/02/23 15:36:23 by axbal            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

t_dot		new_dot(float x, float y, float z)
{
	t_dot	d;

	d.x = x;
	d.y = y;
	d.z = z;
	return (d);
}

t_vec		new_vec(float x, float y, float z)
{
	t_vec	v;

	v.x = x;
	v.y = y;
	v.z = z;
	return (v);
}

t_color		new_color(int r, int g, int b, int a)
{
	t_color		new;

	new.r = r;
	new.g = g;
	new.b = b;
	new.a = a;
	return (new);
}

t_data		*new_data(void)
{
	t_data	*new;

	if (!(new = (t_data *)malloc(sizeof(t_data) * 1)))
		ft_fail("Error: Could not allocate memory", NULL);
	if (!(new->mlx_ptr = mlx_init()))
		ft_fail("Error: Connection failed.", NULL);
	if (!(new->win_ptr = mlx_new_window(new->mlx_ptr, LA, HA, "rt")))
		ft_fail("Error: Unable to create window.", NULL);
	init_data(new);
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
	new->size_c = 0;
	new->angle_c = 0;
	new->vector_c = 0;
	new->rotation_c = 0;
	new->lim_x_c = 0;
	new->lim_y_c = 0;
	new->lim_z_c = 0;
	new->rlim_x_c = 0;
	new->rlim_y_c = 0;
	new->rlim_z_c = 0;
	new->shiny = 0;
	new->mirror = 0;
	new->d1 = 0;
	new->d2 = 0;
	new->d3 = 0;
	new->color = new_color(255, 255, 255, 0);
	return (new);
}
