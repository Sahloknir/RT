#include "rtv1.h"

void	draw_menu0(t_img *img, t_data *d)
{
	t_color		c;
	t_dot		dot;
	int			x;
	int			y;

	c = new_color(200, 180, 100, 1);
	y = -1;
	while (++y < HA)
	{
		x = -1;
		dot.y = y;
		while (++x < LA)
		{
			dot.x = x;
			put_pixel_to_image(dot, d, img->str, c);
		}
	}
}

void	write_menu(t_data *d)
{
	char	*s_string;
	int		choice;

	choice = d->selected_choice - 1;
	if (choice < 0)
		choice = d->dir_files - 1;
	s_string = ft_strdup(d->files[choice]);
	mlx_string_put(d->mlx_ptr, d->win_ptr, LA / 8 - (ft_strlen(s_string) * 2.5), HA / 1.76, 0xCCCCCCCC, s_string);
	free(s_string);
	choice = d->selected_choice;
	s_string = ft_strdup(d->files[choice]);
	if (d->selected_option == -1)
		mlx_string_put(d->mlx_ptr, d->win_ptr, LA / 2.1 - (ft_strlen(s_string) * 2.5), HA / 1.6, 0xAAFFFAA, s_string);
	else
		mlx_string_put(d->mlx_ptr, d->win_ptr, LA / 2.1 - (ft_strlen(s_string) * 2.5), HA / 1.6, 0xCCCCCCCC, s_string);
	free(s_string);
	choice = d->selected_choice + 1;
	if (choice >= d->dir_files)
		choice = 0;
	s_string = ft_strdup(d->files[choice]);
	mlx_string_put(d->mlx_ptr, d->win_ptr, LA - LA / 5 - (ft_strlen(s_string) * 2.5), HA / 1.76, 0xCCCCCCC, s_string);
	free(s_string);
	s_string = ft_strdup("options");
	if (d->selected_option == -1)
		mlx_string_put(d->mlx_ptr, d->win_ptr, LA / 2.1 - (ft_strlen(s_string) * 2.5), HA / 1.3, 0xCCCCCCCC, s_string);
	else
		mlx_string_put(d->mlx_ptr, d->win_ptr, LA / 2.1 - (ft_strlen(s_string) * 2.5), HA / 1.3, 0xAAFFFAA, s_string);
	free(s_string);
}

void	set_up_menu(t_data *d)
{
	d->menu = 0;
	d->selected_choice = 0;
	d->img0 = init_img(d);
	draw_menu0(d->img0, d);
	write_menu(d);
}
