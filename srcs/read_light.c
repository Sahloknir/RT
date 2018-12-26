/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_light.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: axbal <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/15 10:27:47 by axbal             #+#    #+#             */
/*   Updated: 2018/11/13 13:30:22 by axbal            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

void	copy_lights(t_data *data, t_light **tmp)
{
	int		i;

	i = 0;
	while (i < data->lights)
	{
		tmp[i] = data->light[i];
		i++;
	}
}

void	assign_light(t_data *data, t_light *light)
{
	t_light		**tmp;

	if (!(tmp = (t_light **)malloc(sizeof(t_light *) * (data->lights + 1))))
		ft_fail("Error: Could not allocate memory.", data);
	if (data->lights > 0)
	{
		copy_lights(data, tmp);
		free(data->light);
	}
	data->light = tmp;
	data->light[data->lights] = light;
	data->lights++;
}

int		get_light_pos(char *file, int select, t_light *light)
{
	float	*tab;

	tab = three_values_tab(file, select);
	select = tab[4];
	if (tab[3] != 3 || file[select] != ')')
	{
		free(tab);
		return (-1);
	}
	light->px = tab[0];
	light->py = tab[1];
	light->pz = tab[2];
	light->intensity = 100;
	free(tab);
	return (select);
}

int		read_light(t_data *data, char *file, int select)
{
	t_light		*light;

	if (!(light = (t_light *)malloc(sizeof(t_light))))
		ft_fail("Error: Could not allocate memory.", data);
	while (file[select] && file[select] != '}')
	{
		if (ft_strncmp(file + select, "pos(", 4) == 0)
		{
			if ((select = get_light_pos(file, select, light)) == -1)
				break ;
		}
		select++;
	}
	if (select != -1)
		assign_light(data, light);
	else
		free(light);
	return (select);
}
