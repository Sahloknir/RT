/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   write_options.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: axbal <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/21 14:30:39 by axbal             #+#    #+#             */
/*   Updated: 2019/03/21 14:30:41 by axbal            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void	ft_string(t_data *d, char *str, int color, int nb)
{
	int		x;
	int		y;

	if (ft_strcmp(str, "OFF") == 0 || ft_strcmp(str, "ON") == 0
		|| ft_strcmp("sinus", str) == 0 || !ft_strcmp("squared", str)
			|| !ft_strcmp("none", str) || !ft_strcmp("strong", str)
				|| !ft_strcmp("mild", str))
			x = LA / 1.7 - (ft_strlen(str) * 2.5);
	else
		x = LA / 6 - (ft_strlen(str) * 2.5);
	y = (HA / 3.5) + ((HA / 15) * nb);
	if (nb == 0)
		y = HA / 7;
	if (nb > 6)
	{
		x = nb == 7 ? LA / 8 : LA / 2.1;
		x = nb > 8 ? LA - LA / 5 : x;
		x -= ft_strlen(str) * 2.5;
		y = nb == 8 ? HA / 1.6 : HA / 1.8;
		if (!ft_strcmp(str, "options"))
			y = HA / 1.3;
	}
	mlx_string_put(d->mlx_ptr, d->win_ptr, x,
	y, color, str);
}

int		write_options4(t_data *d, char *off, char *on, char *str)
{
	free(str);
	if (d->img->d5 > 0)
	{
		str = d->img->d5 < 20 ? ft_strdup("strong") : ft_strdup("mild");
		ft_string(d, str, 0xDDFFDDDD, 6);
	}
	else
	{
		str = ft_strdup("none");
		ft_string(d, str, 0xCCCCCCCC, 6);
	}
	free(on);
	free(off);
	free(str);
	return (1);
}

int		write_options3(t_data *d, char *off, char *on, char *str)
{
	if (d->selected_option == 4)
		ft_string(d, str, 0xAAFFFAA, 4);
	else
		ft_string(d, str, 0xCCCCCCCC, 4);
	if (d->img->crtn == 0)
		ft_string(d, off, 0xFFDDDDDD, 4);
	else
		ft_string(d, on, 0xDDFFDDDD, 4);
	free(str);
	str = ft_strdup("minecraft texture");
	if (d->selected_option == 5)
		ft_string(d, str, 0xAAFFFAA, 5);
	else
		ft_string(d, str, 0xCCCCCCCC, 5);
	if (d->img->d4 == 0)
		ft_string(d, off, 0xFFDDDDDD, 5);
	else
		ft_string(d, on, 0xDDFFDDDD, 5);
	free(str);
	str = ft_strdup("perlin noise");
	if (d->selected_option == 6)
		ft_string(d, str, 0xAAFFFAA, 6);
	else
		ft_string(d, str, 0xCCCCCCCC, 6);
	return (write_options4(d, off, on, str));
}

int		write_options2(t_data *d, char *off, char *on, char *str)
{
	if (d->img->gs == 0)
		ft_string(d, off, 0xCCCCCCC, 2);
	else
		ft_string(d, on, 0xDDFFDDDD, 2);
	free(str);
	str = ft_strdup("disturbance");
	if (d->selected_option == 3)
		ft_string(d, str, 0xAAFFFAA, 3);
	else
		ft_string(d, str, 0xCCCCCCCC, 3);
	free(str);
	if (d->img->d > 0)
	{
		str = d->img->d < 2 ? ft_strdup("sinus") : ft_strdup("squared");
		ft_string(d, str, 0xAAFFFAA, 3);
	}
	else
	{
		str = ft_strdup("none");
		ft_string(d, str, 0xCCCCCCCC, 3);
	}
	free(str);
	str = ft_strdup("cartoon");
	return (write_options3(d, off, on, str));
}


int		write_options(t_data *d)
{
	char	*on;
	char	*off;
	char	*str;

	on = ft_strdup("ON");
	off = ft_strdup("OFF");
	str = ft_strdup("<- Q TO SAVE AND RETURN");
	ft_string(d, str, 0xCCCCCCCC, 0);
	free(str);
	str = ft_strdup("sepia");
	if (d->selected_option == 1)
		ft_string(d, str, 0xAAFFFAA, 1);
	else
		ft_string(d, str, 0xCCCCCCCC, 1);
	if (d->img->sp == 0)
		ft_string(d, off, 0xFFDDDDDD, 1);
	else
		ft_string(d, on, 0xDDFFDDDD, 1);
	free(str);
	str = ft_strdup("grayscale");
	if (d->selected_option == 2)
		ft_string(d, str, 0xAAFFFAA, 2);
	else
		ft_string(d, str, 0xCCCCCCCC, 2);
	return (write_options2(d, off, on, str));
}
