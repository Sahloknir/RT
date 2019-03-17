/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   objects.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: axbal <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/11 21:56:25 by axbal             #+#    #+#             */
/*   Updated: 2019/03/16 15:15:46 by axbal            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

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

void	add_neg(t_data *data, t_obj *obj)
{
	t_obj	**tmp;
	int		i;

	i = 0;
	if (!(tmp = (t_obj **)malloc(sizeof(t_obj *) * (data->negs + 1))))
		ft_fail("Error: Could not allocate memory.", data);
	while (i < data->negs)
	{
		tmp[i] = data->neg[i];
		i++;
	}
	tmp[i] = obj;
	if (data->negs > 0)
		free(data->neg);
	data->neg = tmp;
	data->negs++;
}

int		read_object_var(char *f, int s, t_obj *new)
{
	new->type = 0;
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
	result = read_object_var(f, s, new);
	if (new->type == 0 || result != 1)
	{
		free(new);
		return (0);
	}
	if (new->type == CUBE || new->type == SQUARE)
	{
		fabricated_object(d, new);
		free(new);
		return (0);
	}
	else if (new->neg == 1)
		add_neg(d, new);
	else
		add_obj(d, new);
	return (1);
}
