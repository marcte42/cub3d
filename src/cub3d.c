/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mterkhoy <mterkhoy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/02 20:56:03 by mterkhoy          #+#    #+#             */
/*   Updated: 2021/02/19 13:20:05 by mterkhoy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	exit_failure(char *error)
{
	//free_struct(data);
	ft_putstr_fd("Error\n", STDERR_FILENO);
	ft_putstr_fd(error, STDERR_FILENO);
	ft_putstr_fd("\n", STDERR_FILENO);
	exit(1);
}

void	update(t_data *data)
{
	if (data->event.front || data->event.side || data->event.turn)
	{
		update_player(data);
	}
	raycast(data);
}

int		engine(t_data *data)
{
	update(data);
	draw(data);

	return (1);
}

void print_matrix(t_data *data)
{
	int i = -1;


	while (++i < data->cfg.map_size.y)
	{
		int j = -1;
		while (++j < data->cfg.map_size.x)
		{
			printf("%c", data->cfg.map[i][j]);
		}
		printf("\n");
	}
}

void	load_texturess(t_data *data)
{
	if (!(data->textures[0].ptr = mlx_xpm_file_to_image(data->mlx.ptr, data->cfg.no, &data->textures[0].width, &data->textures[0].height)))
		exit_failure("Unable to load textures NO");
	data->textures[0].addr = (int *)mlx_get_data_addr(data->textures[0].ptr, &data->textures[0].bpp, &data->textures[0].line_length, &data->textures[0].endian);

	if (!(data->textures[1].ptr = mlx_xpm_file_to_image(data->mlx.ptr, data->cfg.so, &data->textures[1].width, &data->textures[1].height)))
		exit_failure("Unable to load textures SO");
	data->textures[1].addr = (int *)mlx_get_data_addr(data->textures[1].ptr, &data->textures[1].bpp, &data->textures[1].line_length, &data->textures[1].endian);

	if (!(data->textures[2].ptr = mlx_xpm_file_to_image(data->mlx.ptr, data->cfg.we, &data->textures[2].width, &data->textures[2].height)))
		exit_failure("Unable to load textures WE");
	data->textures[2].addr = (int *)mlx_get_data_addr(data->textures[2].ptr, &data->textures[2].bpp, &data->textures[2].line_length, &data->textures[2].endian);

	if (!(data->textures[3].ptr = mlx_xpm_file_to_image(data->mlx.ptr, data->cfg.ea, &data->textures[3].width, &data->textures[3].height)))
		exit_failure("Unable to load textures EA");
	data->textures[3].addr = (int *)mlx_get_data_addr(data->textures[3].ptr, &data->textures[3].bpp, &data->textures[3].line_length, &data->textures[3].endian);
}

int		init_mlx(t_data *data)
{
	int x;
	int y;

	if (!(data->mlx.ptr = mlx_init()))
		return (0);

	mlx_get_screen_size(data->mlx.ptr, &x, &y);
	if (x < data->cfg.r.x)
		data->cfg.r.x = x;
	if (y < data->cfg.r.y)
		data->cfg.r.y = y;
	if (!(data->mlx.win = mlx_new_window(data->mlx.ptr, data->cfg.r.x, data->cfg.r.y, "Cub3D")))
		return (0);
	return (1);
}

int		mlx_end_loop(t_data *data)
{
	exit(0);
	//free_struct(data);
	return (1);
}

void	cub3d(char *map, t_bool save)
{
	t_data data;

	errno = 0;
	ft_bzero(&data, sizeof(data));
	parse_file(map, &data);
	print_matrix(&data);
	if (!init_mlx(&data))
		exit_failure("MLX initialization failed");
	load_texturess(&data);
	mlx_hook(data.mlx.win, KEY_PRESS, 1L << 0, key_press, &data);
	mlx_hook(data.mlx.win, KEY_RELEASE, 1L << 1, key_release, &data);
	mlx_hook(data.mlx.win, 17, 1L << 5, mlx_end_loop, &data);
	mlx_loop_hook(data.mlx.ptr, engine, &data);
	mlx_loop(data.mlx.ptr);
}

int		main(int argc, char **argv)
{
	if (argc < 2 || argc > 3 || (argc == 3 && strcmp(argv[2], "-save") != 0))
	{
		write(1, "Usage : cub3d [map] [-save]", 27);
		return (1);
	}
	cub3d(argv[1], argc == 3 ? 1 : 0);

	return (0);
}
