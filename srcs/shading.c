/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shading.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: axbal <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/13 13:17:13 by axbal             #+#    #+#             */
/*   Updated: 2019/03/18 16:32:15 by axbal            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"
#include <math.h>

t_color		apply_color_effects(t_color c, t_sec_r s, t_data *d, t_obj *o)
{
	t_color	col;
	int		i;

	if (d->img->d5 > 0)
		c = perlin(d, c.r, c.g, c.b, s.inter);
	if (o->d3)
		c = checkered(o, s.inter, c, new_color(1 + (c.r + 1) / 2, 1
			+ (c.g + 1) / 2, 1 + (c.b + 1) / 2, 0));
	i = -1;
	col = new_color(c.r, c.g, c.b, 0);
	while (++i < s.tab_size)
	{
		s.lo = two_point_vector(d->light[s.tab[i]]->pos, s.inter);
		col = add_shine(s, o, c, col);
	}
	return (col);
}

t_color		every_lights(t_data *d, t_sec_r s, t_obj *o, t_color c)
{
	while (++(d->l) < d->lights)
	{
		s.lo = two_point_vector(d->light[d->l]->pos, s.inter);
		test_object(d, s.lo, o, d->light[d->l]->pos);
		s.dist = find_right_distance(d, d->light[d->l]->pos, s.lo, s.inter);
		s.i = -1;
		c = find_c(&s, c, o, d);
	}
	c = apply_color_effects(c, s, d, o);
	return (c);
}

t_color		secondary_rays(t_dot inter, t_data *d, t_obj *o, t_vec ray)
{
	t_sec_r	s;
	t_color	c;

	s.inter = inter;
	if (!(s.tab = malloc(sizeof(int) * d->lights)))
		ft_fail("Error: Unable to allocate memory.", d);
	d->l = -1;
	s.tab_size = 0;
	c = init_c(d, o);
	s.o_ray = ray;
	c = every_lights(d, s, o, c);
	if (o->mirror > 0 && o->mirror < 100)
		c = real_lerp(c, find_reflection(c, s, o, d), o->mirror);
	if (o->trsp > 0)
		c = real_lerp(c, transparent(c, d, s, o), o->trsp);
	free(s.tab);
	return (c);
}
