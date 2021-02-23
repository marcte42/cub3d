/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_hud.C                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mterkhoy <mterkhoy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/22 18:35:34 by mterkhoy          #+#    #+#             */
/*   Updated: 2021/02/22 23:13:21 by mterkhoy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	draw_tile(t_data *data, t_crd pos, size_t size, int color)
{
	t_crd limit;

	limit.x = pos.x;
	limit.y = pos.y;
	while (pos.y < limit.y + size)
	{
		pos.x = limit.x;
		while (pos.x < limit.x + size)
		{
			data->frame.addr[pos.y * data->frame.line_length / 4
				+ pos.x] = color;
			pos.x++;
		}
		pos.y++;
	}
}

void	draw_map(t_data *data)
{
	int		i;
	int		j;
	t_crd	pos;

	i = -1;
	while (++i < data->cfg.map_size.y)
	{
		j = -1;
		while (++j < data->cfg.map_size.x)
		{
			pos.x = j * ((data->cfg.r.x / MAP_RATIO) / data->cfg.map_size.x)
						+ 10;
			pos.y = i * ((data->cfg.r.x / MAP_RATIO) / data->cfg.map_size.x)
						+ 10;
			if (data->cfg.map[i][j] == '1')
				draw_tile(data, pos, (data->cfg.r.x / MAP_RATIO) /
							data->cfg.map_size.x, 0x00FF0000);
			if (ft_strchr("-2NSWE", data->cfg.map[i][j]))
				draw_tile(data, pos, (data->cfg.r.x / MAP_RATIO) /
							data->cfg.map_size.x, 0x00000000);
		}
	}
}

void	draw_entities(t_data *data)
{
	t_crd	pos;
	size_t	i;

	i = -1;
	while (++i < data->entities_count)
	{
		pos.x = data->entities[i].pos.x / TILE_SIZE *
			((data->cfg.r.x / MAP_RATIO) / data->cfg.map_size.x) + 10;
		pos.y = data->entities[i].pos.y / TILE_SIZE *
			((data->cfg.r.x / MAP_RATIO) / data->cfg.map_size.x) + 10;
		data->frame.addr[pos.y * data->frame.line_length / 4 +
							pos.x] = 0x00FFFF00;
		data->frame.addr[pos.y * data->frame.line_length / 4 +
							(pos.x - 1)] = 0x00FFFF00;
		data->frame.addr[pos.y * data->frame.line_length / 4 +
							(pos.x + 1)] = 0x00FFFF00;
		data->frame.addr[(pos.y - 1) * data->frame.line_length / 4 +
							pos.x] = 0x00FFFF00;
		data->frame.addr[(pos.y + 1) * data->frame.line_length / 4 +
							pos.x] = 0x00FFFF00;
	}
}

void	draw_player(t_data *data)
{
	t_crd pos;

	pos.x = data->player.pos.x / TILE_SIZE *
		((data->cfg.r.x / MAP_RATIO) / data->cfg.map_size.x) + 10;
	pos.y = data->player.pos.y / TILE_SIZE *
		((data->cfg.r.x / MAP_RATIO) / data->cfg.map_size.x) + 10;
	data->frame.addr[pos.y * data->frame.line_length / 4 +
							pos.x] = 0x0000FF00;
	data->frame.addr[pos.y * data->frame.line_length / 4 +
							(pos.x - 1)] = 0x0000FF00;
	data->frame.addr[pos.y * data->frame.line_length / 4 +
							(pos.x + 1)] = 0x0000FF00;
	data->frame.addr[(pos.y - 1) * data->frame.line_length / 4 +
							pos.x] = 0x0000FF00;
	data->frame.addr[(pos.y + 1) * data->frame.line_length / 4 +
							pos.x] = 0x0000FF00;
}
