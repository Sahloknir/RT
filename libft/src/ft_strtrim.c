/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: axbal <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/12 16:10:43 by axbal             #+#    #+#             */
/*   Updated: 2017/11/16 16:19:37 by axbal            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strtrim(const char *s)
{
	int		i;
	int		space;
	int		start;
	char	*new;

	i = 0;
	space = 0;
	if (s == NULL)
		return (NULL);
	while (s[i] == ' ' || s[i] == '\t' || s[i] == '\n')
		i++;
	if (s[i] == '\0')
		return (ft_strdup(""));
	start = i;
	i = ft_strlen(s) - 1;
	while (i > 0 && (s[i] == ' ' || s[i] == '\t' || s[i] == '\n'))
	{
		i--;
		space++;
	}
	if (!(new = ft_strsub(s, start, ft_strlen(s) - start - space)))
		return (0);
	return (new);
}
