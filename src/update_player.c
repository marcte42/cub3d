/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update_player.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mterkhoy <mterkhoy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/03 13:22:56 by mterkhoy          #+#    #+#             */
/*   Updated: 2021/02/07 17:00:29 by mterkhoy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int		is_colliding(t_fcrd pos, t_data *data)
{
	if (data->cfg.map[(int)pos.y][(int)pos.x] == '1' ||
		pos.x < 0 || pos.y < 0 ||
		(int)pos.x > data->cfg.map_size.x ||
		(int)pos.y > data->cfg.map_size.y)
		return (1);
	return (0);
}

void	player_move(t_data *data)
{
	t_fcrd pos;

	pos.x = data->player.pos.x;
	pos.y = data->player.pos.y;
	if (data->event.front)
	{
		pos.x += cos(data->player.angle) * data->event.front * SPEED;
		pos.y += -sin(data->player.angle) * data->event.front * SPEED;
		if (!is_colliding(pos, data))
		{
			data->player.pos.x = pos.x;
			data->player.pos.y = pos.y;
		}
	}
	if (data->event.side)
	{
		pos.x += sin(data->player.angle) * data->event.side * SPEED;
		pos.y += cos(data->player.angle) * data->event.side * SPEED;
		if (!is_colliding(pos, data))
		{
			data->player.pos.x = pos.x;
			data->player.pos.y = pos.y;
		}
	}
}

void	player_turn(t_data *data)
{
	t_fcrd	pos;
	float	angle;

	pos.x = data->player.pos.x;
	pos.y = data->player.pos.y;
	if (data->event.turn)
		data->player.angle += (data->event.turn * TURN_SPEED);
}

void	update_player(t_data *data)
{
	player_move(data);
	player_turn(data);
}
