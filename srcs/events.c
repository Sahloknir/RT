/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: axbal <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/23 16:05:39 by axbal             #+#    #+#             */
/*   Updated: 2018/11/13 13:27:58 by axbal            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"
#include <fcntl.h>

void	free_obj(t_obj *obj)
{
	if (obj->vector_c != 0 && obj->v)
		free(obj->v);
	free(obj);
}

void	free_data(t_data *d)
{
	int		j;

	free(d->t);
	j = -1;
	while (d->objects > 0 && ++j <= HA)
		free(d->rays[j]);
	if (d->objects > 0 && d->rays)
		free(d->rays);
	j = -1;
	while (d->lights > 0 && ++j < d->lights)
		free(d->light[j]);
	if (d->lights > 0)
	free(d->light);
	j = -1;
	while (d->objects > 0 && ++j < d->objects)
		free_obj(d->obj[j]);
	if (d->objects > 0)
		free(d->obj);
	mlx_destroy_image(d->mlx_ptr, d->img->ptr);
}

int		close_program(t_data *d)
{
	if (d)
		free_data(d);
	mlx_destroy_window(d->mlx_ptr, d->win_ptr);
	exit(0);
}

int		key_release(int key, void *d)
{
	if (key == 53 || key == 12)
		close_program(d);
	return (1);
}

int		refresh_expose(t_data *d)
{
	mlx_put_image_to_window(d->mlx_ptr, d->win_ptr, d->img->ptr, 0, 0);
	return (0);
}
