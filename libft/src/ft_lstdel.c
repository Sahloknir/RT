/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstdel.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: axbal <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/14 16:25:57 by axbal             #+#    #+#             */
/*   Updated: 2017/11/14 16:48:48 by axbal            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstdel(t_list **alst, void (*del)(void *, size_t))
{
	t_list		*ptr;

	while (*alst)
	{
		ptr = (*alst)->next;
		del((*alst)->content, (*alst)->content_size);
		free(*alst);
		*alst = ptr;
	}
}
