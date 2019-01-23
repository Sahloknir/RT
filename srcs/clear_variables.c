#include "rtv1.h"

void	free_obj(t_obj *obj)
{
	if (obj->vector_c != 0)
		free(obj->v);
	free(obj);
}

void	free_rays(t_data *d)
{
	int		j;

	j = -1;
	while (++j < HA)
		free(d->rays[j]);
	free(d->rays);
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
		free(d->light);
	}
	j = -1;
	while (d->objects > 0 && ++j < d->objects)
		free_obj(d->obj[j]);
	if (d->objects > 0 && d->cam != NULL && d->rays != NULL)
		free_rays(d);
	if (d->cam != NULL)
		free(d->cam);
	d->cam = NULL;
	d->light = NULL;
	d->rays = NULL;
	d->objects = 0;
	d->lights = 0;
	d->current_img = d->img0;
	mlx_put_image_to_window(d->mlx_ptr, d->win_ptr, d->img0->ptr, 0, 0);
}
