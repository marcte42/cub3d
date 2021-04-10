/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mterkhoy <mterkhoy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/02 20:56:03 by mterkhoy          #+#    #+#             */
/*   Updated: 2021/03/27 13:30:45 by mterkhoy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int		engine(t_data *data)
{
	update(data);
	draw(data);
	return (0);
}

void	setup(t_data *data, char *file)
{
	parse(data, file);
	init(data);
}

void	cub3d(char *file, int save)
{
	t_data data;

	ft_bzero(&data, sizeof(data));
	data.save = save;
	setup(&data, file);
	if (!save)
		handle_events(&data);
	if (!save)
		mlx_loop_hook(data.mlx.ptr, engine, &data);
	else 
		engine(&data);
	mlx_loop(data.mlx.ptr);
}

int		main(int argc, char **argv)
{
	if (argc < 2 || argc > 3 ||
		(argc == 3 && ft_strcmp(argv[2], "--save") != 0))
	{
		write(1, "Usage : cub3D [map] [--save]\n", 29);
		return (1);
	}
	cub3d(argv[1], argc == 3);
	return (0);
}
