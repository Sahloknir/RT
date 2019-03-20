/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reading_utilitaries.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: axbal <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/23 16:10:34 by axbal             #+#    #+#             */
/*   Updated: 2019/03/16 15:24:03 by axbal            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"
#include <fcntl.h>

float		ft_atof(const char *str)
{
	int		s;
	int		virgule;
	float	result;
	int		levier;

	s = 0;
	result = 0;
	levier = 1;
	virgule = 0;
	while (str[s] == '\f' || str[s] == '\n' || str[s] == ' '
		|| str[s] == '\t' || str[s] == '\r' || str[s] == '\v')
		s++;
	if (str[s] == '-')
		levier = -1;
	if (str[s] == '-' || str[s] == '+')
		s++;
	while (str[s] >= '0' && str[s] <= '9')
	{
		result = result * 10 + (str[s++] - '0');
		if (str[s] == '.')
			virgule = s++;
	}
	while (virgule != 0 && ft_isdigit(str[++virgule]))
		levier = levier * 10;
	return (result / levier);
}

int			ft_increase_file(char **file, char *line)
{
	char	*copy;

	if (*file == NULL)
	{
		if (!(*file = ft_strdup(line)))
			return (-1);
		free(line);
		return (1);
	}
	if (!(copy = ft_strdup(*file)))
		return (-1);
	free(*file);
	if (!(*file = ft_strnew(ft_strlen(copy) + ft_strlen(line))))
		return (-1);
	ft_strcpy(*file, copy);
	free(copy);
	ft_strcat(*file, line);
	free(line);
	return (1);
}

char		*start_reading(char *str)
{
	int		fd;
	int		ret;
	char	*file;
	char	*line;

	file = NULL;
	fd = open(str, O_RDONLY);
	if (fd < 0)
	{
		ft_putstr_fd("Error: No file '", 2);
		ft_putstr_fd(str, 2);
		ft_fail("' found.", NULL);
	}
	while ((ret = get_next_line(fd, &line)) > 0)
	{
		if (ft_increase_file(&file, line) == -1)
			ft_fail("Error: An error occurred.", NULL);
	}
	close(fd);
	if (ret <= -1 || (file && ft_strlen(file) >= (163840)))
		ft_fail("Error: File is too big or is a directory.", NULL);
	if (!file || ft_strlen(file) == 0)
		ft_fail("Error: File is empty.", NULL);
	return (file);
}
