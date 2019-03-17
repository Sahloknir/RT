/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clear_variables.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ceugene <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/27 12:37:36 by ceugene           #+#    #+#             */
/*   Updated: 2019/03/16 14:47:51 by axbal            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void	free_obj(int j, t_data *d)
{
	if (d->obj[j]->vector_c == 1)
		free(d->obj[j]->v);
	free(d->obj[j]);
	d->obj[j] = NULL;
}

void	free_neg(t_data *d)
{
	int		j;

	j = -1;
	while (++j < d->negs)
	{
		if (d->neg[j]->vector_c == 1)
			free(d->neg[j]->v);
		free(d->neg[j]);
		d->neg[j] = NULL;
	}
	if (d->neg != NULL)
		free(d->neg);
	d->neg = NULL;
	d->negs = 0;
}

void	free_rays(t_data *d)
{
	int		j;

	j = -1;
	while (++j < HA)
	{
		free(d->rays[j]);
		d->rays[j] = NULL;
	}
	if (d->rays)
		free(d->rays);
}

void	clear_images(t_data *d)
{
	d->obj = NULL;
	d->light = NULL;
	d->rays = NULL;
	d->objects = 0;
	d->negs = 0;
	d->lights = 0;
	d->a = new_color(0, 0, 0, 1);
	d->current_img = 0;
	ft_memset(d->img->str, 0, (LA - 1) * d->img->bpp + (HA - 1)
		* d->img->s_l);
	ft_memset(d->img2->str, 0, (LA - 1) * d->img2->bpp + (HA - 1)
		* d->img2->s_l);
		loading_screen_bar(d);
	reset_colors(d);
	refresh_expose(d);
	d->selected_option = -1;
}

void	free_data(t_data *d)
{
	int		j;

	if (d->file_name != NULL)
		free(d->file_name);
	d->file_name = NULL;
	j = -1;
	while (d->lights > 0 && ++j < d->lights)
	{
		free(d->light[j]);
		d->light[j] = NULL;
	}
	if (d->light != NULL)
		free(d->light);
	j = -1;
	while (d->obj && d->objects > 0 && ++j < d->objects)
		free_obj(j, d);
	if (d->obj != NULL)
		free(d->obj);
	free_neg(d);
	if (d->objects > 0 && d->cam != NULL && d->rays != NULL)
		free_rays(d);
	if (d->cam != NULL)
		free(d->cam);
	d->cam = NULL;
	if (d->img0 != NULL)
		clear_images(d);
}
