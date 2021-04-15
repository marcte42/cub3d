/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_world.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mterkhoy <mterkhoy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/27 13:43:11 by mterkhoy          #+#    #+#             */
/*   Updated: 2021/04/15 21:10:01 by marcte           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	strip_init(t_data *data, t_strip *strip, size_t x)
{
	strip->perp_distance = data->rays[x].distance
							* cos(data->rays[x].angle - data->player.angle);
	strip->plane_distance = (data->cfg.r.x / 2) * tan(FOV / 2);
	strip->height = (TILE_SIZE / strip->perp_distance)
					* strip->plane_distance * 3;
	strip->top = (data->cfg.r.y / 2) - (strip->height / 2);
	strip->tmp_top = strip->top;
	strip->bottom = (data->cfg.r.y / 2) + (strip->height / 2);
	strip->top = strip->top < 0 ? 0 : strip->top;
	strip->bottom = strip->bottom > data->cfg.r.y ?
								data->cfg.r.y : strip->bottom;
}

void	find_h_strip_color(t_data *data, t_strip *strip, size_t x, size_t y)
{
	if (data->rays[x].angle < M_PI && data->rays[x].angle > 0)
		strip->color = data->textures[0].addr[(int)((y - strip->tmp_top)
		* (float)data->textures[0].height / strip->height)
		* data->textures[0].line_length / 4
		+ (int)((int)data->rays[x].hit.x % TILE_SIZE
		* data->textures[0].width / TILE_SIZE)];
	else
		strip->color = data->textures[1].addr[(int)((y - strip->tmp_top)
		* (float)data->textures[1].height / strip->height)
		* data->textures[1].line_length / 4
		+ (data->textures[1].width - (int)((int)data->rays[x].hit.x % TILE_SIZE
		* data->textures[1].width / TILE_SIZE))];
}

void	find_v_strip_color(t_data *data, t_strip *strip, size_t x, size_t y)
{
	if (data->rays[x].angle < M_PI_2 || data->rays[x].angle > M_PI_2 * 3)
		strip->color = (data->textures[3].addr[(int)((y - strip->tmp_top)
		* (float)data->textures[3].height / strip->height)
		* data->textures[3].line_length / 4
		+ (int)((int)data->rays[x].hit.y % TILE_SIZE
		* data->textures[3].width / TILE_SIZE)] >> 1) & 8355711;
	else
		strip->color = (data->textures[2].addr[(int)((y - strip->tmp_top)
		* (float)data->textures[2].height / strip->height)
		* data->textures[2].line_length / 4
		+ (data->textures[2].width - (int)((int)data->rays[x].hit.y % TILE_SIZE
		* data->textures[2].width / TILE_SIZE))] >> 1)
		& 8355711;
}

void	find_strip_color(t_data *data, t_strip *strip, size_t x, size_t y)
{
	if (data->rays[x].horizontal)
		find_h_strip_color(data, strip, x, y);
	else
		find_v_strip_color(data, strip, x, y);
}

void	draw_world(t_data *data)
{
	t_strip	strip;
	int		x;
	int		y;

	x = -1;
	while (++x < data->cfg.r.x)
	{
		strip_init(data, &strip, x);
		y = 0;
		while (y < strip.top)
			data->frame.addr[y++ *
				data->frame.line_length / 4 + x] = data->cfg.c;
		while (y < strip.bottom)
		{
			find_strip_color(data, &strip, x, y);
			data->frame.addr[y *
				data->frame.line_length / 4 + x] = strip.color;
			y++;
		}
		while (y < data->cfg.r.y)
			data->frame.addr[y++ *
				data->frame.line_length / 4 + x] = data->cfg.f;
	}
}
