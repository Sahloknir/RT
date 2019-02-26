#include "rt.h"
#include <fcntl.h>

char	*get_file_name(char *str)
{
	int		s;
	int		max_len;
	int		min_len;

	s = 0;
	while (str[s] != '.' && str[s] != '\0')
		s++;
	if (str[s] == '\0')
		return (NULL);
	max_len = s;
	while (str[s] != '\0' && str[s] != '/')
		s--;
	min_len = s;
	return(ft_strsub(str, s + 1, max_len - min_len - 1));
}

char	*get_img(char *img_str, t_data *d, t_hdr h)
{
	int		i;
	int		j;
	int		k;
	char	*str;

	i = h.i_size - 1;
	j = 0;
	if (!(str = (char *)malloc(sizeof(char) * LA * d->img->s_l)))
		ft_fail("Error: Could not malloc enough memory.\n", d);
	while (i >= 0)
	{
		i -= d->img->s_l;
		k = 0;
		while (k < d->img->s_l)
		{
			str[j] = img_str[i + k + 1];
			str[j + 1] = img_str[i + k + 2];
			str[j + 2] = img_str[i + k + 3];
			j += 3;
			k += 4;
		}
	}
	return (str);
}

void	write_to_file(int fd, t_hdr h, t_data *d)
{
	char	*image_string;

	write(fd, &h.type, 2);
	write(fd, &h.file_size, 4);
	write(fd, &h.rsrvd, 4);
	write(fd, &h.offset, 4);
	write(fd, &h.size, 4);
	write(fd, &h.la, 4);
	write(fd, &h.ha, 4);
	write(fd, &h.plane_nb, 2);
	write(fd, &h.bpp, 2);
	write(fd, &h.compression, 4);
	write(fd, &h.i_size, 4);
	write(fd, &h.h_res, 4);
	write(fd, &h.v_res, 4);
	write(fd, &h.color_nb, 4);
	write(fd, &h.imp_color_nb, 4);
	image_string = get_img(d->img->str, d, h);
	write(fd, image_string, h.i_size);
	free(image_string);
}

void	fill_header_info(int fd, t_data *d)
{
	t_hdr	h;

	h.type[0] = 0x42;
	h.type[1] = 0x4D;
	h.offset = 54;
	h.i_size = d->img->s_l * HA;
	h.file_size = h.offset + h.i_size;
	h.rsrvd = 0;
	h.size = 40;
	h.plane_nb = 1;
	h.bpp = 24;
	h.compression = 0;
	h.h_res = 2835;
	h.v_res = 2835;
	h.color_nb = 0;
	h.imp_color_nb = 0;
	h.la = LA;
	h.ha = HA;
	write_to_file(fd, h, d);
}

int		screenshot(t_data *d)
{
	int		fd;
	char	*name;
	char	*tmp;
	char	*trois;

	ft_putstr("SCREENSHOT -\n");
	trois = get_file_name(d->file_name);
	tmp = ft_strjoin("./screenshots/", trois);
	free(trois);
	name = ft_strjoin(tmp, ".bmp");
	free(tmp);
	if ((fd = open(name, O_WRONLY | O_CREAT | O_EXCL, 0640)) < 0)
	{
		ft_putstr("Screenshot ");
		ft_putstr(name);
		ft_putstr(" already exists or cannot be created.\n");
		free(name);
		ft_putstr("SCREENSHOT OK\n");
		return (-1);
	}
	free(name);
	fill_header_info(fd, d);
	if (close(fd) == -1)
		ft_fail("Error occurred while closing file descriptor.\n", d);
	ft_putstr("SCREENSHOT OK\n");
	return (1);
}
