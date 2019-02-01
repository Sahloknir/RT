#include "rtv1.h"

void	reset_colors(t_data *d)
{
	int		y;
	int		x;

	y = -1;
	while (++y < HA)
	{
		x = -1;
		while (++x < LA)
			d->pix_col[y][x] = new_color(0, 0, 0, 0);
	}
}

void	malloc_colors(t_data *d)
{
	int		i;

	i = 0;
	if (!(d->pix_col = (t_color **)malloc(sizeof(t_color *) * HA)))
		ft_fail("Error: could not allocate memory.", d);
	while (i < HA)
	{
		if (!(d->pix_col[i] = (t_color *)malloc(sizeof(t_color) * LA)))
			ft_fail("Error: could not allocate memory.", d);
		i++;
	}
}

void	gen_colors(t_data *d)
{
	malloc_colors(d);
	reset_colors(d);
}

void	init_data(t_data *new)
{
	new->img = NULL;
	new->img2 = NULL;
	new->obj = NULL;
	new->cam = NULL;
	new->light = NULL;
	new->rays = NULL;
	new->lights = 0;
	new->objects = 0;
	new->t[0] = -1;
	new->t[1] = -1;
	new->img = init_img(new);
	new->img2 = init_img(new);
	new->green = new_color(180, 250, 180, 0);
	new->red = new_color(250, 180, 180, 0);
	new->blue = new_color(180, 180, 250, 0);
	new->a = new_color(0, 0, 0, 0);
	new->current_img = 1;
	new->file_name = NULL;
	gen_colors(new);
	new->selected_option = -1;
	new->img->aa = 0;
}
