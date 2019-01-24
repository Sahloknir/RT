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

void	free_data(t_data *d)
{
	int		j;

	ft_putstr("clear1\n");
	if (d->file_name != NULL)
		free(d->file_name);
	d->file_name = NULL;
	ft_putstr("clear2\n");
	j = -1;
	while (d->lights > 0 && ++j < d->lights)
	{
		free(d->light[j]);
		d->light[j] = NULL;
	ft_putstr("clear3\n");
	}
	if (d->light != NULL)
		free(d->light);
	ft_putstr("clear4\n");
	j = -1;
	while (d->objects > 0 && ++j < d->objects)
		free_obj(d->obj[j]);
	ft_putstr("clear5\n");
	if (d->objects > 0 && d->cam != NULL && d->rays != NULL)
		free_rays(d);
	ft_putstr("clear6\n");
	if (d->cam != NULL)
		free(d->cam);
	ft_putstr("clear7\n");
	d->cam = NULL;
	d->light = NULL;
	d->rays = NULL;
	d->objects = 0;
	d->lights = 0;
	ft_putstr("clear8\n");
	d->current_img = d->img0;
	mlx_put_image_to_window(d->mlx_ptr, d->win_ptr, d->img0->ptr, 0, 0);
}
