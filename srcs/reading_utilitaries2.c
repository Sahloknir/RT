/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reading_utilitaries2.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: axbal <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/05 16:03:36 by axbal             #+#    #+#             */
/*   Updated: 2019/02/05 16:10:39 by axbal            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

int		get_object_mirror(char *f, int s, t_obj *obj)
{
	float	*tab;

	tab = three_values_tab(f, s);
	if (tab[3] != 1)
	{
		free(tab);
		return (0);
	}
	obj->mirror = ft_clamp((int)tab[0], 0, 100);
	free(tab);
	return (0);
}
