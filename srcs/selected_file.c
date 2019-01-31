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

void	blend_colors(t_data *d, int x, int y)
{
	t_color	blend1;
	t_color	blend2;
	t_color	blend3;

			blend1 = d->pix_col[y][x];
			blend2 = d->pix_col[y][x];
			blend3 = d->pix_col[y][x];
	if (y > 0)
		blend1 = real_lerp(d->pix_col[y][x], d->pix_col[y - 1][x], 60);
	if (y < HA - 1)
		blend2 = real_lerp(d->pix_col[y][x], d->pix_col[y + 1][x], 60);
	blend1 = real_lerp(blend1, blend2, 50);
	blend2 = d->pix_col[y][x];
	if (x > 0)
		blend2 = real_lerp(d->pix_col[y][x], d->pix_col[y][x - 1], 60);
	if (x < LA - 1)
		blend3 = real_lerp(d->pix_col[y][x], d->pix_col[y][x + 1], 60);
	blend2 = real_lerp(blend2, blend3, 50);
	d->pix_col[y][x] = real_lerp(blend1, blend2, 50);
}

void	anti_aliasing(t_data *d)
{
	t_dot	t;
	int		y;
	int		x;
	int		itr;

	itr = -1;
	while (++itr < 6)
	{
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
	if (d->objects > 0)
		anti_aliasing(d);
	d->current_img = 1;
	refresh_expose(d);
	return (1);
}
