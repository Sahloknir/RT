#include "rtv1.h"

int		check_file(t_data *d, char *file)
{
	// img_to_expose = img2
	file = start_reading(file);
	read_file(d, file);
	if (d->objects != 0 && d->cam != NULL)
		start_raytracing(d);
	else if (d->objects == 0)
	{
		ft_putstr_fd("No object to draw! Enjoy the black screen!\n", 2);
		return (-1);
	}
	else if (d->cam == NULL)
	{
		ft_fail("Error: No valid camera. Cannot draw the scene.\n", d);
		return (-1);
	}
	// nettoyer la fenetre et afficher img au lieu d'img 2
	// img_to_expose = img;
	// vider img2
	return (1);
}
