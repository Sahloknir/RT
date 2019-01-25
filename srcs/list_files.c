#include "rtv1.h"
#include <dirent.h>

int		list_all_scene_files(t_data *d, DIR *di)
{
	struct dirent	*dir;
	char			str[4];
	int				lenght;

	str[3] = '\0';
	while ((dir = readdir(di)) != NULL)
	{
		if (dir->d_type != DT_DIR && (lenght = ft_strlen(dir->d_name)) > 3)
		{
			str[0] = dir->d_name[lenght - 3];
			str[1] = dir->d_name[lenght - 2];
			str[2] = dir->d_name[lenght - 1];
			if (ft_strequ(str, ".sc"))
			{
				d->dir_files++;
				ft_putstr(dir->d_name);
				ft_putstr("\n");
			}
		}
	}
	return (d->dir_files);
}

int		open_scenes_dir(t_data *d)
{
	DIR				*di;

	d->dir_files = 0;
	if ((di = opendir(SCENES_PATH)) == NULL)
		ft_fail("Error: Path to scenes directory is invalid.", d);
	else if (list_all_scene_files(d, di) == 0)
		ft_fail("Error: There are no scene files in the path mentionned.", d);
	closedir(di);
	return (1);
}
