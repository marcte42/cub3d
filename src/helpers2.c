/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helpers2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mterkhoy <mterkhoy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/10 12:40:47 by mterkhoy          #+#    #+#             */
/*   Updated: 2021/04/10 16:52:12 by marcte           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int		params_count(char **params)
{
	size_t i;

	i = 0;
	if (!params)
		return (0);
	while (params[i])
		i++;
	return (i);
}

int		ft_issuffix(char *s1, char *s2)
{
	size_t	s1_len;
	size_t	s2_len;

	s1_len = ft_strlen(s1);
	s2_len = ft_strlen(s2);
	return (!ft_strcmp(s1 + (s1_len - s2_len), s2));
}

t_crd	ft_lstpop(t_list **lst)
{
	t_list	*tmp;
	t_crd	p;
	t_crd	*pp;

	tmp = *lst;
	pp = (*lst)->content;
	p.x = pp->x;
	p.y = pp->y;
	*lst = tmp->next;
	free(tmp->content);
	free(tmp);
	return (p);
}

t_crd	*point_create(t_data *data, int x, int y)
{
	t_crd	*p;

	if (!(p = malloc(sizeof(t_crd))))
		exit_failure(data, "Malloc failed");
	p->x = x;
	p->y = y;
	return (p);
}
