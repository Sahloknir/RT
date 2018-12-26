/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ceugene <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/12 12:19:58 by ceugene           #+#    #+#             */
/*   Updated: 2018/11/13 13:21:58 by axbal            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_stock_up(char **stock)
{
	char	*copy;

	if (*stock == NULL)
	{
		if (!(*stock = ft_strnew(BUFF_SIZE)))
			return (-1);
		return (1);
	}
	if (!(copy = ft_strdup(*stock)))
		return (-1);
	free(*stock);
	if (!(*stock = ft_strnew(ft_strlen(copy) + BUFF_SIZE)))
		return (-1);
	ft_strncpy(*stock, copy, ft_strlen(copy));
	free(copy);
	return (1);
}

int		ft_fill_line(char **line, char **stok, int select, int select2)
{
	free(*line);
	if (ft_memchr(*stok, '\n', ft_strlen(*stok)))
	{
		while ((*stok)[select] && ((*stok)[select] != '\n'))
			select++;
		if (!(*line = ft_strdup(*stok)))
			return (-1);
		(*line)[select] = '\0';
		while ((*stok)[select++])
		{
			(*stok)[select2] = (*stok)[select];
			select2++;
		}
		while (++select2 != select)
			(*stok)[select2] = '\0';
		return (1);
	}
	else if (!(*line = ft_strdup(*stok)))
		return (-1);
	ft_bzero(*stok, ft_strlen(*stok));
	return (1);
}

int		get_next_line(const int fd, char **line)
{
	static char		*stock;
	char			*lu;
	int				ret;

	if ((fd != 0 && fd < 3) || BUFF_SIZE < 1 || !&(*line)
		|| !(*line = ft_strnew(BUFF_SIZE)))
		return (-1);
	while ((lu = ft_strnew(BUFF_SIZE))
		&& (ret = read(fd, lu, BUFF_SIZE)) > 0)
	{
		lu[ret] = '\0';
		if (!(ft_stock_up(&stock)))
			return (-1);
		ft_strncat(stock, lu, ret);
		free(lu);
		if (ft_memchr(stock, '\n', ft_strlen(stock)))
			return (ft_fill_line(line, &stock, 0, 0));
	}
	if (ret < 0 || !(lu))
		return (-1);
	free(lu);
	if (stock && ft_strlen(stock) > 0)
		return (ft_fill_line(line, &stock, 0, 0));
	free(*line);
	return (0);
}
