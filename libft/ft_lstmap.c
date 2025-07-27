/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamerlin <mamerlin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/20 18:28:33 by mamerlin          #+#    #+#             */
/*   Updated: 2024/01/20 20:20:23 by mamerlin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void*), void (*del)(void*))
{
	t_list	*node;
	t_list	*pol;

	if (lst)
	{
		pol = ft_lstnew(f(lst->content));
		if (!pol)
			return (NULL);
		lst = lst->next;
		while (lst)
		{
			node = ft_lstnew(f(lst->content));
			if (!node)
			{
				ft_lstclear(&pol, del);
				return (NULL);
			}
			ft_lstadd_back(&pol, node);
			lst = lst->next;
		}
		return (pol);
	}
	return (NULL);
}
