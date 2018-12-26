/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_cam.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: axbal <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/13 13:16:58 by axbal             #+#    #+#             */
/*   Updated: 2018/11/13 13:30:07 by axbal            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

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
	cam->px = tab[0];
	cam->py = tab[1];
	cam->pz = tab[2];
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
	cam->rx = tab[0];
	cam->ry = tab[1];
	cam->rz = tab[2];
	free(tab);
	return (1);
}

int		read_camera2(char *file, int select, t_cam *new)
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
	result = read_camera2(file, select, new);
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
