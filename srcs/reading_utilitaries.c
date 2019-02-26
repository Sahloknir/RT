/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reading_utilitaries.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: axbal <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/23 16:10:34 by axbal             #+#    #+#             */
/*   Updated: 2019/02/23 16:18:17 by axbal            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"
#include <fcntl.h>

float		ft_atof(const char *str)
{
	int		s;
	int		virgule;
	float	result;
	int		levier;

	s = 0;
	result = 0;
	levier = 1;
	virgule = 0;
	while (str[s] == '\f' || str[s] == '\n' || str[s] == ' '
		|| str[s] == '\t' || str[s] == '\r' || str[s] == '\v')
		s++;
	if (str[s] == '-')
		levier = -1;
	if (str[s] == '-' || str[s] == '+')
		s++;
	while (str[s] >= '0' && str[s] <= '9')
	{
		result = result * 10 + (str[s++] - '0');
		if (str[s] == '.')
			virgule = s++;
	}
	while (virgule != 0 && ft_isdigit(str[++virgule]))
		levier = levier * 10;
	return (result / levier);
}

int			ft_increase_file(char **file, char *line)
{
	char	*copy;

	if (*file == NULL)
	{
		if (!(*file = ft_strdup(line)))
			return (-1);
		free(line);
		return (1);
	}
	if (!(copy = ft_strdup(*file)))
		return (-1);
	free(*file);
	if (!(*file = ft_strnew(ft_strlen(copy) + ft_strlen(line))))
		return (-1);
	ft_strcpy(*file, copy);
	free(copy);
	ft_strcat(*file, line);
	free(line);
	return (1);
}

char		*start_reading(char *str)
{
	int		fd;
	int		ret;
	char	*file;
	char	*line;

	file = NULL;
	fd = open(str, O_RDONLY);
	if (fd < 0)
	{
		ft_putstr_fd("Error: No file '", 2);
		ft_putstr_fd(str, 2);
		ft_fail("' found.", NULL);
	}
	while ((ret = get_next_line(fd, &line)) > 0)
	{
		if (ft_increase_file(&file, line) == -1)
			ft_fail("Error: An error occurred.", NULL);
	}
	close(fd);
	if (ret <= -1 || (file && ft_strlen(file) >= (163840)))
		ft_fail("Error: File is too big or is a directory.", NULL);
	if (!file || ft_strlen(file) == 0)
		ft_fail("Error: File is empty.", NULL);
	return (file);
}

void		get_vec(t_obj *o)
{
	t_vec	v;
	t_vec	*vec;

	v = new_vec(0, 0, 1);
	v = rot_vec(v, o->rx, o->ry, 0);
	if (!(vec = (t_vec *)malloc(sizeof(t_vec) * 1)))
		ft_fail("Error: Could not allocate memory.", NULL);
	vec->x = v.x;
	vec->y = v.y;
	vec->z = v.z;
	o->vector_c += 1;
	o->v = vec;
}

int			get_object_rot(char *f, int s, t_obj *obj)
{
	float	*tab;

	tab = three_values_tab(f, s);
	if (!(f[(int)tab[4]]) || tab[3] != 2)
	{
		free(tab);
		return (0);
	}
	obj->rx = tab[0];
	obj->ry = tab[1];
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
