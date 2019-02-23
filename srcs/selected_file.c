#include "rtv1.h"
#include <math.h>

int		simp_clr(int clr)
{
	if (clr <= 0)
		return (0);
	if (clr < 50)
		return (25);
	if (clr <= 75)
		return (75);
	if (clr <= 125)
		return (100);
	if (clr <= 150)
		return (150);
	if (clr <= 175)
		return (175);
	if (clr <= 215)
		return (200);
	if (clr <= 230)
		return (230);
	if (clr <= 245)
		return (245);
	return (255);
}

void	blend_grey(t_data *d, int x, int y)
{
	t_color	color;
	int		l;

	l = d->pix_col[y][x].r * 0.2126 + d->pix_col[y][x].g * 0.7152 + d->pix_col[y][x].b * 0.0722;
	color = new_color(l, l, l, 0);
	d->pix_col[y][x] = color;
}

void	blend_sepia(t_data *d, int x, int y)
{
	float	ou_red;
	float	ou_blue;
	float	ou_green;
	t_color	color;

	ou_red = ft_clamp((d->pix_col[y][x].r * 0.333) + (d->pix_col[y][x].g
		* 0.769) + (d->pix_col[y][x].b * 0.189), 0, 255);
	ou_green = ft_clamp((d->pix_col[y][x].r * 0.349) + (d->pix_col[y][x].g
		* 0.686) + (d->pix_col[y][x].b * 0.168), 0, 255);
	ou_blue = ft_clamp((d->pix_col[y][x].r * 0.272) + (d->pix_col[y][x].g
		* 0.534) + (d->pix_col[y][x].b * 0.131), 0, 255);
	color = new_color((int)ou_red, (int)ou_green, (int)ou_blue, 0);
	d->pix_col[y][x] = color;
}

void	filter(t_data *d)
{
	t_dot	t;
	int		y;
	int		x;

		y = -1;
		while (++y < HA)
		{
			x = -1;
			t.y = y;
			while (++x < LA)
			{
				t.x = x;
				if (d->img->crtn)
					d->pix_col[y][x] = new_color(simp_clr(d->pix_col[y][x].r), simp_clr(d->pix_col[y][x].g), simp_clr(d->pix_col[y][x].b), 0);
				if (d->img->sp)
					blend_sepia(d, x, y);
				else if (d->img->gs)
					blend_grey(d, x, y);
				put_pixel_to_image(t, d, d->img->str, d->pix_col[y][x]);
			}
		}
}

int		open_selected_choice(t_data *d)
{
	char	*str;

	if (d)
		free_data(d);
	d->file_name = ft_strdup(d->files[d->selected_choice]);
	str = ft_strjoin(SCENES_PATH, d->files[d->selected_choice]);
	check_file(d, str);
	free(str);
	return (0);
}

int		check_file(t_data *d, char *file)
{
	d->current_img = 2;
	file = start_reading(file);
	read_file(d, file);
	if (d->current_img != 2)
		ft_return("Error: Reading error occurred.", d);
	refresh_expose(d);
	if (d->objects != 0 && d->cam != NULL)
		start_raytracing(d);
	if (d->cam == NULL)
	{
		ft_return("Error: No valid camera. Cannot draw the scene.", d);
		ft_putchar('\a');
		return (-1);
	}
	else if (d->objects == 0)
		ft_putstr_fd("No object to draw! Enjoy the black screen!\n", 2);
	if (d->objects > 0 && (d->img->sp || d->img->gs || d->img->crtn))
		filter(d);
	d->current_img = 1;
	refresh_expose(d);
	return (1);
}
