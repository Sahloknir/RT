/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstprint.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: axbal <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/17 14:20:06 by axbal             #+#    #+#             */
/*   Updated: 2017/11/17 14:32:06 by axbal            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstprint(t_list **alst)
{
	t_list	*elem;

	elem = *alst;
	while (elem)
	{
		write(1, elem->content, elem->content_size);
		write(1, "\n", 1);
		elem = elem->next;
	}
}
