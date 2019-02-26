/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_cam.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: axbal <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/13 13:16:58 by axbal             #+#    #+#             */
/*   Updated: 2019/02/23 15:06:24 by axbal            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

int		search_pos_cam(t_cam *cam, char *f, int s)
{
	float	*tab;

	tab = three_values_tab(f, s);
	s = (int)tab[4];
	if (!(f[s]) || (int)tab[3] != 3 || f[s] != ')')
	{
		free(tab);
		return (-1);
	}
	cam->pos.x = tab[0];
	cam->pos.y = tab[1];
	cam->pos.z = tab[2];
	free(tab);
	return (1);
}

int		search_dir_cam(t_cam *cam, char *f, int s)
{
	float	*tab;

	tab = three_values_tab(f, s);
	s = (int)tab[4];
	if (!(f[s]) || (int)tab[3] != 3 || f[s] != ')')
	{
		free(tab);
		return (-1);
	}
	cam->vec.x = tab[0];
	cam->vec.y = tab[1];
	cam->vec.z = tab[2];
	free(tab);
	return (1);
}

int		read_ambient(char *f, int s, t_data *d)
{
	float	*tab;

	tab = three_values_tab(f, s);
	if (!(f[(int)tab[4]]) || tab[3] != 3)
	{
		free(tab);
		return (-1);
	}
	else if (tab[0] > 0 && tab[1] > 0 && tab[2] > 0 && tab[0] < 255
		&& tab[1] < 255 && tab[2] < 255)
		d->a = new_color(tab[0] / 10 / 2, tab[1] / 10 / 2, tab[2] / 10 / 2, 0);
	free(tab);
	return (0);
}

int		read_camera2(char *file, int select, t_cam *new, t_data *d)
{
	int		pos;
	int		dir;
	char	*word;

	pos = 0;
	dir = 0;
	while (file[select] && file[select] != '}')
	{
		word = NULL;
		if (ft_isalpha(file[select]))
			word = word_return(file, select);
		if (word != NULL)
		{
			select += ft_strlen(word);
			if (!(ft_strcmp(word, "pos")))
				pos = search_pos_cam(new, file, select);
			else if (!(ft_strcmp(word, "rotation")))
				dir = search_dir_cam(new, file, select);
			else if (!(ft_strcmp(word, "ambient")))
				read_ambient(file, select, d);
			free(word);
		}
		select++;
	}
	return (pos + dir);
}

int		read_camera(t_data *data, char *file, int select)
{
	t_cam	*new;
	int		result;

	if (!(new = (t_cam *)malloc(sizeof(t_cam) * 1)))
		ft_fail("Error: Could not allocate memory.", data);
	result = read_camera2(file, select, new, data);
	if (result == 2 && data->cam != NULL)
	{
		free(new);
		ft_fail("Error: Several valid cameras detected.", data);
	}
	if (result == 2)
		data->cam = new;
	else
		free(new);
	return (select);
}
