#include "rt.h"

void	draw_menu0(t_img *img, t_data *d)
{
	t_color		c;
	t_dot		dot;
	int			x;
	int			y;

	c = new_color(75, 70, 117, 1);
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

int		write_options(t_data *d)
{
	char	*on;
	char	*off;
	char	*str;

	on = ft_strdup("ON");
	off = ft_strdup("OFF");
	str = ft_strdup("<- Q TO SAVE AND RETURN");
	mlx_string_put(d->mlx_ptr, d->win_ptr, LA / 7 - (ft_strlen(str) * 2.5), HA / 5, 0xCCCCCCCC, str);
	free(str);
	str = ft_strdup("sepia");
	if (d->selected_option == 1)
		mlx_string_put(d->mlx_ptr, d->win_ptr, LA / 6 - (ft_strlen(str) * 2.5), HA / 3.2, 0xAAFFFAA, str);
	else
		mlx_string_put(d->mlx_ptr, d->win_ptr, LA / 6 - (ft_strlen(str) * 2.5), HA / 3.2, 0xCCCCCCCC, str);
	if (d->img->sp == 0)
		mlx_string_put(d->mlx_ptr, d->win_ptr, LA / 1.7 - (ft_strlen(off) * 2.5), HA / 3.2, 0xFFDDDDDD, off);
	else
		mlx_string_put(d->mlx_ptr, d->win_ptr, LA / 1.7 - (ft_strlen(off) * 2.5), HA / 3.2, 0xDDFFDDDD, on);
	free(str);
	str = ft_strdup("grayscale");
	if (d->selected_option == 2)
		mlx_string_put(d->mlx_ptr, d->win_ptr, LA / 6 - (ft_strlen(str) * 2.5), HA / 2.5, 0xAAFFFAA, str);
	else
		mlx_string_put(d->mlx_ptr, d->win_ptr, LA / 6 - (ft_strlen(str) * 2.5), HA / 2.5, 0xCCCCCCCC, str);
	if (d->img->gs == 0)
		mlx_string_put(d->mlx_ptr, d->win_ptr, LA / 1.7 - (ft_strlen(off) * 2.5), HA / 2.5, 0xFFDDDDDD, off);
	else
		mlx_string_put(d->mlx_ptr, d->win_ptr, LA / 1.7 - (ft_strlen(off) * 2.5), HA / 2.5, 0xDDFFDDDD, on);
	free(str);
	str = ft_strdup("disturbance");
	if (d->selected_option == 3)
		mlx_string_put(d->mlx_ptr, d->win_ptr, LA / 6 - (ft_strlen(str) * 2.5), HA / 1.9, 0xAAFFFAA, str);
	else
		mlx_string_put(d->mlx_ptr, d->win_ptr, LA / 6 - (ft_strlen(str) * 2.5), HA / 1.9, 0xCCCCCCCC, str);
	free(str);
	if (d->img->d > 0)
	{
		str = d->img->d < 2 ? ft_strdup("sinus") : ft_strdup("squared");
		mlx_string_put(d->mlx_ptr, d->win_ptr, LA / 1.7 - (ft_strlen(str) * 2.5), HA / 1.9, 0xAAFFFAA, str);
	}
	else
	{
		str = ft_strdup("none");
		mlx_string_put(d->mlx_ptr, d->win_ptr, LA / 1.7 - (ft_strlen(str) * 2.5), HA / 1.9, 0xCCCCCCCC, str);
	}
	free(str);
	str = ft_strdup("cartoon");
	if (d->selected_option == 4)
		mlx_string_put(d->mlx_ptr, d->win_ptr, LA / 6 - (ft_strlen(str) * 2.5), HA / 1.5, 0xAAFFFAA, str);
	else
		mlx_string_put(d->mlx_ptr, d->win_ptr, LA / 6 - (ft_strlen(str) * 2.5), HA / 1.5, 0xCCCCCCCC, str);
	if (d->img->crtn == 0)
		mlx_string_put(d->mlx_ptr, d->win_ptr, LA / 1.7 - (ft_strlen(off) * 2.5), HA / 1.5, 0xFFDDDDDD, off);
	else
		mlx_string_put(d->mlx_ptr, d->win_ptr, LA / 1.7 - (ft_strlen(off) * 2.5), HA / 1.5, 0xDDFFDDDD, on);
	free(str);
	str = ft_strdup("minecraft texture");
	if (d->selected_option == 5)
		mlx_string_put(d->mlx_ptr, d->win_ptr, LA / 6 - (ft_strlen(str) * 2.5), HA / 1.3, 0xAAFFFAA, str);
	else
		mlx_string_put(d->mlx_ptr, d->win_ptr, LA / 6 - (ft_strlen(str) * 2.5), HA / 1.3, 0xCCCCCCCC, str);
	if (d->img->d4 == 0)
		mlx_string_put(d->mlx_ptr, d->win_ptr, LA / 1.7 - (ft_strlen(off) * 2.5), HA / 1.3, 0xFFDDDDDD, off);
	else
		mlx_string_put(d->mlx_ptr, d->win_ptr, LA / 1.7 - (ft_strlen(off) * 2.5), HA / 1.3, 0xDDFFDDDD, on);
	free(str);
	str = ft_strdup("perlin noise");
	if (d->selected_option == 6)
		mlx_string_put(d->mlx_ptr, d->win_ptr, LA / 6 - (ft_strlen(str) * 2.5), HA / 1.15, 0xAAFFFAA, str);
	else
		mlx_string_put(d->mlx_ptr, d->win_ptr, LA / 6 - (ft_strlen(str) * 2.5), HA / 1.15, 0xCCCCCCCC, str);
	free(str);
	if (d->img->d5 > 0)
	{
		str = d->img->d5 < 20 ? ft_strdup("strong") : ft_strdup("mild");
		mlx_string_put(d->mlx_ptr, d->win_ptr, LA / 1.7 - (ft_strlen(str) * 2.5), HA / 1.15, 0xDDFFDDDD, str);
	}
	else
	{
		str = ft_strdup("none");
		mlx_string_put(d->mlx_ptr, d->win_ptr, LA / 1.7 - (ft_strlen(str) * 2.5), HA / 1.15, 0xCCCCCCCC, str);
	}
	free(on);
	free(off);
	free(str);
return (1);
}

int		write_menu(t_data *d)
{
	char	*s_string;
	int		choice;

	choice = d->selected_choice - 1;
	if (d->selected_option > 0)
		return (write_options(d));
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
	return (1);
}

void	set_up_menu(t_data *d)
{
	d->menu = 0;
	d->selected_choice = 0;
	d->img0 = init_img(d);
	draw_menu0(d->img0, d);
	write_menu(d);
}
