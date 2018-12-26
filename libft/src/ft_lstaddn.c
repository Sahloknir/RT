/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstaddn.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: axbal <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/17 13:59:08 by axbal             #+#    #+#             */
/*   Updated: 2017/11/17 14:48:20 by axbal            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstaddn(t_list **alst, t_list *new, size_t n)
{
	size_t		i;
	t_list		*tmp;

	tmp = *alst;
	i = 0;
	while (i < n - 2 && tmp->next)
	{
		tmp = tmp->next;
		i++;
	}
	if (tmp->next == NULL && i != n - 2)
	{
		new->next = NULL;
		tmp->next = new;
	}
	else if (n < 2)
		ft_lstadd(alst, new);
	else
	{
		new->next = tmp->next;
		tmp->next = new;
	}
}
