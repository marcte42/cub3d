/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mterkhoy <mterkhoy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/16 21:54:27 by mterkhoy          #+#    #+#             */
/*   Updated: 2021/02/23 09:54:58 by mterkhoy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	parse_resolution(char **params, t_data *data)
{
	if (arg_exists(params, data))
		error_params(data, params, "Duplicated parameters");
	else if (params_count(params) != 3 || !only_digit(params[1]) ||
		!only_digit(params[2]) || ft_atoi(params[1]) == 0 ||
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
			data->cfg.no = ft_strdup(params[1]);
		if (ft_strcmp(params[0], "SO") == 0)
			data->cfg.so = ft_strdup(params[1]);
		if (ft_strcmp(params[0], "WE") == 0)
			data->cfg.we = ft_strdup(params[1]);
		if (ft_strcmp(params[0], "EA") == 0)
			data->cfg.ea = ft_strdup(params[1]);
		if (ft_strcmp(params[0], "S") == 0)
			data->cfg.s = ft_strdup(params[1]);
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
	{
		free(line);
		exit_failure(data, "Malloc failed or your map is empty");
	}
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
		error_params(data, params, "Unknown parameter");
	else if ((params[0] || data->cfg.map_lst) && cfg_filled(data))
		parse_map(line, data);
	free_params(params);
}

int		parse(t_data *data, char *file)
{
	char	*line;
	int		fd;

	if ((fd = open(file, O_RDONLY)) < 0 || !ft_issuffix(file, ".cub"))
		exit_failure(data, "Bad filename");
	line = 0;
	while (get_next_line(fd, &line))
	{
		parse_selector(line, data);
		free(line);
	}
	if (!cfg_filled(data))
		exit_failure(data, "Empty file");
	map_to_mat(data);
	parse_player(data);
	if (is_map_leaking(data))
		exit_failure(data, "Map is leaking");
	if (line)
		free(line);
	return (1);
}
