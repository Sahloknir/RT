/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_obj.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: axbal <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/23 16:09:35 by axbal             #+#    #+#             */
/*   Updated: 2019/01/05 13:45:21 by axbal            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

int		get_object_type(char *f, int s, t_obj *obj)
{
	char	*type;

	s += 5;
	type = word_return(f, s);
	if (type != NULL && (ft_strcmp(type, "sphere") == 0
		|| ft_strcmp(type, "cylinder") == 0 || ft_strcmp(type, "cone") == 0
			|| ft_strcmp(type, "plane") == 0))
	{
		if (obj->type_c == 0)
			obj->type = type;
		else
			free(type);
		obj->type_c += 1;
	}
	return (0);
}

int		get_object_pos(char *f, int s, t_obj *obj)
{
	float	*tab;

	tab = three_values_tab(f, s);
	if (!(f[(int)tab[4]]) || tab[3] != 3)
	{
		free(tab);
		return (0);
	}
	obj->px = tab[0];
	obj->py = tab[1];
	obj->pz = tab[2];
	free(tab);
	obj->pos_c += 1;
	return (1);
}

int		get_object_rad(char *f, int s, t_obj *obj)
{
	float	*tab;

	tab = three_values_tab(f, s);
	if (!(f[(int)tab[4]]) || tab[3] != 1 || tab[0] < 0)
	{
		free(tab);
		return (0);
	}
	obj->radius = tab[0];
	obj->radius_c += 1;
	free(tab);
	return (1);
}

int		get_object_angle(char *f, int s, t_obj *obj)
{
	float	*tab;

	tab = three_values_tab(f, s);
	if (!(f[(int)tab[4]]) || tab[3] != 1)
	{
		free(tab);
		return (0);
	}
	obj->angle = degree_to_radian(tab[0]);
	obj->angle_c += 1;
	free(tab);
	return (1);
}

int		get_object_vec(char *f, int s, t_obj *obj)
{
	float	*tab;
	t_vec	*vec;

	tab = three_values_tab(f, s);
	if (!(f[(int)tab[4]]) || tab[3] != 3)
	{
		free(tab);
		return (0);
	}
	if (!(vec = (t_vec *)malloc(sizeof(t_vec) * 1)))
		ft_fail("Error: Could not allocate memory.", NULL);
	vec->x = tab[0];
	vec->y = tab[1];
	vec->z = tab[2];
	norm_vec(vec);
	obj->v = vec;
	free(tab);
	obj->vector_c += 1;
	return (1);
}

int		get_object_lim(char *f, int s, t_obj *obj)
{
	float	*tab;

	tab = three_values_tab(f, s);
	if (!(f[(int)tab[4]]) || tab[3] != 2)
	{
		free(tab);
		return (0);
	}
	if (tab[0] < 1 && tab[1] > 0)
	{
		obj->lim_x_neg = tab[0];
		obj->lim_x_pos = tab[1];
		obj->lim_x_c = 1;
	}
	free(tab);
	return (1);
}
