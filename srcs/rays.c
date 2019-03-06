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
#include <pthread.h>

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

void	*mt_rays(void *data)
{
	t_data *d;
	t_dot	p1;
	t_dot	p2;
	int		i;
	int		j;

	d = data;
	i = d->start - 1;
	p1 = new_dot(0, 0, 0);
	while (++i < d->limit)
	{
		j = 0;
		while (j < LA)
		{
			p2 = new_dot(j - LA / 2, -i + HA / 2, LA / (2 * (tan(FOV / 2))));
			d->rays[i][j] = two_point_vector(p1, p2);
			norm_vec(&(d->rays[i][j]));
			j++;
		}
	}
	return (data);
}

void	gen_rays(t_data *d)
{
	pthread_t	thread_tab[4];
	int			calcul;
	int			thread_nb;

	thread_nb = 4;
	calcul = HA / thread_nb;
	d->start = 0;
	d->limit = calcul;
	malloc_rays(d);
	thread_nb -= 1;
	while (thread_nb >= 0)
	{
		if (pthread_create(&thread_tab[thread_nb], NULL, &mt_rays, d) != 0)
			ft_fail("Error: Multi-threading failed.", d);
		pthread_join(thread_tab[thread_nb], NULL);
		d->start += calcul;
		d->limit += calcul;
		thread_nb -= 1;
	}
	rot_rays(d);
}
