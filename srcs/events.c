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

int		key_release(int key, void *d)
{
	if (key == 53)
		close_program(d);
	else if (key == 12)
		free_data(d);
	else if (key == 1)
		screenshot(d);
	return (1);
}

int		refresh_expose(t_data *d)
{
	mlx_put_image_to_window(d->mlx_ptr, d->win_ptr, d->current_img, 0, 0);
	return (0);
}
