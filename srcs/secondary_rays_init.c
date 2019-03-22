/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   secondary_rays_init.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: axbal <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/21 14:30:06 by axbal             #+#    #+#             */
/*   Updated: 2019/03/22 14:34:19 by ceugene          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

t_color	init_c(t_data *d, t_obj *obj)
{
	t_color	c;

	c = d->lights > 0 ? new_color(d->a.r * (obj->color.r * 0.2)
		/ (d->lights + 2), d->a.g * (obj->color.g * 0.2) / (d->lights + 2),
			d->a.b * (obj->color.b * 0.2) / (d->lights + 2), 0) :
	new_color(obj->color.r, obj->color.g, obj->color.b, 0);
	return (c);
}

int		comp_c(t_color c1, t_color c2)
{
	if (c1.r == c2.r && c1.b == c2.b && c1.g == c2.g)
		return (1);
	return (0);
}

t_sec_r	*init_var_s(t_sec_r *s, t_color c, t_obj *obj, t_data *d)
{
	t_color	col2;

	d->l = d->l >= d->lights ? d->l - 1 : d->l;
	s->ret = test_object(d, s->lo, d->obj[s->i], d->light[d->l]->pos);
	if (s->ret < 1)
		return (s);
	s->dot = get_hitpoint(d->light[d->l]->pos, s->lo, d->t[0]);
	s->dot2 = get_hitpoint(d->light[d->l]->pos, s->lo, d->t[1]);
	if ((d->t[0] > 0 && d->t[0] < s->dist
		&& check_lim(d->obj[s->i], s->dot,
			newdir(d->light[d->l]->pos, s->o_ray), d) == 1)
				|| (d->t[1] > 0 && d->t[1] < s->dist
					&& check_lim(d->obj[s->i], s->dot2,
						newdir(d->light[d->l]->pos, s->o_ray), d) == 1))
	{
		if (d->obj[s->i]->trsp <= 0)
			s->lever = 1;
		col2 = real_lerp(c, find_diffuse(s->col, s->inter, obj, d),
			d->obj[s->i]->trsp);
		if ((!comp_c(s->col, c) && (col2.r <= s->col.r || col2.g <= s->col.g
			|| col2.b <= s->col.b)) || comp_c(s->col, c))
			s->col = new_color(col2.r, col2.g, col2.b, 0);
	}
	return (s);
}

t_color	find_c(t_sec_r *s, t_color c, t_obj *obj, t_data *d)
{
	if ((obj->trsp <= 0 && (obj->lim_x_c || obj->lim_y_c || obj->lim_z_c) &&
	call_side_light_check(*s, obj, d) == -1) || (d->lights == 0))
		return (c);
	s->col = new_color(c.r, c.g, c.b, 0);
	s->lever = 0;
	while (++(s->i) < d->objects)
	{
		s = init_var_s(s, c, obj, d);
		if (s->lever == 1)
			break ;
		if (s->i == d->objects - 1)
		{
			if (s->col.r != c.r || s->col.g != c.g || s->col.b != c.b)
				return (s->col);
			c = find_diffuse(c, s->inter, obj, d);
			s->tab[s->tab_size] = d->l;
			s->tab_size++;
		}
	}
	return (c);
}
