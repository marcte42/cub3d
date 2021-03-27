/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_helpers.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mterkhoy <mterkhoy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/22 17:47:37 by mterkhoy          #+#    #+#             */
/*   Updated: 2021/03/27 12:43:52 by mterkhoy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int		arg_exists(char **params, t_data *data)
{
	if (ft_strcmp(params[0], "R") == 0 && data->cfg.r.x)
		return (1);
	else if (ft_strcmp(params[0], "NO") == 0 && data->cfg.textures[0])
		return (1);
	else if (ft_strcmp(params[0], "SO") == 0 && data->cfg.textures[1])
		return (1);
	else if (ft_strcmp(params[0], "WE") == 0 && data->cfg.textures[2])
		return (1);
	else if (ft_strcmp(params[0], "EA") == 0 && data->cfg.textures[3])
		return (1);
	else if (ft_strcmp(params[0], "S") == 0 && data->cfg.textures[4])
		return (1);
	else if (ft_strcmp(params[0], "F") == 0 && data->cfg.f_str)
		return (1);
	else if (ft_strcmp(params[0], "C") == 0 && data->cfg.c_str)
		return (1);
	return (0);
}

int		cfg_filled(t_data *data)
{
	if (data->cfg.r.x && data->cfg.textures[0] && data->cfg.textures[1]
		&& data->cfg.textures[2] && data->cfg.textures[3]
		&& data->cfg.textures[4] && data->cfg.f_str && data->cfg.c_str)
		return (1);
	return (0);
}

float	get_angle(char direction)
{
	if (direction == 'N')
		return (M_PI / 2);
	if (direction == 'S')
		return (3 * M_PI / 2);
	if (direction == 'W')
		return (M_PI);
	return (0);
}
