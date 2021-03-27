/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mterkhoy <mterkhoy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/22 12:47:02 by mterkhoy          #+#    #+#             */
/*   Updated: 2021/03/27 12:52:20 by mterkhoy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	free_params(char **params)
{
	size_t i;

	if (!params)
		return ;
	i = -1;
	while (params[++i])
		free(params[i]);
	free(params);
}

void	free_struct(t_data *data)
{
	int i;

	if (data->rays)
		free(data->rays);
	if (data->entities)
		ft_lstclear(&data->entities, free);
	i = -1;
	while (++i < T_COUNT)
		if (data->cfg.textures[i])
			free(data->cfg.textures[i]);
	if (data->cfg.c_str)
		free(data->cfg.c_str);
	if (data->cfg.f_str)
		free(data->cfg.f_str);
	if (data->cfg.map_lst)
		ft_lstclear(&data->cfg.map_lst, free);
	if (data->cfg.map)
	{
		while (--data->cfg.map_size.y >= 0
				&& data->cfg.map[data->cfg.map_size.y])
			free(data->cfg.map[data->cfg.map_size.y]);
		free(data->cfg.map);
	}
	if (data->mlx.win)
		mlx_destroy_window(data->mlx.ptr, data->mlx.win);
}

void	exit_failure(t_data *data, char *error)
{
	free_struct(data);
	if (error)
	{
		ft_putstr_fd("Error\n", STDERR_FILENO);
		ft_putstr_fd(error, STDERR_FILENO);
		ft_putstr_fd("\n", STDERR_FILENO);
		system("leaks cub3d");
		exit(1);
	}
	system("leaks cub3d");
	exit(0);
}

void	error_params(t_data *data, char **params, char *error)
{
	free_params(params);
	exit_failure(data, error);
}
