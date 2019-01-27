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
	char	*s_middle;
	int		i;

	i = -1;
	s_middle = ft_strdup(d->files[d->selected_choice]);
	mlx_string_put(d->mlx_ptr, d->win_ptr, 40, HA / 1.76, 0xFFFFFFF, s_middle);
	free(s_middle);
//	i = -1;
//	l = d->lst;
//	while (++i != middle)
//		l = l->next;
//	mlx_string_put(d->mlx_ptr, d->win_ptr, LA / 2, HA / 2, 0xFFFFFFFF, l->content);
//	l = d->lst;
//	i = -1;
//	while (++i != right)
//		l = l->next;
//	mlx_string_put(d->mlx_ptr, d->win_ptr, LA - 10, HA / 1.76, 0xCCCCCCCC, l->content);
}

void	set_up_menu(t_data *d)
{
	d->menu = 0;
	d->selected_choice = 0;
	d->img0 = init_img(d);
	draw_menu0(d->img0, d);
	mlx_put_image_to_window(d->mlx_ptr, d->win_ptr, d->img0->ptr, 0, 0);
	write_menu(d);
}
