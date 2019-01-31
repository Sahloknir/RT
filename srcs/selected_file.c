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
	d->current_img = 1;
	refresh_expose(d);
	return (1);
}
