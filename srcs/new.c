/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   new.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: axbal <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/13 13:04:35 by axbal             #+#    #+#             */
/*   Updated: 2019/03/16 15:10:59 by axbal            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

t_dot		new_dot(float x, float y, float z)
{
	t_dot	d;

	d.x = x;
	d.y = y;
	d.z = z;
	return (d);
}

t_vec		new_vec(float x, float y, float z)
{
	t_vec	v;

	v.x = x;
	v.y = y;
	v.z = z;
	return (v);
}

t_color		new_color(int r, int g, int b, int a)
{
	t_color		new;

	new.r = ft_clamp(r, 0, 255);
	new.g = ft_clamp(g, 0, 255);
	new.b = ft_clamp(b, 0, 255);
	new.a = ft_clamp(a, 0, 1);
	return (new);
}

t_data		*new_data(void)
{
	t_data	*new;

	if (!(new = (t_data *)malloc(sizeof(t_data) * 1)))
		ft_fail("Error: Could not allocate memory", NULL);
	if (!(new->mlx_ptr = mlx_init()))
		ft_fail("Error: Connection failed.", NULL);
	if (!(new->win_ptr = mlx_new_window(new->mlx_ptr, LA, HA, "rt")))
		ft_fail("Error: Unable to create window.", NULL);
	init_data(new);
	return (new);
}
