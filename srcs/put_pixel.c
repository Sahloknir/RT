/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   put_pixel.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: axbal <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/10 19:11:29 by axbal             #+#    #+#             */
/*   Updated: 2019/01/10 15:39:38 by ceugene          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

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

t_color	apply_color(t_color c, t_obj *o, t_data *d, float angle)
{
	c.r += ft_clamp(((o->color.r / d->lights) * angle), 0, o->color.r);
	c.g += ft_clamp(((o->color.g / d->lights) * angle), 0, o->color.g);
	c.b += ft_clamp(((o->color.b / d->lights) * angle), 0, o->color.b);
	return (c);
}
