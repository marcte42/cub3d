/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mterkhoy <mterkhoy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/22 12:41:35 by mterkhoy          #+#    #+#             */
/*   Updated: 2021/02/23 19:10:34 by mterkhoy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	init_textures(t_data *data)
{
	if (!(data->textures[0].ptr = mlx_xpm_file_to_image(data->mlx.ptr, data->cfg.no, &data->textures[0].width, &data->textures[0].height)))
		exit_failure(data, "Unable to load texture");
	data->textures[0].addr = (int *)mlx_get_data_addr(data->textures[0].ptr, &data->textures[0].bpp, &data->textures[0].line_length, &data->textures[0].endian);
	if (!(data->textures[1].ptr = mlx_xpm_file_to_image(data->mlx.ptr, data->cfg.so, &data->textures[1].width, &data->textures[1].height)))
		exit_failure(data, "Unable to load texture");
	data->textures[1].addr = (int *)mlx_get_data_addr(data->textures[1].ptr, &data->textures[1].bpp, &data->textures[1].line_length, &data->textures[1].endian);
	if (!(data->textures[2].ptr = mlx_xpm_file_to_image(data->mlx.ptr, data->cfg.we, &data->textures[2].width, &data->textures[2].height)))
		exit_failure(data, "Unable to load texture");
	data->textures[2].addr = (int *)mlx_get_data_addr(data->textures[2].ptr, &data->textures[2].bpp, &data->textures[2].line_length, &data->textures[2].endian);
	if (!(data->textures[3].ptr = mlx_xpm_file_to_image(data->mlx.ptr, data->cfg.ea, &data->textures[3].width, &data->textures[3].height)))
		exit_failure(data, "Unable to load texture");
	data->textures[3].addr = (int *)mlx_get_data_addr(data->textures[3].ptr, &data->textures[3].bpp, &data->textures[3].line_length, &data->textures[3].endian);
	if (!(data->textures[4].ptr = mlx_xpm_file_to_image(data->mlx.ptr, data->cfg.s, &data->textures[4].width, &data->textures[4].height)))
		exit_failure(data, "Unable to load texture");
	data->textures[4].addr = (int *)mlx_get_data_addr(data->textures[4].ptr, &data->textures[4].bpp, &data->textures[4].line_length, &data->textures[4].endian);
}

void	init_colors(t_data *data, char *color, int *spot)
{
	char	**colors;
	int		r;
	int		g;
	int		b;

	if (!(colors = ft_split(color, ",")))
		exit_failure(data, "Malloc failed");
	if (params_count(colors) != 3 || !only_digit(colors[0]) ||
		!only_digit(colors[1]) || !only_digit(colors[2]))
		exit_failure(data, "Color parameter badly formated");
	r = ft_atoi(colors[0]);
	g = ft_atoi(colors[1]);
	b = ft_atoi(colors[2]);
	free_params(colors);
	if (r < 0 || r > 255 || g < 0 || g > 255 || b < 0 || b > 255)
		exit_failure(data, "Color parameter out of range");
	*spot = r << 16 | g << 8 | b;
}

void	init_player(t_data *data)
{
	data->player.pos.x = data->player.pos.x * TILE_SIZE + TILE_SIZE / 2;
	data->player.pos.y = data->player.pos.y * TILE_SIZE + TILE_SIZE / 2;
}

void	init_window(t_data *data)
{
	int x;
	int y;

	mlx_get_screen_size(data->mlx.ptr, &x, &y);
	if (x < data->cfg.r.x)
		data->cfg.r.x = x;
	if (y < data->cfg.r.y)
		data->cfg.r.y = y;
	data->mlx.win = mlx_new_window(data->mlx.ptr, data->cfg.r.x,
	data->cfg.r.y, "Cub3D");
}

void	init(t_data *data)
{
	data->mlx.ptr = mlx_init();
	init_colors(data, data->cfg.c_str, &data->cfg.c);
	init_colors(data, data->cfg.f_str, &data->cfg.f);
	init_textures(data);
	init_player(data);
	init_entities(data);
	init_window(data);
}
