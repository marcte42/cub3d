/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mterkhoy <mterkhoy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/16 21:54:27 by mterkhoy          #+#    #+#             */
/*   Updated: 2021/04/15 13:51:08 by marcte           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	parse_resolution(char **params, t_data *data)
{
	if (arg_exists(params, data))
		error_params(data, params, "Duplicated parameters");
	else if (params_count(params) != 3 || !ft_onlydigit(params[1]) ||
		!ft_onlydigit(params[2]) || ft_atoi(params[1]) == 0 ||
		ft_atoi(params[2]) == 0)
		error_params(data, params, "Resolution parameter badly formated");
	else
	{
		data->cfg.r.x = ft_atoi(params[1]);
		data->cfg.r.y = ft_atoi(params[2]);
	}
}

void	parse_texture(char **params, t_data *data)
{
	int fd;

	if (arg_exists(params, data))
		error_params(data, params, "Duplicated parameters");
	else if (params_count(params) != 2)
		error_params(data, params, "Texture parameter badly formated");
	else if ((fd = open(params[1], O_RDONLY)) >= 0)
	{
		if (ft_strcmp(params[0], "NO") == 0)
			data->cfg.textures[0] = ft_strdup(params[1]);
		if (ft_strcmp(params[0], "SO") == 0)
			data->cfg.textures[1] = ft_strdup(params[1]);
		if (ft_strcmp(params[0], "WE") == 0)
			data->cfg.textures[2] = ft_strdup(params[1]);
		if (ft_strcmp(params[0], "EA") == 0)
			data->cfg.textures[3] = ft_strdup(params[1]);
		if (ft_strcmp(params[0], "S") == 0)
			data->cfg.textures[4] = ft_strdup(params[1]);
		close(fd);
	}
	else
		error_params(data, params, "Texture parameter not found");
}

void	parse_color(char **params, t_data *data)
{
	size_t	i;
	char	*color;
	char	*tmp;

	if (arg_exists(params, data))
		error_params(data, params, "Duplicated parameters");
	color = 0;
	i = 0;
	while (params[++i])
	{
		tmp = color;
		color = ft_strjoin(color, params[i]);
		if (tmp)
			free(tmp);
	}
	if (!color)
		error_params(data, params, "Malloc failed");
	if (ft_strcmp(params[0], "F") == 0)
		data->cfg.f_str = color;
	if (ft_strcmp(params[0], "C") == 0)
		data->cfg.c_str = color;
}

void	parse_selector(char *line, t_data *data)
{
	char **params;

	if (!(params = ft_split(line, SPACE)))
		exit_failure(data, "Malloc failed or your map is empty");
	if (params[0] && (ft_strcmp(params[0], "R") == 0))
		parse_resolution(params, data);
	else if (params[0] && ((ft_strcmp(params[0], "NO") == 0 ||
		ft_strcmp(params[0], "SO") == 0 || ft_strcmp(params[0], "EA") == 0 ||
		ft_strcmp(params[0], "WE") == 0 || ft_strcmp(params[0], "S") == 0)))
		parse_texture(params, data);
	else if (params[0] && (ft_strcmp(params[0], "F") == 0 ||
		ft_strcmp(params[0], "C") == 0))
		parse_color(params, data);
	else if (params[0] && !cfg_filled(data))
		error_params(data, params, "Unknown or missing parameter");
	else if ((params[0] || data->cfg.map_lst) && cfg_filled(data))
		parse_map(params, data);
	free_params(params);
}

int		parse(t_data *data, char *file)
{
	if ((data->fd = open(file, O_RDONLY)) < 0 || !ft_issuffix(file, ".cub"))
		exit_failure(data, "File not found or bad suffix");
	while (get_next_line(data->rest, data->fd, &data->line))
	{
		parse_selector(data->line, data);
		free(data->line);
	}
	parse_selector(data->line, data);
	if (!cfg_filled(data))
		exit_failure(data, "Empty file");
	map_to_mat(data);
	parse_player(data);
	if (is_map_leaking(data->player.pos.x, data->player.pos.y, data))
		exit_failure(data, "Map is leaking");
	return (1);
}
