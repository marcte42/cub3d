/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mterkhoy <mterkhoy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/04 12:21:00 by mterkhoy          #+#    #+#             */
/*   Updated: 2021/02/18 13:37:56 by mterkhoy         ###   ########.fr       */
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

void	draw_line(t_data *data, int x1, int y1, int x2, int y2, int color)
{
	// Iterators, counters required by algorithm
    int x, y, dx, dy, dx1, dy1, px, py, xe, ye, i;
	t_crd pos;
    // Calculate line deltas
    dx = x2 - x1;
    dy = y2 - y1;
    // Create a positive copy of deltas (makes iterating easier)
    dx1 = abs(dx);
    dy1 = abs(dy);
    // Calculate error intervals for both axis
    px = 2 * dy1 - dx1;
    py = 2 * dx1 - dy1;
    // The line is X-axis dominant
    if (dy1 <= dx1) {
        // Line is drawn left to right
        if (dx >= 0) {
            x = x1; y = y1; xe = x2;
        } else { // Line is drawn right to left (swap ends)
            x = x2; y = y2; xe = x1;
        }
		pos.x = x;
		pos.y = y;
        draw_pixel(data, pos, color); // Draw first pixel
        // Rasterize the line
        for (int i = 0; x < xe; i++) {
            x = x + 1;
            // Deal with octants...
            if (px < 0) {
                px = px + 2 * dy1;
            } else {
                if ((dx < 0 && dy < 0) || (dx > 0 && dy > 0)) {
                    y = y + 1;
                } else {
                    y = y - 1;
                }
                px = px + 2 * (dy1 - dx1);
            }
            // Draw pixel from line span at
            // currently rasterized position
            pos.x = x;
			pos.y = y;
			draw_pixel(data, pos, color);
        }
    } else { // The line is Y-axis dominant
        // Line is drawn bottom to top
        if (dy >= 0) {
            x = x1; y = y1; ye = y2;
        } else { // Line is drawn top to bottom
            x = x2; y = y2; ye = y1;
        }
        pos.x = x;
		pos.y = y;
        draw_pixel(data, pos, color);
        // Rasterize the line
        for (int i = 0; y < ye; i++) {
            y = y + 1;
            // Deal with octants...
            if (py <= 0) {
                py = py + 2 * dx1;
            } else {
                if ((dx < 0 && dy<0) || (dx > 0 && dy > 0)) {
                    x = x + 1;
                } else {
                    x = x - 1;
                }
                py = py + 2 * (dx1 - dy1);
            }
            // Draw pixel from line span at
            // currently rasterized position
            pos.x = x;
			pos.y = y;
			draw_pixel(data, pos, color);
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
				draw_tile(data, pos, 0x00FF0000, 0);
		}
	}
}

void	draw_player(t_data *data)
{
	t_crd pos;

	pos.x = data->player.pos.x;
	pos.y = data->player.pos.y;
	draw_pixel(data, pos, 0x00FFFFFF);
}

void	draw_rays(t_data *data)
{
	size_t	i;

	i = -1;
	while (++i < data->cfg.r.x)
	//while (++i < 1)
		draw_line(data, data->player.pos.x, data->player.pos.y, data->rays[i].hit.x, data->rays[i].hit.y, 0x00FFFFFF);
}

void	draw_walls(t_data *data)
{
	t_crd	crd;
	for (int i = 0; i < data->cfg.r.x; i++) {
        float perpDistance = data->rays[i].distance * cos(data->rays[i].angle - data->player.angle);
        float distanceProjPlane = (data->cfg.r.x / 2) * tan(FOV / 2);
        float projectedWallHeight = (TILE_SIZE / perpDistance) * distanceProjPlane;

        int wallStripHeight = (int)projectedWallHeight;

        int wallTopPixel = (data->cfg.r.y / 2) - (wallStripHeight / 2);
        wallTopPixel = wallTopPixel < 0 ? 0 : wallTopPixel;

        int wallBottomPixel = (data->cfg.r.y / 2) + (wallStripHeight / 2);
        wallBottomPixel = wallBottomPixel > data->cfg.r.y ? data->cfg.r.y : wallBottomPixel;

        // render the wall from wallTopPixel to wallBottomPixel
        for (int y = wallTopPixel; y < wallBottomPixel; y++) {
			crd.x = i;
			crd.y = y;
            draw_pixel(data, crd, data->rays[i].horizontal ? 0x00FFFFFF : 0x00CCCCCC);
        }
    }
}

void	draw_floor(t_data *data)
{
	size_t	y;
	size_t	x;

	y = data->cfg.r.y / 2;
	while (y < data->cfg.r.y)
	{
		x = -1;
		while (++x < data->cfg.r.x)
			data->frame.addr[y * data->frame.line_length / 4 + x] = 0x00808080;
		y++;
	}
}

void	draw_ceiling(t_data *data)
{
	size_t	y;
	size_t	x;

	y = -1;
	while (++y < data->cfg.r.y / 2)
	{
		x = -1;
		while (++x < data->cfg.r.x)
			data->frame.addr[y * data->frame.line_length / 4 + x] = 0x0087CEEB;
	}
}

void	draw(t_data *data)
{
	data->frame.ptr = mlx_new_image(data->mlx.ptr, data->cfg.r.x, data->cfg.r.y);
	data->frame.addr = (int *)mlx_get_data_addr(data->frame.ptr, &(data->frame.bpp), &(data->frame.line_length), &(data->frame.endian));
	//draw_map(data);
	//draw_player(data);
	//draw_rays(data);
	draw_ceiling(data);
	draw_floor(data);
	draw_walls(data);
	//draw_world(data);
	//draw_entities(data);
	//draw_hud(data);
	mlx_put_image_to_window(data->mlx.ptr, data->mlx.win, data->frame.ptr, 0, 0);
	mlx_destroy_image(data->mlx.ptr, data->frame.ptr);
}
