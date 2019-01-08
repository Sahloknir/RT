/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   objects.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: axbal <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/11 21:56:25 by axbal             #+#    #+#             */
/*   Updated: 2019/01/08 15:07:09 by axbal            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

void	add_obj(t_data *data, t_obj *obj)
{
	t_obj	**tmp;
	int		i;

	i = 0;
	if (!(tmp = (t_obj **)malloc(sizeof(t_obj *) * (data->objects + 1))))
		ft_fail("Error: Could not allocate memory.", data);
	while (i < data->objects)
	{
		tmp[i] = data->obj[i];
		i++;
	}
	tmp[i] = obj;
	if (data->objects > 0)
		free(data->obj);
	data->obj = tmp;
	data->objects++;
}

int		expected_result2(t_obj *obj)
{
	if (!(ft_strcmp(obj->type, "cube")))
	{
		if (obj->pos_c == 1 && obj->size_c == 1)
			return (1);
	}
	return (-2);
}

int		expected_result(t_obj *obj)
{
	if (obj->type_c == 0)
		return (0);
	if (!(ft_strcmp(obj->type, "sphere")))
	{
		if (obj->pos_c == 1 && obj->radius_c == 1)
			return (1);
	}
	if (!(ft_strcmp(obj->type, "cylinder")))
	{
		if (obj->pos_c == 1 && obj->radius_c == 1 && obj->rotation_c == 1)
			return (1);
	}
	if (!(ft_strcmp(obj->type, "cone")))
	{
		if (obj->pos_c == 1 && obj->angle_c == 1 && obj->rotation_c == 1)
			return (1);
	}
	if (!(ft_strcmp(obj->type, "plane")))
	{
		if (obj->pos_c == 1 && obj->vector_c == 1)
			return (1);
	}
	return (expected_result2(obj));
}

int		compare_string_to_values(char *f, int s, t_obj *new)
{
	if (ft_strncmp(f + s, "type(", 5) == 0)
		return (get_object_type(f, s, new));
	else if (ft_strncmp(f + s, "shiny", 5) == 0)
		new->shiny = 1;
	else if (ft_strncmp(f + s, "pos(", 4) == 0)
		return (get_object_pos(f, s, new));
	else if (ft_strncmp(f + s, "radius(", 7) == 0)
		return (get_object_rad(f, s, new));
	else if (ft_strncmp(f + s, "angle(", 6) == 0)
		return (get_object_angle(f, s, new));
	else if (ft_strncmp(f + s, "vector(", 7) == 0)
		return (get_object_vec(f, s, new));
	else if (ft_strncmp(f + s, "rotation(", 9) == 0)
		return (get_object_rot(f, s, new));
	else if (ft_strncmp(f + s, "color(", 6) == 0)
		return (get_object_color(f, s, new));
	else if (ft_strncmp(f + s, "lim_x(", 6) == 0)
		return (get_object_lim_x(f, s, new));
	else if (ft_strncmp(f + s, "lim_y(", 6) == 0)
		return (get_object_lim_y(f, s, new));
	else if (ft_strncmp(f + s, "lim_z(", 6) == 0)
		return (get_object_lim_z(f, s, new));
	else if (ft_strncmp(f + s, "size(", 5) == 0)
		return (get_object_size(f, s, new));
	return (0);
}

int		read_object_var(char *f, int s, t_obj *new)
{
	new->type = NULL;
	while (f[s] && (f[s] != '}'))
	{
		if (ft_isalpha(f[s]))
			compare_string_to_values(f, s, new);
		s++;
	}
	if (f[s] != '}' || expected_result(new) != 1)
		return (-1);
	return (1);
}

int		read_object(t_data *d, char *f, int s)
{
	t_obj	*new;
	int		result;

	new = create_object(d);
	new->type = NULL;
	result = read_object_var(f, s, new);
	if (new->type == NULL || result != 1)
	{
		if (new->type != NULL)
			free(new->type);
		free(new);
		return (0);
	}
	if (ft_strcmp(new->type, "cube") == 0)
	{
		fabricated_object(d, new);
		free(new->type);
	}
	else
		add_obj(d, new);
	return (1);
}
