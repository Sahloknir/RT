/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   negobj.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: axbal <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/06 15:07:17 by axbal             #+#    #+#             */
/*   Updated: 2019/03/14 14:25:23 by axbal            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"
#include <stdio.h>

int		check_neg2(int i, t_vec ray, t_data *d, float l)
{
	float	t1;
	float	t2;
	float	l1;
	float	l2;

	t1 = d->t[0];
	t2 = d->t[1];
	if (test_object(d, ray, d->neg[i], d->cam->pos) > 0)
	{
		if (d->t[1] != -1)
		{
			l1 = d->t[0] < d->t[1] ? d->t[0] : d->t[1];
			l2 = d->t[0] < d->t[1] ? d->t[1] : d->t[0];
			if (l < l2 && l > l1)
			{
				d->t[0] = t1;
				d->t[1] = t2;
				return (-1);
			}
		}
	}
	return (1);
}

int		check_neg(t_dot dot, t_vec ray, t_data *d)
{
	int		i;
	float	l;
	float	t1;
	float	t2;

	t1 = d->t[0];
	t2 = d->t[1];
	i = -1;
	l = find_right_distance(d, d->cam->pos, ray, dot);
	while (++i < d->negs)
	{
		if (check_neg2(i, ray, d, l) == -1)
			return (-1);
	}
	d->t[0] = t1;
	d->t[1] = t2;
	return (1);
}
