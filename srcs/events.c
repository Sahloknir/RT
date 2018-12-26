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

int		close_program(t_data *d)
{
	if (d)
		exit(0);
	exit(0);
}

int		key_release(int key, void *d)
{
	if (key == 53 || key == 12)
		close_program(d);
	return (1);
}

int		refresh_expose(t_data *d)
{
	mlx_put_image_to_window(d->mlx_ptr, d->win_ptr, d->img->ptr, 0, 0);
	return (0);
}
