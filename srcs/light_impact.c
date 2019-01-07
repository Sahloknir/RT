/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   light_impact.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: axbal <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/06 14:44:53 by axbal             #+#    #+#             */
/*   Updated: 2019/01/07 15:42:18 by axbal            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

int		light_cyli(t_data *d, t_light *l, t_sec_r r, t_obj *o)
{
	t_dot	q;
	t_vec	p;
	float	delta;

	p = new_vec(l->px, l->py, l->pz);
	p = trans_vec(p, o->px, o->py, o->pz);
	p = rot_vec(p, o->rx, o->ry, 0);
	r.lo = rot_vec(r.lo, o->rx, o->ry, 0);
	q.x = pow(r.lo.x, 2) + pow(r.lo.y, 2);
	q.y = 2 * p.x * r.lo.x + 2 * p.y * r.lo.y;
	q.z = pow(p.x, 2) + pow(p.y, 2) - pow(o->radius, 2);
	delta = pow(q.y, 2) - 4 * q.x * q.z;
	if (delta < 0)
		return (-1);
	else if (delta == 0)
	{
		d->t[0] = -q.y / (2 * q.x);
		return (check_lim(o, dot_from_light(l, r.lo, d->t[0])));
	}
	d->t[0] = (-q.y - sqrt(delta)) / (2 * q.x);
	d->t[1] = (-q.y + sqrt(delta)) / (2 * q.x);
	return (double_check_lim(o, dot_from_light(l, r.lo, d->t[0]),
	dot_from_light(l, r.lo, d->t[1])));
}

int		light_cone(t_data *d, t_light *l, t_sec_r r, t_obj *o)
{
	t_dot	q;
	t_vec	p;
	float	delta;

	p = new_vec(l->px, l->py, l->pz);
	p = trans_vec(p, o->px, o->py, o->pz);
	p = rot_vec(p, o->rx, o->ry, 0);
	r.lo = rot_vec(r.lo, o->rx, o->ry, 0);
	q.x = pow(r.lo.x, 2) + pow(r.lo.y, 2) - pow(r.lo.z, 2) * tan(o->angle);
	q.y = 2 * (p.x * r.lo.x) + 2 * (p.y * r.lo.y) - 2 * ((p.z * r.lo.z)
		* tan(o->angle));
	q.z = pow(p.x, 2) + pow(p.y, 2) - (pow(p.z, 2) * tan(o->angle));
	delta = pow(q.y, 2) - 4 * q.x * q.z;
	if (delta < 0)
		return (-1);
	else if (delta == 0)
	{
		d->t[0] = -q.y / (2 * q.x);
		return (check_lim(o, dot_from_light(l, r.lo, d->t[0])));
	}
	d->t[0] = (-q.y - sqrt(delta)) / (2 * q.x);
	d->t[1] = (-q.y + sqrt(delta)) / (2 * q.x);
	return (double_check_lim(o, dot_from_light(l, r.lo, d->t[0]),
	dot_from_light(l, r.lo, d->t[1])));
}

int		light_plane(t_data *d, t_light *l, t_sec_r r, t_obj *p)
{
	float	q;

	if (scalar(p->v, &r.lo) != 0)
	{
		q = -(p->v->x * p->px + p->v->y * p->py + p->v->z * p->pz);
		d->t[0] = (-(p->v->x * l->px) - p->v->y * l->py - p->v->z
		* l->pz - q) / (r.lo.x * p->v->x + r.lo.y * p->v->y + r.lo.z * p->v->z);
		if (d->t[0] < 0)
			return (-1);
		return (check_lim(p, dot_from_light(l, r.lo, d->t[0])));
	}
	return (-1);
}

int		light_sphere(t_data *d, t_light *l, t_sec_r r, t_obj *s)
{
	float	a;
	float	b;
	float	c;
	float	delta;
	t_vec	p;

	p = new_vec(l->px, l->py, l->pz);
	p = trans_vec(p, s->px, s->py, s->pz);
	a = pow(r.lo.x, 2) + pow(r.lo.y, 2) + pow(r.lo.z, 2);
	b = 2 * (p.x * r.lo.x + p.y * r.lo.y + p.z * r.lo.z);
	c = (pow(p.x, 2) + pow(p.y, 2) + pow(p.z, 2)) - pow(s->radius, 2);
	delta = pow(b, 2) - 4 * a * c;
	if (delta == 0)
	{
		d->t[0] = -b / (2 * a);
		return (check_lim(s, dot_from_light(l, r.lo, d->t[0])));
	}
	else if (delta > 0)
	{
		d->t[0] = (-b - sqrt(delta)) / (2 * a);
		d->t[1] = (-b + sqrt(delta)) / (2 * a);
		return (double_check_lim(s, dot_from_light(l, r.lo, d->t[0]),
		dot_from_light(l, r.lo, d->t[1])));
	}
	return (-1);
}

int		test_light(t_data *d, t_light *l, t_sec_r s, t_obj *obj)
{
	int		ret;

	d->t[0] = -1;
	d->t[1] = -1;
	ret = 0;
	if (ft_strcmp(obj->type, "sphere") == 0)
		ret = light_sphere(d, l, s, obj);
	if (ft_strcmp(obj->type, "plane") == 0)
		ret = light_plane(d, l, s, obj);
	if (ft_strcmp(obj->type, "cylinder") == 0)
		ret = light_cyli(d, l, s, obj);
	if (ft_strcmp(obj->type, "cone") == 0)
		ret = light_cone(d, l, s, obj);
	return (ret);
}
