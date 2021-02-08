/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mterkhoy <mterkhoy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/07 19:40:06 by mterkhoy          #+#    #+#             */
/*   Updated: 2021/01/24 17:39:09 by mterkhoy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int		ft_issep(char c, char *sep)
{
	size_t i;

	i = -1;
	while (sep[++i])
		if (sep[i] == c)
			return (1);
	return (0);
}

static size_t	ft_word_count(char const *s, char *sep)
{
	size_t	i;
	size_t	wc;

	wc = 0;
	i = -1;
	while (s[++i])
		if (!ft_issep(s[i], sep) && (ft_issep(s[i + 1], sep) || !s[i + 1]))
			wc++;
	return (wc);
}

static char		*ft_strduptosep(const char *s1, char *sep, size_t *index)
{
	char	*dst;
	size_t	i;
	size_t	len;

	len = 0;
	while (s1[len] && !ft_issep(s1[len], sep))
		len++;
	if (!(dst = (char *)malloc((len + 1) * sizeof(char))))
		return (NULL);
	i = -1;
	while (++i < len)
		dst[i] = s1[i];
	dst[i] = '\0';
	(*index) += len - 1;
	return (dst);
}

char			**ft_split(char const *s, char *sep)
{
	char	**tab;
	size_t	wc;
	size_t	i;
	size_t	j;

	if (!s)
		return (NULL);
	wc = ft_word_count(s, sep);
	if (!(tab = (char **)malloc((wc + 1) * sizeof(char *))))
		return (NULL);
	j = 0;
	i = -1;
	while (s[++i])
		if ((i == 0 && !ft_issep(s[i], sep)) ||
			(i != 0 && !ft_issep(s[i], sep) && ft_issep(s[i - 1], sep)))
			tab[j++] = ft_strduptosep(&s[i], sep, &i);
	tab[j] = 0;
	return (tab);
}
