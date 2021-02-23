/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   entities.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mterkhoy <mterkhoy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/19 19:00:08 by mterkhoy          #+#    #+#             */
/*   Updated: 2021/02/23 10:40:16 by mterkhoy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	update_entities(t_data *data)
{
	return ;
}

size_t	count_entities(t_data *data)
{
	size_t x;
	size_t y;
	size_t count;

	count = 0;
	y = -1;
	while (++y < data->cfg.map_size.y)
	{
		x = -1;
		while (++x < data->cfg.map_size.x)
		{
			if (ft_strchr(SPRITE, data->cfg.map[y][x]))
				count++;
		}
	}
	return (count);
}

void	init_entities(t_data *data)
{
	size_t	entities_count;
	size_t	x;
	size_t	y;
	size_t	i;

	entities_count = count_entities(data);
	if (!(data->entities = malloc(entities_count * sizeof(t_entity))))
		exit_failure(data, "Malloc failed");
	i = 0;
	y = -1;
	while (++y < data->cfg.map_size.y)
	{
		x = -1;
		while (++x < data->cfg.map_size.x)
		{
			if (ft_strchr(SPRITE, data->cfg.map[y][x]))
			{
				data->entities[i].pos.x = (x * TILE_SIZE) + (TILE_SIZE / 2);
				data->entities[i].pos.y = (y * TILE_SIZE) + (TILE_SIZE / 2);
				data->entities[i].angle = M_PI;
				i++;
			}
		}
	}
	data->entities_count = entities_count;
}
