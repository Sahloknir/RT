/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   put_pixel.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: axbal <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/10 19:11:29 by axbal             #+#    #+#             */
/*   Updated: 2019/01/06 13:57:38 by axbal            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

void	put_pixel_to_image(t_dot d, t_data *dt, char *i, t_color c)
{
	int		px;

	px = ((int)d.x * dt->img->bpp) + ((int)d.y * dt->img->s_l);
	if (d.x >= 0 && d.x <= LA && d.y >= 0 && d.y < HA)
	{
		i[px + 0] = (char)ft_clamp(c.b, 0, 255);
		i[px + 1] = (char)ft_clamp(c.g, 0, 255);
		i[px + 2] = (char)ft_clamp(c.r, 0, 255);
		i[px + 3] = (char)0;
	}
}

t_dot	dot_from_light(t_light *l, t_vec vec, float dist)
{
	t_dot	dot;

	dot.x = l->px + (float)(vec.x * dist);
	dot.y = l->py + (float)(vec.y * dist);
	dot.z = l->pz + (float)(vec.z * dist);
	return (dot);
}
