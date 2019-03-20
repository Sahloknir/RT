/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: axbal <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/06 13:33:37 by axbal             #+#    #+#             */
/*   Updated: 2019/03/04 14:26:28 by axbal            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"
#include <math.h>

t_vec	rot_x(t_vec ray, float teta)
{
	float	y;
	float	z;

	y = cos(teta) * ray.y - sin(teta) * ray.z;
	z = sin(teta) * ray.y + cos(teta) * ray.z;
	ray.y = y;
	ray.z = z;
	return (ray);
}

t_vec	rot_y(t_vec ray, float teta)
{
	float	x;
	float	z;

	x = cos(teta) * ray.x + sin(teta) * ray.z;
	z = -sin(teta) * ray.x + cos(teta) * ray.z;
	ray.x = x;
	ray.z = z;
	return (ray);
}

t_vec	rot_z(t_vec ray, float teta)
{
	float	x;
	float	y;

	x = cos(teta) * ray.x - sin(teta) * ray.y;
	y = sin(teta) * ray.x + cos(teta) * ray.y;
	ray.x = x;
	ray.y = y;
	return (ray);
}

t_vec	rot_vec(t_vec ray, float rx, float ry, float rz)
{
	ray = rot_x(ray, degree_to_radian(rx));
	ray = rot_y(ray, degree_to_radian(ry));
	if (rz != 0)
		ray = rot_z(ray, degree_to_radian(rz));
	return (ray);
}

t_vec	unrot_vec(t_vec ray, float rx, float ry, float rz)
{
	if (rz != 0)
		ray = rot_z(ray, -degree_to_radian(rz));
	ray = rot_y(ray, -degree_to_radian(ry));
	ray = rot_x(ray, -degree_to_radian(rx));
	return (ray);
}

