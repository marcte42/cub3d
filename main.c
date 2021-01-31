/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mterkhoy <mterkhoy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/23 11:28:57 by mterkhoy          #+#    #+#             */
/*   Updated: 2021/01/31 16:36:26 by mterkhoy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "inc/cub3d.h"

void		mlx_draw_pixel(t_data *data, t_crd pos, int color)
{
	data->frame.addr[pos.y * data->frame.line_length / 4 + pos.x] = color;
}

void		mlx_draw_tile(t_data *data, t_crd pos, int color, int stroke)
{
	int		i;
	int		j;
	t_crd	npos;

	i = -1 + stroke;
	while (++i < data->cfg.tile_size - stroke)
	{
		j = -1 + stroke;
		while (++j < data->cfg.tile_size - stroke)
		{
			npos.x = pos.x + j;
			npos.y = pos.y + i;
			mlx_draw_pixel(data, npos, color);
		}
	}
}

void	flush_image(t_data *data)
{
	int		i;
	int		j;
	t_crd	pos;

	i = -1;
	while (++i < data->mlx.res.y)
	{
		j = -1;
		while (++j < data->mlx.res.x)
		{
			pos.x = j;
			pos.y = i;
			mlx_draw_pixel(data, pos, 0);
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
			pos.x = j * data->cfg.tile_size;
			pos.y = i * data->cfg.tile_size;
			if (data->cfg.map[i][j] == '1')
				mlx_draw_tile(data, pos, 0x00FF0000, 1);
			if (data->cfg.map[i][j] == '2')
				mlx_draw_tile(data, pos, 0x0000FF00, 12);
		}
	}
}

void	draw_player(t_data *data)
{
	t_crd	pos;

	pos.x = data->player.pos.x * data->cfg.tile_size;
	pos.y = data->player.pos.y * data->cfg.tile_size;
	mlx_draw_tile(data, pos, data->player.color, 10);
}

int			return_error(void)
{
	if (errno)
	{
		if (errno == ARG_EXISTS)
			printf("Error\nConfig: Duplicated parameters\n");
		else if (errno == PARAM_INVALID)
			printf("Error\nConfig: Parameters badly formated\n");
		else if (errno == TXT_ERROR)
			printf("Error\nConfig: Texture files corrupted\n");
		else if (errno == ARG_INVALID)
			printf("Error\nCongif: Invalid argument found\n");
		else if (errno == EMPTY_FILE)
			printf("Error\nCongif: Empty file\n");
		else if (errno == WRONG_TILE)
			printf("Error\nMap: Wrong tile in map description\n");
		else if (errno == MAP_LEAKING)
			printf("Error\nMap: Your map is leaking or the player is outside of the map\n");
		else if (errno == PLAYER_ERROR)
			printf("Error\nMap: Player is missing or multiple instances found\n");
		else if (errno == MAP_BLANK_LINE)
			printf("Error\nMap: Blank line\n");
		else
			perror("Error\nInternal");
		return (-1);
	}
	return (1);
}

int			main_loop(t_data *data)
{
	//update();
	//cast();
	//draw();
	if (data->frame.ptr)
		mlx_destroy_image(data->mlx.ptr, data->frame.ptr);
	data->frame.ptr = mlx_new_image(data->mlx.ptr, data->cfg.map_size.x * data->cfg.tile_size, data->cfg.map_size.y * data->cfg.tile_size);
	data->frame.addr = (int *)mlx_get_data_addr(data->frame.ptr, &data->frame.bpp, &data->frame.line_length, &data->frame.endian);
	draw_map(data);
	draw_player(data);
	mlx_put_image_to_window(data->mlx.ptr, data->mlx.win, data->frame.ptr, 0, 0);
	//flush_image(data);
	return (1);
}

int key_press(int keycode, t_data *data)
{
	if (keycode == 126 && data->cfg.map[data->player.pos.y - 1][data->player.pos.x] != '1')
		data->player.pos.y -= 1;
	if (keycode == 125 && data->cfg.map[data->player.pos.y + 1][data->player.pos.x] != '1')
		data->player.pos.y += 1;
	if (keycode == 123 && data->cfg.map[data->player.pos.y][data->player.pos.x - 1] != '1')
		data->player.pos.x -= 1;
	if (keycode == 124 && data->cfg.map[data->player.pos.y][data->player.pos.x + 1] != '1')
		data->player.pos.x += 1;
	return (1);
}

int key_release(int keycode, t_data *data)
{
	return (1);
}

int			main(int argc, char **argv)
{
	t_data	data;

	errno = 0;
	ft_bzero(&data, sizeof(data));
	if (!(parse_file("map.cub", &data)))
		return (return_error());
    data.mlx.ptr = mlx_init();
	data.mlx.res.x = data.cfg.map_size.x * data.cfg.tile_size;
	data.mlx.res.y = data.cfg.map_size.y * data.cfg.tile_size;
	data.mlx.win = mlx_new_window(data.mlx.ptr, data.mlx.res.x, data.mlx.res.y, "CUB3D");
	data.frame.ptr = NULL;
	mlx_hook(data.mlx.win, 2, 1L << 0, key_press, &data);
	mlx_hook(data.mlx.win, 3, 1L << 1, key_release, &data);
	mlx_loop_hook(data.mlx.ptr, main_loop, &data);
    mlx_loop(data.mlx.ptr);
	return (0);
}
