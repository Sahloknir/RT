/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_lim.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: axbal <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/07 15:43:31 by axbal             #+#    #+#             */
/*   Updated: 2019/01/10 15:39:00 by ceugene          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

int		get_object_lim_x(char *f, int s, t_obj *obj)
{
	float	*tab;

	tab = three_values_tab(f, s);
	if (!(f[(int)tab[4]]) || tab[3] != 2)
	{
		free(tab);
		return (0);
	}
	if (tab[0] < 1 && tab[1] > 0)
	{
		obj->lim_x_neg = tab[0];
		obj->lim_x_pos = tab[1];
		obj->lim_x_c = 1;
	}
	free(tab);
	return (1);
}

int		get_object_lim_y(char *f, int s, t_obj *obj)
{
	float	*tab;

	tab = three_values_tab(f, s);
	if (!(f[(int)tab[4]]) || tab[3] != 2)
	{
		free(tab);
		return (0);
	}
	if (tab[0] < 1 && tab[1] > 0)
	{
		obj->lim_y_neg = tab[0];
		obj->lim_y_pos = tab[1];
		obj->lim_y_c = 1;
	}
	free(tab);
	return (1);
}

int		get_object_lim_z(char *f, int s, t_obj *obj)
{
	float	*tab;

	tab = three_values_tab(f, s);
	if (!(f[(int)tab[4]]) || tab[3] != 2)
	{
		free(tab);
		return (0);
	}
	if (tab[0] < 1 && tab[1] > 0)
	{
		obj->lim_z_neg = tab[0];
		obj->lim_z_pos = tab[1];
		obj->lim_z_c = 1;
	}
	free(tab);
	return (1);
}
