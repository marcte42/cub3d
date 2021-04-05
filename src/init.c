/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mterkhoy <mterkhoy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/22 12:41:35 by mterkhoy          #+#    #+#             */
/*   Updated: 2021/03/27 16:46:02 by mterkhoy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	init_colors(t_data *data, char *color, int *spot)
{
	char	**colors;
	int		r;
	int		g;
	int		b;

	if (!(colors = ft_split(color, ",")))
		exit_failure(data, "Malloc failed");
	if (params_count(colors) != 3 || !ft_onlydigit(colors[0]) ||
		!ft_onlydigit(colors[1]) || !ft_onlydigit(colors[2]))
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
