/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: axbal <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/24 12:10:49 by axbal             #+#    #+#             */
/*   Updated: 2019/01/10 15:27:23 by ceugene          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"
#include <fcntl.h>

void		ft_fail(char *str, t_data *data)
{
	ft_putstr_fd(str, 2);
	ft_putchar('\n');
	if (data)
		exit(0);
	exit(0);
}

t_img		*init_img(t_data *data)
{
	t_img		*img;

	if (!(img = (t_img *)malloc(sizeof(t_img) * 1)))
		ft_fail("Error: Could not allocate memory", NULL);
	img->width = LA;
	img->height = HA;
	if (!(img->ptr = mlx_new_image(data->mlx_ptr, LA, HA)))
		ft_fail("Error: cant create image.", NULL);
	if (!(img->str = mlx_get_data_addr(img->ptr, &img->bpp,
		&img->s_l, &img->endian)))
		ft_fail("Error: cant create image.", NULL);
	img->bpp /= 8;
	return (img);
}

void		let_mlx_loop(t_data *data)
{
	mlx_hook(data->win_ptr, 17, 1L << 17, &close_program, data);
	mlx_hook(data->win_ptr, 3, 1L << 1, &key_release, data);
	mlx_loop_hook(data->mlx_ptr, &refresh_expose, data);
	mlx_put_image_to_window(data->mlx_ptr, data->win_ptr, data->img->ptr, 0, 0);
	mlx_loop(data->mlx_ptr);
}

int			main(int argc, char **argv)
{
	t_data	*data;
	char	*file;

	file = NULL;
	if (argc < 2)
		ft_fail("Usage: rtv1 input_file", NULL);
	data = new_data();
	file = start_reading(argv[1]);
	read_file(data, file);
	if (data->objects != 0 && data->cam != NULL)
		start_raytracing(data);
	if (data->objects < 1 && data->cam != NULL)
		ft_putstr_fd("No object to draw! Enjoy the black screen.\n", 2);
	if (data->cam == NULL)
		ft_fail("Error: No valid camera. Cannot draw the scene.", data);
	else
		let_mlx_loop(data);
	return (0);
}
