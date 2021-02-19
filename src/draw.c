/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mterkhoy <mterkhoy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/04 12:21:00 by mterkhoy          #+#    #+#             */
/*   Updated: 2021/02/19 15:14:29 by mterkhoy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void		draw_pixel(t_data *data, t_crd pos, int color)
{
	data->frame.addr[pos.y * data->frame.line_length / 4 + pos.x] = color;
}

void		draw_tile(t_data *data, t_crd pos, size_t size, int color)
{
	t_crd limit;

	limit.x = pos.x;
	limit.y = pos.y;
	while (pos.y < limit.y + size)
	{
		pos.x = limit.x;
		while (pos.x < limit.x + size)
		{
			draw_pixel(data, pos, color);
			pos.x++;
		}
		pos.y++;
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
			pos.x = j * 10 + 10;
			pos.y = i * 10 + 10;
			if (data->cfg.map[i][j] == '1')
				draw_tile(data, pos, 10, 0x00FF0000);
			if (data->cfg.map[i][j] == '2')
				draw_tile(data, pos, 10, 0x0000FF00);
			if (ft_strchr("-NSWE", data->cfg.map[i][j]))
				draw_tile(data, pos, 10, 0x00000000);
		}
	}
}

void	draw_player(t_data *data)
{
	t_crd pos;

	pos.x = (data->player.pos.x + TILE_SIZE) * MAP_RATIO;
	pos.y = (data->player.pos.y + TILE_SIZE) * MAP_RATIO;
	draw_tile(data, pos, 2, 0x0000FF00);
}

void	draw_world(t_data *data)
{
	int		color;
	size_t	x;
	size_t	y;

	x = -1;
	while (++x < data->cfg.r.x)
	{
        float perp_distance = data->rays[x].distance * cos(data->rays[x].angle - data->player.angle);
		perp_distance = !perp_distance ? 1 : perp_distance;
        float plane_distance = (data->cfg.r.x / 2) * tan(FOV / 2);
        float wall_height = (TILE_SIZE / perp_distance) * plane_distance;

        int strip_height = (int)wall_height * 3;

        int wall_top = (data->cfg.r.y / 2) - (strip_height / 2);
		int tmp_top = wall_top;
		int wall_bottom = (data->cfg.r.y / 2) + (strip_height / 2);
		float ratio = 1.0 * TILE_SIZE / strip_height;
        wall_top = wall_top < 0 ? 0 : wall_top;
		wall_bottom = wall_bottom > data->cfg.r.y ? data->cfg.r.y : wall_bottom;

		y = 0;
		while (y < wall_top)
			data->frame.addr[y++ * data->frame.line_length / 4 + x] = data->cfg.c;
        while (y < wall_bottom)
		{
			if (data->rays[x].horizontal)
				if (data->rays[x].angle < M_PI && data->rays[x].angle > 0)
					color = data->textures[0].addr[(int)((y - tmp_top) * ratio) * data->textures[0].line_length / 4 + ((int)data->rays[x].hit.x % TILE_SIZE)];
				else
					color = data->textures[1].addr[(int)((y - tmp_top) * ratio) * data->textures[1].line_length / 4 + (TILE_SIZE - (int)data->rays[x].hit.x % TILE_SIZE)];
			else
				if (data->rays[x].angle < M_PI_2 || data->rays[x].angle > M_PI_2 * 3)
					color = (data->textures[2].addr[(int)((y - tmp_top) * ratio) * data->textures[2].line_length / 4 + ((int)data->rays[x].hit.y % TILE_SIZE)] >> 1) & 8355711;
				else
					color = (data->textures[3].addr[(int)((y - tmp_top) * ratio) * data->textures[3].line_length / 4 + (TILE_SIZE - (int)data->rays[x].hit.y % TILE_SIZE)] >> 1) & 8355711;
			data->frame.addr[y * data->frame.line_length / 4 + x] = color;
			y++;
		}
		while (y < data->cfg.r.y)
			data->frame.addr[y++ * data->frame.line_length / 4 + x] = data->cfg.f;
    }
}

void	draw_entities(t_data *data)
{

}

void	draw(t_data *data)
{
	data->frame.ptr = mlx_new_image(data->mlx.ptr, data->cfg.r.x, data->cfg.r.y);
	data->frame.addr = (int *)mlx_get_data_addr(data->frame.ptr, &data->frame.bpp, &data->frame.line_length, &data->frame.endian);

	//draw_rays(data);


	//
	draw_world(data);
	draw_map(data);
	//draw_player(data);
	//draw_entities(data);
	//draw_hud(data);

	mlx_put_image_to_window(data->mlx.ptr, data->mlx.win, data->frame.ptr, 0, 0);
	mlx_destroy_image(data->mlx.ptr, data->frame.ptr);
}
