/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: axbal <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/23 16:05:39 by axbal             #+#    #+#             */
/*   Updated: 2018/11/13 13:27:58 by axbal            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"
#include <fcntl.h>

int		close_program(t_data *d)
{
	if (d)
		free_data(d);
	exit(0);
}

int		side_keys(int key, t_data *d)
{
	if (d->current_img != 0)
		return (1);
	if (d->selected_option == -1)
	{
		if (key == 123)
			d->selected_choice--;
		else if (key == 124)
			d->selected_choice++;
		if (d->selected_choice < 0)
			d->selected_choice = d->dir_files - 1;
		else if (d->selected_choice >= d->dir_files)
			d->selected_choice = 0;
	}
	refresh_expose(d);
	return (1);
}

int		select_option(int key, t_data *d)
{
	if (d->current_img != 0)
		return (-1);
	if (d->selected_option == -1 && key == 125)
		d->selected_option = 1;
	else if (d->selected_option == 1 && key == 126)
		d->selected_option = -1;
	refresh_expose(d);
	return (1);
}

int		keys_repertory(int key, t_data *d)
{
	if (d->current_img == 1)
	{
		if (key == 12)
			ft_return(NULL, d);
		else if (key == 1)
			screenshot(d);
	}
	else if (d->current_img == 0)
	{
		if (key == 123 || key == 124)
			side_keys(key, d);
		if (key == 36)
			open_selected_choice(d);
		else if (key == 125 || key == 126)
			select_option(key, d);
	}
	return (1);
}

int		key_release(int key, void *d)
{
	if (key == 53)
		close_program(d);
	else
		keys_repertory(key, d);
	return (1);
}

int		refresh_expose(t_data *d)
{
	mlx_clear_window(d->mlx_ptr, d->win_ptr);
	if (d->current_img == 1)
		mlx_put_image_to_window(d->mlx_ptr, d->win_ptr, d->img->ptr, 0, 0);
	else if (d->current_img == 2)
		mlx_put_image_to_window(d->mlx_ptr, d->win_ptr, d->img2->ptr, 0, 0);
	else
	{
		mlx_put_image_to_window(d->mlx_ptr, d->win_ptr, d->img0->ptr, 0, 0);
		write_menu(d);
	}
	return (0);
}
