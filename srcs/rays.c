/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rays.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: axbal <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/13 13:15:40 by axbal             #+#    #+#             */
/*   Updated: 2019/02/23 15:05:02 by axbal            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"
#include <math.h>

void	rot_rays(t_data *d)
{
	int		i;
	int		j;

	i = 0;
	while (i < HA)
	{
		j = 0;
		while (j < LA)
		{
			d->rays[i][j] = rot_vec(d->rays[i][j], d->cam->vec.x, d->cam->vec.y,
				d->cam->vec.z);
			j++;
		}
		i++;
	}
}

void	malloc_rays(t_data *d)
{
	int		i;

	i = 0;
	if (!(d->rays = (t_vec **)malloc(sizeof(t_vec *) * HA)))
		ft_fail("Error: could not allocate memory.", d);
	while (i < HA)
	{
		if (!(d->rays[i] = (t_vec *)malloc(sizeof(t_vec) * LA)))
			ft_fail("Error: could not allocate memory.", d);
		i++;
	}
}

void	gen_rays(t_data *d)
{
	int		i;
	int		j;
	t_dot	p1;
	t_dot	p2;

	i = 0;
	p1 = new_dot(0, 0, 0);
	malloc_rays(d);
	while (i < HA)
	{
		j = 0;
		while (j < LA)
		{
			p2 = new_dot(j - LA / 2, -i + HA / 2, LA / (2 * (tan(FOV / 2))));
			d->rays[i][j] = two_point_vector(p1, p2);
			norm_vec(&(d->rays[i][j]));
			j++;
		}
		i++;
	}
	rot_rays(d);
}
