/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raytracer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: axbal <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/13 13:16:31 by axbal             #+#    #+#             */
/*   Updated: 2019/02/23 16:02:22 by axbal            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

t_rtc	ft_raytracer(t_rtc r, t_data *d)
{
	if (test_object(d, d->rays[r.i][r.j], d->obj[r.obj_i], d->cam->pos) > 0)
	{
		r.stamp = r.dm;
		r.dm = pick_a_side(r.dm, d->rays[r.i][r.j], d->obj[r.obj_i], d);
		if (r.stamp != r.dm)
			r.o = d->obj[r.obj_i];
	}
	return (r);
}

void	loading_screen_bar(t_data *d)
{
	t_dot	dot;

	dot.x = LA / 5;
	while (++dot.x < LA / 5 + HA)
	{
		dot.y = HA -15;
		while (++dot.y < HA - 11)
			put_pixel_to_image(dot, d, d->img2->str, d->blue);
	}
}

void	loading_screen_update(t_data *d, int h)
{
	t_dot	dot;

	dot = new_dot(LA / 5 + h, HA - 15, 0);
	while (++dot.y < HA - 11)
		put_pixel_to_image(dot, d, d->img2->str, d->green);
	if (h % 28 == 0)
	{
		mlx_put_image_to_window(d->mlx_ptr, d->win_ptr, d->img2->ptr, 0, 0);
		mlx_do_sync(d->mlx_ptr);
	}
}

void	start_raytracing(t_data *d)
{
	t_rtc	r;
	t_color	c;

	d->current_img = 2;
	r.i = -1;
	gen_rays(d);
	while (++r.i < HA)
	{
		r.j = -1;
		while (++r.j < LA)
		{
			r.dm = -1;
			r.o = NULL;
			r.obj_i = -1;
			while (++r.obj_i <= d->objects - 1)
				r = ft_raytracer(r, d);
			if (r.dm > -1)
			{
				c = secondary_rays(get_hitpoint(d->cam->pos, d->rays[r.i][r.j],
					r.dm), d, r.o, d->rays[r.i][r.j]);
				put_pixel_to_image(new_dot(r.j, r.i, 0), d, d->img->str, c);
				d->pix_col[r.i][r.j] = c;
			}
		}
		loading_screen_update(d, r.i);
	}
}
