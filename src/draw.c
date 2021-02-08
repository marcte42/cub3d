/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mterkhoy <mterkhoy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/04 12:21:00 by mterkhoy          #+#    #+#             */
/*   Updated: 2021/02/07 20:25:36 by mterkhoy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void		draw_pixel(t_data *data, t_crd pos, int color)
{
	data->frame.addr[pos.y * data->frame.line_length / 4 + pos.x] = color;
}

void		draw_tile(t_data *data, t_crd pos, int color, int padding)
{
	int		i;
	int		j;
	t_crd	npos;

	i = -1 + padding;
	while (++i < TILE_SIZE - padding)
	{
		j = -1 + padding;
		while (++j < TILE_SIZE - padding)
		{
			npos.x = pos.x + j;
			npos.y = pos.y + i;
			draw_pixel(data, npos, color);
		}
	}
}

void	draw_map(t_data *data)
{
	int		i;
	int		j;
	t_crd 	pos;

	i = -1;
	while (++i < data->cfg.map_size.y)
	{
		j = -1;
		while (++j < data->cfg.map_size.x)
		{
			pos.x = j * TILE_SIZE;
			pos.y = i * TILE_SIZE;
			if (strchr("02NSEW -", data->cfg.map[i][j]))
				draw_tile(data, pos, 0x00000000, 0);
			if (data->cfg.map[i][j] == '1')
				draw_tile(data, pos, 0x00FF0000, 1);
		}
	}
}

void	draw_player(t_data *data)
{
	t_crd pos;

	pos.x = (int)(data->player.pos.x * TILE_SIZE);
	pos.y = (int)(data->player.pos.y * TILE_SIZE);
	draw_pixel(data, pos, 0x00FFFFFF);
}

void	draw_rays(t_data *data)
{
	size_t i;

	i = -1;
	while (++i < data->cfg.r.x)
	{

	}
}

void	draw(t_data *data)
{
	draw_map(data);
	draw_player(data);
	draw_rays(data);
	//draw_world(data);
	//draw_entities(data);
	//draw_hud(data);
	mlx_put_image_to_window(data->mlx.ptr, data->mlx.win, data->frame.ptr, 0, 0);
}
