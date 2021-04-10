/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update_entities.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mterkhoy <mterkhoy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/27 14:03:37 by mterkhoy          #+#    #+#             */
/*   Updated: 2021/04/09 23:17:41 by mterkhoy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

float ft_lerp(float p1, float p2, float t) {
    return (p1*(1-t)+p2*t);
}

void	update_entity(t_data *data, t_entity *entity)
{
	float angle;
	float distance;

	if ((distance = hit_distance(data->player.pos.x, data->player.pos.y, entity->pos.x, entity->pos.y)) < TILE_SIZE * 7)
	{
		if (distance > TILE_SIZE * 2)
		{
			entity->pos.x = ft_lerp(entity->pos.x, data->player.pos.x, 0.005);
			entity->pos.y = ft_lerp(entity->pos.y, data->player.pos.y, 0.005);
		}
		else
		{
			if (data->player.health < 0)
				printf("Player dead !\n");
			else
				printf("Player health : %d\n", data->player.health--);
		}
	}
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
	ft_entityiter(data, data->entities, update_entity);
}
