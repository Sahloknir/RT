/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raytracer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: axbal <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/13 13:16:31 by axbal             #+#    #+#             */
/*   Updated: 2019/01/08 13:21:59 by axbal            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

t_rtc	ft_raytracer(t_rtc r, t_data *d)
{
	if (test_object(d, d->rays[r.i][r.j], d->obj[r.obj_i]) > 0)
	{
		r.stamp = r.dm;
		r.dm = pick_a_side(r.dm, d->rays[r.i][r.j], d->obj[r.obj_i], d);
		if (r.stamp != r.dm)
			r.o = d->obj[r.obj_i];
	}
	return (r);
}

void	start_raytracing(t_data *d)
{
	t_rtc	r;
	t_color	c;

	r.i = -1;
	r.obj_i = 0;
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
				c = secondary_rays(get_hitpoint(d->rays[r.i][r.j], r.dm, d),
					d, r.o, d->rays[r.i][r.j]);
				put_pixel_to_image(new_dot(r.j, r.i, 0), d, d->img->str, c);
			}
		}
	}
}
