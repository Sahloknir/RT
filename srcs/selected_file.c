#include "rtv1.h"

int		open_selected_choice(t_data *d)
{
	char	*str;

	if (d)
		free_data(d);
	d->file_name = ft_strdup(d->files[d->selected_choice]);
	if (!(str = malloc(sizeof(char) * ft_strlen(d->files[d->selected_choice]
		+ ft_strlen(SCENES_PATH)))))
		ft_fail("Error: Could not allocate memory.", d);
	ft_strcpy(str, SCENES_PATH);
	ft_strcat(str, d->files[d->selected_choice]);
	check_file(d, str);
	free(str);
	return (0);
}

int		check_file(t_data *d, char *file)
{
	file = start_reading(file);
	read_file(d, file);
	d->current_img = 2;
	refresh_expose(d);
	if (d->objects != 0 && d->cam != NULL)
		start_raytracing(d);
	else if (d->objects == 0)
		ft_putstr_fd("No object to draw! Enjoy the black screen!\n", 2);
	else if (d->cam == NULL)
	{
		ft_return("Error: No valid camera. Cannot draw the scene.", d);
		return (-1);
	}
	d->current_img = 1;
	refresh_expose(d);
	return (1);
}
