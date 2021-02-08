/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mterkhoy <mterkhoy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/09 13:46:29 by mterkhoy          #+#    #+#             */
/*   Updated: 2020/11/02 14:39:03 by mterkhoy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list *nlist;

	(void)del;
	nlist = 0;
	while (lst)
	{
		ft_lstadd_back(&nlist, ft_lstnew(f(lst->content)));
		lst = lst->next;
	}
	return (nlist);
}
