/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_obj.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: axbal <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/23 16:09:35 by axbal             #+#    #+#             */
/*   Updated: 2019/02/23 15:07:14 by axbal            ###   ########.fr       */
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
			|| ft_strcmp(type, "plane") == 0 || ft_strcmp(type, "cube") == 0))
	{
		if (obj->type_c == 0)
		{
			if (ft_strcmp(type, "sphere") == 0)
				obj->type = SPHERE;
			if (ft_strcmp(type, "cylinder") == 0)
				obj->type = CYLINDER;
			if (ft_strcmp(type, "plane") == 0)
				obj->type = PLANE;
			if (ft_strcmp(type, "cone") == 0)
				obj->type = CONE;
			if (ft_strcmp(type, "cube") == 0)
				obj->type = CUBE;
		}
		obj->type_c += 1;
	}
	free(type);
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
