#include "rtv1.h"
#include <fcntl.h>

int		screenshot(t_data *d)
{
	int		fd;
	char	*name;
	char	*tmp;

	tmp = ft_strjoin("./screenshots/", d->file_name);
	name = ft_strjoin(tmp, ".bmp");
	free(tmp);
	if ((fd = open(name, O_WRONLY | O_CREAT, O_EXCL)) == -1)
	{
		ft_putstr("Screenshot ");
		ft_putstr(name);
		ft_putstr(" already exists or cannot be created.\n");
		free(name);
		return (-1);
	}
	ft_putstr("OK\n");
	free(name);
	if (close(fd) == -1)
		ft_fail("Error occurred while closing file descriptor.\n", d);
	return (1);
}
