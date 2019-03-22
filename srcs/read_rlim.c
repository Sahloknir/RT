/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_rlim.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ceugene <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/22 14:27:31 by ceugene           #+#    #+#             */
/*   Updated: 2019/03/22 14:28:36 by ceugene          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

int		get_object_rlim_x(char *f, int s, t_obj *obj)
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
		obj->rlim_x_neg = tab[0];
		obj->rlim_x_pos = tab[1];
		obj->rlim_x_c = 1;
	}
	free(tab);
	return (1);
}

int		get_object_rlim_y(char *f, int s, t_obj *obj)
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
		obj->rlim_y_neg = tab[0];
		obj->rlim_y_pos = tab[1];
		obj->rlim_y_c = 1;
	}
	free(tab);
	return (1);
}

int		get_object_rlim_z(char *f, int s, t_obj *obj)
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
		obj->rlim_z_neg = tab[0];
		obj->rlim_z_pos = tab[1];
		obj->rlim_z_c = 1;
	}
	free(tab);
	return (1);
}
