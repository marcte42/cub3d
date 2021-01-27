/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mterkhoy <mterkhoy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/23 11:28:57 by mterkhoy          #+#    #+#             */
/*   Updated: 2021/01/27 14:40:54 by mterkhoy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "inc/cub3d.h"

/*void		mlx_draw_pixel(t_data *data, t_crd pos, int color)
{
	data->frame.addr[pos.y * data->frame.line_length / 4 + pos.x] = color;
}

void		mlx_draw_tile(t_data *data, t_crd pos, int color)
{
	int		i;
	int		j;
	t_crd	npos;

	i = -1;
	while (++i < data->cfg.tile_size)
	{
		j = -1;
		while (++j < data->cfg.tile_size)
		{
			npos.x = pos.x + j;
			npos.y = pos.y + i;
			mlx_draw_pixel(data, npos, color);
		}
	}
}

void draw_map(t_data *data)
{
	int		i;
	int		j;
	t_crd 	pos;

	i = -1;
	while (++i < data->cfg.map_size.y)
	{
		j = -1;
		while (++j < data->cfg.map_size.x)
			if (data->cfg.map[i * data->cfg.map_size.x + j] == 1)
			{
				pos.x = j * data->cfg.tile_size;
				pos.y = i * data->cfg.tile_size;
				mlx_draw_tile(data, pos, 0x00ff0000);
			}
	}
}*/

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
		else
			perror("Error\nInternal");
		return (-1);
	}
	// ADD SOME FREE FUNCTION TU CLEAN ALL THE STRUCT
	return (1);
}

int			main(void)
{
	t_data	data;

	errno = 0;
	ft_bzero(&data, sizeof(data));
	if (!(parse_file("map.cub", &data)))
		return (return_error());

	for (int i = 0; i < data.cfg.map_size.y; i++)
	{
		for (int j = 0; j < data.cfg.map_size.x; j++)
		{
			printf("%c", data.cfg.map[i][j]);
		}
		printf("\n");
	}
	return (0);
    /*data.mlx.ptr = mlx_init();
	data.mlx.res.x = data.cfg.map_size.x * data.cfg.tile_size;
	data.mlx.res.y = data.cfg.map_size.y * data.cfg.tile_size;
	data.mlx.win = mlx_new_window(data.mlx.ptr, data.mlx.res.x, data.mlx.res.y, "CUB3D");

	data.frame.ptr = mlx_new_image(data.mlx.ptr, data.cfg.map_size.x * data.cfg.tile_size, data.cfg.map_size.y * data.cfg.tile_size);
	data.frame.addr = (int *)mlx_get_data_addr(data.frame.ptr, &data.frame.bpp, &data.frame.line_length, &data.frame.endian);
	draw_map(&data);
	mlx_put_image_to_window(data.mlx.ptr, data.mlx.win, data.frame.ptr, 0, 0);

    mlx_loop(data.mlx.ptr);*/
}
