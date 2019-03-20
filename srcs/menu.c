/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   menu.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ceugene <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/27 12:38:25 by ceugene           #+#    #+#             */
/*   Updated: 2019/02/27 12:38:27 by ceugene          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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

int		write_menu2(t_data *d, int choice, char *s_string)
{
	free(s_string);
	if (choice >= d->dir_files)
		choice = 0;
	s_string = ft_strdup(d->files[choice]);
	ft_string(d, s_string, 0xCCCCCCC, 9);
	free(s_string);
	s_string = ft_strdup("options");
	if (d->selected_option == -1)
		ft_string(d, s_string, 0xCCCCCCC, 8);
	else
		ft_string(d, s_string, 0xAAFFFAA, 8);
	free(s_string);
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
	ft_string(d, s_string, 0xCCCCCCC, 7);
	free(s_string);
	choice = d->selected_choice;
	s_string = ft_strdup(d->files[choice]);
	if (d->selected_option == -1)
		ft_string(d, s_string, 0xAAFFFAA, 8);
	else
		ft_string(d, s_string, 0xCCCCCCC, 8);
	return (write_menu2(d, d->selected_choice + 1, s_string));
}

void	set_up_menu(t_data *d)
{
	d->menu = 0;
	d->selected_choice = 0;
	d->img0 = init_img(d);
	draw_menu0(d->img0, d);
	write_menu(d);
}
