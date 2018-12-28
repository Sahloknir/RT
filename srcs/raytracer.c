/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raytracer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: axbal <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/13 13:16:31 by axbal             #+#    #+#             */
/*   Updated: 2018/12/27 12:09:52 by axbal            ###   ########.fr       */
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

float	pick_a_side(float dm, t_vec ray, t_obj *o, t_data *d)
{
	int		d1;
	int		d2;

	d1 = check_lim(o, get_hitpoint(ray, d->t[0], d));
	d2 = check_lim(o, get_hitpoint(ray, d->t[1], d));
	if (dm == -1 && ((d->t[0] > 0 && d1 == 1) || (d->t[1] > 0 && d2 == 1)))
	{
		if (d->t[0] > 0 && d1 == 1)
			dm = d->t[0];
		if (d->t[1] > 0 && d2 == 1 && (dm == -1 || dm > d->t[1]))
			dm = d->t[1];
	}
	else
	{
		if (d->t[0] >= 0 && d->t[0] < dm && d1 == 1)
			dm = d->t[0];
		if (d->t[1] >= 0 && d->t[1] < dm && d2 == 1)
			dm = d->t[1];
	}
	return (dm);
}

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
