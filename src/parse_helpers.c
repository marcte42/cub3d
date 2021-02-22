/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_helpers.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mterkhoy <mterkhoy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/22 17:47:37 by mterkhoy          #+#    #+#             */
/*   Updated: 2021/02/22 18:47:41 by mterkhoy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int		arg_exists(char **params, t_data *data)
{
	if (ft_strcmp(params[0], "R") == 0 && data->cfg.r.x)
		return (1);
	else if (ft_strcmp(params[0], "NO") == 0 && data->cfg.no)
		return (1);
	else if (ft_strcmp(params[0], "SO") == 0 && data->cfg.so)
		return (1);
	else if (ft_strcmp(params[0], "WE") == 0 && data->cfg.we)
		return (1);
	else if (ft_strcmp(params[0], "EA") == 0 && data->cfg.ea)
		return (1);
	else if (ft_strcmp(params[0], "S") == 0 && data->cfg.s)
		return (1);
	else if (ft_strcmp(params[0], "F") == 0 && data->cfg.f_str)
		return (1);
	else if (ft_strcmp(params[0], "C") == 0 && data->cfg.c_str)
		return (1);
	return (0);
}

int		cfg_filled(t_data *data)
{
	if (data->cfg.r.x && data->cfg.no && data->cfg.so && data->cfg.we &&
		data->cfg.ea && data->cfg.s && data->cfg.f_str && data->cfg.c_str)
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
