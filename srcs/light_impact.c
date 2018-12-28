/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   light_impact.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: axbal <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/06 14:44:53 by axbal             #+#    #+#             */
/*   Updated: 2018/12/28 18:36:38 by axbal            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

int		light_cyli(t_data *d, t_light *l, t_vec ray, t_obj *o)
{
	t_dot	q;
	t_vec	p;
	float	delta;

	p = new_vec(l->px, l->py, l->pz);
	p = trans_vec(p, o->px, o->py, o->pz);
	p = rot_vec(p, o->rx, o->ry, 0);
	ray = rot_vec(ray, o->rx, o->ry, 0);
	q.x = pow(ray.x, 2) + pow(ray.y, 2);
	q.y = 2 * p.x * ray.x + 2 * p.y * ray.y;
	q.z = pow(p.x, 2) + pow(p.y, 2) - pow(o->radius, 2);
	delta = pow(q.y, 2) - 4 * q.x * q.z;
	if (delta < 0)
		return (-1);
	else if (delta == 0)
		d->t[0] = -q.y / (2 * q.x);
	else if (delta > 0)
	{
		d->t[0] = (-q.y - sqrt(delta)) / (2 * q.x);
		d->t[1] = (-q.y + sqrt(delta)) / (2 * q.x);
	}
	return (1);
}

int		light_cone(t_data *d, t_light *l, t_vec ray, t_obj *o)
{
	t_dot	q;
	t_vec	p;
	float	delta;

	p = new_vec(l->px, l->py, l->pz);
	p = trans_vec(p, o->px, o->py, o->pz);
	p = rot_vec(p, o->rx, o->ry, 0);
	ray = rot_vec(ray, o->rx, o->ry, 0);
	q.x = pow(ray.x, 2) + pow(ray.y, 2) - pow(ray.z, 2) * tan(o->angle);
	q.y = 2 * (p.x * ray.x) + 2 * (p.y * ray.y) - 2 * ((p.z * ray.z)
		* tan(o->angle));
	q.z = pow(p.x, 2) + pow(p.y, 2) - (pow(p.z, 2) * tan(o->angle));
	delta = pow(q.y, 2) - 4 * q.x * q.z;
	if (delta < 0)
		return (-1);
	else if (delta == 0)
		d->t[0] = -q.y / (2 * q.x);
	else if (delta > 0)
	{
		d->t[0] = (-q.y - sqrt(delta)) / (2 * q.x);
		d->t[1] = (-q.y + sqrt(delta)) / (2 * q.x);
	}
	return (1);
}

int		light_plane(t_data *d, t_light *l, t_vec ray, t_obj *p)
{
	float	q;

	if (scalar(p->v, &ray) != 0)
	{
		q = -(p->v->x * p->px + p->v->y * p->py + p->v->z * p->pz);
		d->t[0] = (-(p->v->x * l->px) - p->v->y * l->py - p->v->z
		* l->pz - q) / (ray.x * p->v->x + ray.y * p->v->y + ray.z * p->v->z);
		if (d->t[0] < 0)
			return (-1);
		return (1);
	}
	return (-1);
}

int		in_or_out(t_data *d, t_obj *obj, float dist, t_vec vec)
{
	float	d1;
	float	d2;
	int		l1;
	int		l2;

	d1 = d->t[0] < d->t[1] ? d->t[0] : d->t[1];
	d2 = d->t[0] < d->t[1] ? d->t[1] : d->t[0];
	l1 = check_lim(obj, get_hitpoint(vec, d1, d));
	l2 = check_lim(obj, get_hitpoint(vec, d2, d));
	if ((d2 == dist && l2 == 1 && l1 != 1) || (d1 == dist && l1 == 1))
		return (-1);
	return (1);
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
		return (check_lim(s, get_hitpoint(r.lo, d->t[0], d)));
	}
	else if (delta > 0)
	{
		d->t[0] = (-b - sqrt(delta)) / (2 * a);
		d->t[1] = (-b + sqrt(delta)) / (2 * a);
		return (in_or_out(d, s, r.dist, r.lo));
	}
	return (1);
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
		ret = light_plane(d, l, s.lo, obj);
	if (ft_strcmp(obj->type, "cylinder") == 0)
		ret = light_cyli(d, l, s.lo, obj);
	if (ft_strcmp(obj->type, "cone") == 0)
		ret = light_cone(d, l, s.lo, obj);
	if (ret == 1)
		return (1);
	return (0);
}
