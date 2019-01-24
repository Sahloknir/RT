#include "rtv1.h"
#include <dirent.h>

int		open_scenes_dir(t_data *d)
{
	DIR				*di;
	struct dirent	*dir;

	if ((di = opendir(SCENES_PATH)) == NULL)
//		return (-1);
		ft_fail("Error: Path to scenes directory is invalid.", d);
	while ((dir = readdir(di)) != NULL)
	{
		if (dir->d_type != DT_DIR)
		{
			ft_putstr(dir->d_name);
			ft_putstr("\n");
		}
	}
	closedir(di);
	return (1);
}
