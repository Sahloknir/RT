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

#include "rt.h"
#include <fcntl.h>

void		ft_return(char *str, t_data *d)
{
	if (d)
		free_data(d);
	if (str)
	{
		ft_putstr_fd(str, 2);
		ft_putchar('\n');
	}
	d->current_img = 0;
	refresh_expose(d);
}

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
	img->d4 = 0;
	img->d5 = 20;
	return (img);
}

void		let_mlx_loop(t_data *data)
{
	mlx_hook(data->win_ptr, 17, 1L << 17, &close_program, data);
	mlx_hook(data->win_ptr, 3, 1L << 1, &key_release, data);
	mlx_expose_hook(data->win_ptr, &refresh_expose, data);
	mlx_loop(data->mlx_ptr);
}

int			main(int argc, char **argv)
{
	t_data	*data;
	char	*file;

	file = NULL;
	data = new_data();
	if (argc > 2)
		ft_fail("Usage: rtv1 [input_file]", data);
	open_scenes_dir(data);
	set_up_menu(data);
	if (argc == 2)
	{
		loading_screen_bar(data);
		data->file_name = ft_strdup(argv[1]);
		check_file(data, argv[1]);
	}
	else if (argc < 2)
		data->current_img = 0;
	refresh_expose(data);
	let_mlx_loop(data);
	return (0);
}
