/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update_entities.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mterkhoy <mterkhoy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/27 14:03:37 by mterkhoy          #+#    #+#             */
/*   Updated: 2021/03/27 14:04:24 by mterkhoy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	entity_visible(t_data *data, t_entity *entity)
{
	float angle;

	angle = data->player.angle - atan2(data->player.pos.y -
				entity->pos.y, entity->pos.x - data->player.pos.x);
	angle -= (angle > M_PI) ? M_PI * 2 : 0;
	angle += (angle < -M_PI) ? M_PI * 2 : 0;
	angle = fabs(angle);
	if (angle < (FOV / 2) + 0.2)
	{
		entity->visible = 1;
		entity->angle = angle;
		entity->distance = hit_distance(entity->pos.x, entity->pos.y,
					data->player.pos.x, data->player.pos.y);
	}
	else
		entity->visible = 0;
}

void	update_entities(t_data *data)
{
	ft_entityiter(data, data->entities, entity_visible);
}
