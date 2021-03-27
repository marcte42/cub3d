/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mterkhoy <mterkhoy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/22 12:41:35 by mterkhoy          #+#    #+#             */
/*   Updated: 2021/03/27 12:45:41 by mterkhoy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int		*get_texture_addr(t_data *data, int n)
{
	return ((int *)mlx_get_data_addr(data->textures[n].ptr,
										&data->textures[n].bpp,
										&data->textures[n].line_length,
										&data->textures[n].endian));
}

void	*get_texture_ptr(t_data *data, int n)
{
	return (mlx_xpm_file_to_image(data->mlx.ptr, data->cfg.textures[n],
	&data->textures[n].width, &data->textures[n].height));
}

void	init_textures(t_data *data)
{
	if (!(data->textures[0].ptr = get_texture_ptr(data, 0)))
		exit_failure(data, "Unable to load texture");
	data->textures[0].addr = get_texture_addr(data, 0);
	if (!(data->textures[1].ptr = get_texture_ptr(data, 1)))
		exit_failure(data, "Unable to load texture");
	data->textures[1].addr = get_texture_addr(data, 1);
	if (!(data->textures[2].ptr = get_texture_ptr(data, 2)))
		exit_failure(data, "Unable to load texture");
	data->textures[2].addr = get_texture_addr(data, 2);
	if (!(data->textures[3].ptr = get_texture_ptr(data, 3)))
		exit_failure(data, "Unable to load texture");
	data->textures[3].addr = get_texture_addr(data, 3);
	if (!(data->textures[4].ptr = get_texture_ptr(data, 4)))
		exit_failure(data, "Unable to load texture");
	data->textures[4].addr = get_texture_addr(data, 4);
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
	if (!data->save)
		init_window(data);
}
