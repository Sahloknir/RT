/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reading_utilitaries2.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: axbal <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/05 16:03:36 by axbal             #+#    #+#             */
/*   Updated: 2019/02/05 16:10:39 by axbal            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void		get_vec(t_obj *o)
{
	t_vec	v;
	t_vec	*vec;

	v = new_vec(0, 0, 1);
	v = rot_vec(v, o->rx, o->ry, 0);
	norm_vec(&v);
	if (!(vec = (t_vec *)malloc(sizeof(t_vec) * 1)))
		ft_fail("Error: Could not allocate memory.", NULL);
	vec->x = v.x;
	vec->y = v.y;
	vec->z = v.z;
	o->vector_c += 1;
	o->v = vec;
}

int		get_object_refraction(char *f, int s, t_obj *obj)
{
	float	*tab;

	tab = three_values_tab(f, s);
	if (!(f[(int)tab[4]]) || tab[3] != 2)
	{
		free(tab);
		return (0);
	}
	if (tab[1] > 0 && tab[1] <= 100)
	{
		if (tab[0] >= 1 && tab[0] <= 2)
		{
			obj->rf = tab[0];
			obj->trsp = (int)tab[1];
		}
	}
	free(tab);
	return (0);
}

int		get_object_mirror(char *f, int s, t_obj *obj)
{
	float	*tab;

	tab = three_values_tab(f, s);
	if (!(f[(int)tab[4]]) || tab[3] != 1)
	{
		free(tab);
		return (0);
	}
	obj->mirror = ft_clamp((int)tab[0], 0, 100);
	free(tab);
	return (0);
}

int			get_object_rot(char *f, int s, t_obj *obj)
{
	float	*tab;

	tab = three_values_tab(f, s);
	if (!(f[(int)tab[4]]) || tab[3] != 3)
	{
		free(tab);
		return (0);
	}
	obj->rx = tab[0];
	obj->ry = tab[1];
	obj->rz = tab[2];
	free(tab);
	obj->rotation_c += 1;
	if (obj->type == PLANE)
		get_vec(obj);
	return (1);
}

int			get_object_color(char *f, int s, t_obj *obj)
{
	float	*tab;

	tab = three_values_tab(f, s);
	if (!(f[(int)tab[4]]) || tab[3] != 3)
	{
		free(tab);
		return (0);
	}
	if (tab[0] >= 0 && tab[0] <= 255 && tab[1] >= 0 && tab[1] <= 255
	&& tab[2] >= 0 && tab[2] <= 255)
		obj->color = new_color((int)tab[0], (int)tab[1], (int)tab[2], 0);
	free(tab);
	return (1);
}
