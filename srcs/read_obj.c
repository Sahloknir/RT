/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_obj.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: axbal <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/23 16:09:35 by axbal             #+#    #+#             */
/*   Updated: 2019/03/16 15:22:10 by axbal            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

int		get_object_type2(t_obj *obj, char *type)
{
	if ((type != NULL && (ft_strcmp(type, "sphere") == 0
		|| ft_strcmp(type, "cylinder") == 0 || ft_strcmp(type, "cone") == 0
			|| ft_strcmp(type, "plane") == 0 || ft_strcmp(type, "cube") == 0
				|| ft_strcmp(type, "holedcube") == 0
					|| ft_strcmp(type, "square") == 0)) && obj->type_c == 0)
	{
		if (ft_strcmp(type, "sphere") == 0)
			obj->type = SPHERE;
		if (ft_strcmp(type, "cylinder") == 0)
			obj->type = CYLINDER;
		if (ft_strcmp(type, "plane") == 0)
			obj->type = PLANE;
		return (1);
	}
	return (0);
}

int		get_object_type(char *f, int s, t_obj *obj)
{
	char	*type;

	type = word_return(f, s + 5);
	if (get_object_type2(obj, type) == 1)
	{
		if (ft_strcmp(type, "cone") == 0)
			obj->type = CONE;
		if (ft_strcmp(type, "cube") == 0)
			obj->type = CUBE;
		if (ft_strcmp(type, "holedcube") == 0)
		{
			obj->holes = 1;
			obj->type = CUBE;
		}
		if (ft_strcmp(type, "square") == 0)
			obj->type = SQUARE;
		obj->type_c += 1;
	}
	free(type);
	return (1);
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
	obj->pos.x = tab[0];
	obj->pos.y = tab[1];
	obj->pos.z = tab[2];
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
