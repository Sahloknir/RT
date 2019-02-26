/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reading.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: axbal <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/23 16:09:59 by axbal             #+#    #+#             */
/*   Updated: 2019/01/10 13:51:28 by ceugene          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

char	*word_return(char *str, int select)
{
	char	*word;
	int		select2;

	select2 = select;
	while (str[select2] && ft_isalpha(str[select2]))
		select2++;
	if (!(str[select2]))
		return (NULL);
	if (!(word = ft_strnew(select2 - select + 1)))
		ft_fail("Error: Cant allocate memory.", NULL);
	select2 = 0;
	while (str[select] && ft_isalpha(str[select]))
	{
		word[select2] = str[select];
		select++;
		select2++;
	}
	word[select2] = '\0';
	return (word);
}

float	*three_values_tab(char *f, int s)
{
	float	*tab;
	int		levier;
	float	result;

	levier = 0;
	if (!(tab = (float *)malloc(sizeof(float) * 5)))
		ft_fail("Error: Could not allocate memory.", NULL);
	while (f[s] && f[s] != ')')
	{
		if ((ft_isdigit(f[s]) && ((f[s - 1] == ','
			|| f[s - 1] == ' ' || f[s - 1] == '(') || f[s - 1] == '+'))
				|| (f[s] == '-' && f[s + 1] && ft_isdigit(f[s + 1])))
		{
			result = ft_atof(f + s);
			if (levier < 3)
				tab[levier] = result;
			levier++;
		}
		s++;
	}
	tab[3] = levier;
	tab[4] = s;
	return (tab);
}

int		read_new_object(t_data *data, char *ob, char *file, int select)
{
	if (!(file[select]) || !(file[select + 1]))
		return (0);
	if (ft_strcmp(ob, "object") == 0)
		return (read_object(data, file, select));
	else if (ft_strcmp(ob, "light") == 0)
		return (read_light(data, file, select));
	else if (ft_strcmp(ob, "camera") == 0)
		return (read_camera(data, file, select));
	return (0);
}

int		read_file(t_data *data, char *file)
{
	int		select;
	char	*object;

	if (!data)
		return (-1);
	select = 0;
	while (file[select])
	{
		object = NULL;
		if (ft_isalpha(file[select]))
			object = word_return(file, select);
		if (object != NULL)
		{
			select += ft_strlen(object);
			read_new_object(data, object, file, select);
			free(object);
			while (file[select] && file[select] != '}')
				select++;
		}
		select++;
	}
	free(file);
	return (1);
}
