/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mterkhoy <mterkhoy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/22 17:56:13 by mterkhoy          #+#    #+#             */
/*   Updated: 2021/03/27 15:06:02 by mterkhoy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int		is_map_leaking(int x, int y, t_data *data)
{
	if (data->cfg.map[y][x] == ' ' ||
	(ft_strchr("02NSWE ", data->cfg.map[y][x]) && (y - 1 < 0 || x - 1 < 0 ||
		y + 1 >= data->cfg.map_size.y || x + 1 >= data->cfg.map_size.x)))
	{
		data->cfg.map[y][x] = '#';
		return (1);
	}
	if (ft_strchr("0NSWE", data->cfg.map[y][x]))
	{
		if (data->cfg.map[y][x] == '0')
			data->cfg.map[y][x] = '-';
		if (is_map_leaking(x, y - 1, data))
			return (1);
		if (is_map_leaking(x - 1, y, data))
			return (1);
		if (is_map_leaking(x, y + 1, data))
			return (1);
		if (is_map_leaking(x + 1, y, data))
			return (1);
	}
	return (0);
}

void	map_to_mat(t_data *data)
{
	size_t	i;
	t_list	*lst;

	lst = data->cfg.map_lst;
	if (!(data->cfg.map = malloc(data->cfg.map_size.y * sizeof(char *))))
		exit_failure(data, "Malloc failed");
	i = -1;
	while (++i < data->cfg.map_size.y)
	{
		if (!(data->cfg.map[i] = malloc(data->cfg.map_size.x * sizeof(char))))
			exit_failure(data, "Malloc failed");
		ft_memset(data->cfg.map[i], ' ', data->cfg.map_size.x);
		data->cfg.map[i] = ft_memcpy(data->cfg.map[i], lst->content,
			ft_strlen(lst->content));
		lst = lst->next;
	}
}

void	parse_player(t_data *data)
{
	int		i;
	int		j;

	i = -1;
	while (++i < data->cfg.map_size.y)
	{
		j = -1;
		while (++j < data->cfg.map_size.x)
			if (ft_strchr("NSWE", data->cfg.map[i][j]))
			{
				data->player.pos.x = j;
				data->player.pos.y = i;
				data->player.angle = get_angle(data->cfg.map[i][j]);
				while (i < data->cfg.map_size.y)
				{
					while (++j < data->cfg.map_size.x)
						if (ft_strchr("NSWE", data->cfg.map[i][j]))
							exit_failure(data, "Multiple players on map");
					j = -1;
					i++;
				}
				return ;
			}
	}
	exit_failure(data, "Player not found");
}

void	parse_map(char *line, t_data *data)
{
	size_t	i;
	size_t	len;
	char	*new_line;
	t_list	*portion;

	len = ft_strlen(line);
	i = -1;
	while (line[++i])
	{
		if (len > data->cfg.map_size.x)
			data->cfg.map_size.x = len;
		if (!ft_strchr(TILES, line[i]))
		{
			free(line);
			exit_failure(data, "Forbidden map tiles");
		}
	}
	if (!(portion = ft_lstnew(ft_strdup(line))))
		exit_failure(data, "Malloc failed");
	ft_lstadd_back(&data->cfg.map_lst, portion);
	data->cfg.map_size.y++;
}
