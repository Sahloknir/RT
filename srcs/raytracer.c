/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raytracer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: axbal <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/13 13:16:31 by axbal             #+#    #+#             */
/*   Updated: 2018/11/13 13:29:54 by axbal            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

int		test_object(t_data *d, t_vec ray, t_obj *obj)
{
	int		ret;

	d->t[0] = -1;
	d->t[1] = -1;
	ret = 0;
	if (ft_strcmp(obj->type, "sphere") == 0)
		ret = solve_sphere(d, ray, obj);
	if (ft_strcmp(obj->type, "plane") == 0)
		ret = solve_plane(d, ray, obj);
	if (ft_strcmp(obj->type, "cylinder") == 0)
		ret = solve_cyli(d, ray, obj);
	if (ft_strcmp(obj->type, "cone") == 0)
		ret = solve_cone(d, ray, obj);
	if (ret == 1 && (d->t[0] >= 0 || d->t[1] >= 0))
		return (1);
	return (0);
}

t_rtc	ft_raytracer(t_rtc r, t_data *d)
{
	if (test_object(d, d->rays[r.i][r.j], d->obj[r.obj_i]) > 0)
	{
		r.stamp = r.dm;
		if (r.dm == -1 || (d->t[0] < r.dm && d->t[0] >= 0)
			|| (d->t[1] < r.dm && d->t[1] >= 0))
		{
			if (r.dm == -1)
			{
				if (d->t[0] >= 0)
					r.dm = d->t[0];
				if (d->t[1] >= 0)
					r.dm = d->t[0] < d->t[1] ? r.dm : d->t[1];
			}
			else
			{
				if (d->t[0] >= 0 && d->t[0] < r.dm)
					r.dm = d->t[0];
				if (d->t[1] >= 0 && d->t[1] < d->t[0] && d->t[1] < r.dm)
					r.dm = d->t[1];
			}
			if (r.stamp != r.dm)
				r.o = d->obj[r.obj_i];
		}
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
					d, r.o);
				put_pixel_to_image(new_dot(r.j, r.i, 0), d, d->img->str, c);
			}
		}
	}
}
