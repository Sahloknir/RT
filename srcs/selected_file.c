#include "rtv1.h"
#include <math.h>

t_color	real_lerp(t_color c1, t_color c2, float factor)
{
	t_color	color;

	color.r = (int)ft_clamp(c1.r + (factor / 100) * (c2.r - c1.r), 0, 255);
	color.g = (int)ft_clamp(c1.g + (factor / 100) * (c2.g - c1.g), 0, 255);
	color.b = (int)ft_clamp(c1.b + (factor / 100) * (c2.b - c1.b), 0, 255);
	return (color);
}

int		color_diff(t_color c1, t_color c2)
{
	int		res;
	int		res2;
	int		res3;

	res = abs(c1.r - c2.r);
	res2 = abs(c1.g - c2.g);
	res3 = abs(c1.b - c2.b);
	res += res2;
	res += res3;
	return (res);
}

int		blend_colors(t_data *d, int x, int y)
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
	return (1);
}

void	sepia(t_data *d)
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
				blend_colors(d, x, y);
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
	else if (d->objects == 0)
		ft_putstr_fd("No object to draw! Enjoy the black screen!\n", 2);
	else if (d->cam == NULL)
	{
		ft_return("Error: No valid camera. Cannot draw the scene.", d);
		ft_putchar('\a');
		return (-1);
	}
	if (d->objects > 0 && d->img->sp)
		sepia(d);
	d->current_img = 1;
	refresh_expose(d);
	return (1);
}
