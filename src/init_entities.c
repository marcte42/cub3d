/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_entities.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mterkhoy <mterkhoy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/27 14:02:10 by mterkhoy          #+#    #+#             */
/*   Updated: 2021/03/27 14:02:41 by mterkhoy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	init_entities(t_data *data)
{
	size_t		x;
	size_t		y;
	t_entity	*entity;

	y = -1;
	while (++y < data->cfg.map_size.y)
	{
		x = -1;
		while (++x < data->cfg.map_size.x)
		{
			if (ft_strchr(ENTITY, data->cfg.map[y][x]))
			{
				if (!(entity = malloc(sizeof(t_entity))))
					exit_failure(data, "Malloc failed");
				entity->angle = M_PI;
				entity->pos.x = (x * TILE_SIZE) + (TILE_SIZE / 2);
				entity->pos.y = (y * TILE_SIZE) + (TILE_SIZE / 2);
				entity->visible = 0;
				ft_lstadd_front(&data->entities, ft_lstnew(entity));
			}
		}
	}
}
