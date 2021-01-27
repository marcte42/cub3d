/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mterkhoy <mterkhoy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/19 23:01:54 by marc              #+#    #+#             */
/*   Updated: 2021/01/26 13:24:38 by mterkhoy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s1)
{
	char	*dst;
	size_t	len;

	if (!s1)
	{
		if (!(dst = (char *)malloc(sizeof(char))))
			return (0);
		dst[0] = '\0';
	}
	else
	{
		len = ft_strlen(s1);
		if (!(dst = (char *)malloc((len + 1) * sizeof(char))))
			return (NULL);
		ft_strcpy(dst, s1);
	}
	return (dst);
}
