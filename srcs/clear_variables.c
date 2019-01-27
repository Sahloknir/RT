#include "rtv1.h"

void	free_obj(t_obj *obj)
{
	if (obj->vector_c != 0)
		free(obj->v);
	if (obj)
		free(obj);
}

void	free_rays(t_data *d)
{
	int		j;

	j = -1;
	while (++j < HA)
		free(d->rays[j]);
	if (d->rays)
		free(d->rays);
}

void	clear_images(t_data *d)
{
	d->cam = NULL;
	d->light = NULL;
	d->rays = NULL;
	d->objects = 0;
	d->lights = 0;
	d->current_img = 0;
	mlx_put_image_to_window(d->mlx_ptr, d->win_ptr, d->img0->ptr, 0, 0);
	ft_strclr(d->img->str);
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
	while (d->objects > 0 && ++j < d->objects)
		free_obj(d->obj[j]);
	if (d->objects > 0 && d->cam != NULL && d->rays != NULL)
		free_rays(d);
	if (d->cam != NULL)
		free(d->cam);
	clear_images(d);
}
