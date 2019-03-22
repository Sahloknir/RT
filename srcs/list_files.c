/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_files.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: axbal <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/21 14:27:36 by axbal             #+#    #+#             */
/*   Updated: 2019/03/22 14:16:17 by ceugene          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"
#include <dirent.h>

int		add_to_files(t_data *d, char *name)
{
	char	**tmp;
	int		i;

	i = -1;
	if (d->dir_files <= 1)
	{
		if (!(d->files = (char **)(malloc(sizeof(char **) * 1))))
			ft_fail("Error: Could not malloc memory for files tab.", d);
		d->files[d->dir_files - 1] = ft_strdup(name);
		return (1);
	}
	if (!(tmp = (char **)(malloc(sizeof(char *) * d->dir_files - 1))))
		ft_fail("Error: Could not malloc memory for files tab.", d);
	while (++i < d->dir_files - 1)
	{
		tmp[i] = ft_strdup(d->files[i]);
		free(d->files[i]);
	}
	free(d->files);
	tmp[d->dir_files - 1] = ft_strdup(name);
	d->files = tmp;
	return (1);
}

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
				add_to_files(d, dir->d_name);
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
		ft_fail("Error: There are no scene files in the mentionned path.", d);
	closedir(di);
	return (1);
}
