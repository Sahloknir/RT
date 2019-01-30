#include "rtv1.h"
#include <math.h>

t_color		get_pixel_color(char *str, t_dot dot, t_data *d)
{
	t_color	color;
	int		px;

	px = ((int)dot.x * d->img->bpp) + ((int)dot.y * d->img->s_l);
	color.b = abs((int)str[px + 0] + 48);
	color.g = abs((int)str[px + 1] + 48);
	color.r = abs((int)str[px + 2] + 48);
	color.a = 0;
	return (color);
}

t_color	real_lerp(t_color c1, t_color c2, float factor)
{
	t_color	color;

	color.r = ft_clamp(c1.r - ((c1.r - c2.r) / ((factor / 100))), 0, 255);
	color.g = ft_clamp(c1.g - ((c1.g - c2.g) / ((factor / 100))), 0, 255);
	color.b = ft_clamp(c1.b - ((c1.b - c2.b) / ((factor / 100))), 0, 255);
	return (color);
}

void	anti_aliasing(t_data *d)
{
	t_dot	pix;
	t_color	previous;
	t_color	next;
	t_color	actual;

		pix.y = -1;
		while (++pix.y < HA)
		{
			pix.x = -1;
			previous = new_color(-1, -1, -1, 1);
			while (++pix.x < LA)
			{
				if (pix.x < LA - 1)
				{
					++pix.x;
					next = get_pixel_color(d->img->str, pix, d);
					--pix.x;
				}
				else
					next = new_color(-1, -1, -1, 1);
				actual = get_pixel_color(d->img->str, pix, d);
				if ((previous.r >= 0 || previous.b >= 0 || previous.g >= 0) && (next.r >= 0 || next.b >= 0 || next.g >= 0))
					actual = real_lerp(actual, real_lerp(previous, next, 50), 20);
				if (previous.r >= 0 || previous.g >= 0 || previous.b >= 0)
					actual = real_lerp(actual, real_lerp(actual, previous, 50), 20);
				if (next.r >= 0 || next.g >= 0 || next.b >= 0)
					actual = real_lerp(actual, real_lerp(actual, next, 50), 20);
				put_pixel_to_image(pix, d, d->img->str, actual);
				previous = actual;
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
//	anti_aliasing(d);
	d->current_img = 1;
	refresh_expose(d);
	return (1);
}
