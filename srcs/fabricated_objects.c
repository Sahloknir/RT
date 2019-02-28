/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fabricated_objects.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: axbal <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/08 12:30:01 by axbal             #+#    #+#             */
/*   Updated: 2019/02/23 14:54:08 by axbal            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

int		get_object_size(char *f, int s, t_obj *obj)
{
	float	*tab;

	tab = three_values_tab(f, s);
	if (!(f[(int)tab[4]]) || tab[3] != 1 || tab[0] < 0)
	{
		free(tab);
		return (0);
	}
	obj->size = tab[0];
	obj->size_c += 1;
	free(tab);
	return (1);
}


void	fabricated_object(t_data *d, t_obj *obj)
{
	if (obj->type == CUBE)
		create_cube(d, obj);
}
