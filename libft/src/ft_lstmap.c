/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: axbal <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/14 17:03:13 by axbal             #+#    #+#             */
/*   Updated: 2017/11/14 17:15:43 by axbal            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list		*ft_lstmap(t_list *lst, t_list *(*f)(t_list *))
{
	t_list		*start;
	t_list		*prev;
	t_list		*tmp;

	if (lst)
	{
		prev = f(lst);
		start = prev;
	}
	while (lst)
	{
		lst = lst->next;
		if (lst)
			tmp = f(lst);
		if (tmp)
		{
			prev->next = tmp;
			prev = tmp;
		}
	}
	return (start);
}
