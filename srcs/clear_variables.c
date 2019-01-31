#include "rtv1.h"

void	free_obj(int j, t_data *d)
{
	if (d->obj[j]->vector_c != 0)
		free(d->obj[j]->v);
	d->obj[j]->vector_c = 0;
	free(d->obj[j]);
	d->obj[j] = NULL;
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
	d->cam = NULL;
	d->obj = NULL;
	d->light = NULL;
	d->rays = NULL;
	d->objects = 0;
	d->lights = 0;
	d->a = new_color(0, 0, 0, 1);
	d->current_img = 0;
	ft_memset(d->img->str, 0, (LA - 1) * d->img->bpp + (HA - 1) * d->img->s_l);
	ft_memset(d->img2->str, 0, (LA - 1) * d->img2->bpp + (HA - 1) * d->img2->s_l);
	loading_screen_bar(d);
	refresh_expose(d);
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
	if (d->objects > 0 && d->cam != NULL && d->rays != NULL)
		free_rays(d);
	if (d->cam != NULL)
		free(d->cam);
	clear_images(d);
}
