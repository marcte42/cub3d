/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mterkhoy <mterkhoy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/16 21:54:27 by mterkhoy          #+#    #+#             */
/*   Updated: 2021/01/27 15:59:19 by mterkhoy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "inc/cub3d.h"

static int	only_digit(const char *s)
{
	while (*s)
	{
		if (!ft_isdigit(*s))
			return (0);
		s++;
	}
	return (1);
}

static int	params_count(char **params)
{
	size_t i;

	i = 0;
	while (params[i])
		i++;
	return (i);
}

static int	arg_exists(char **params, t_data *data)
{
	if (ft_strcmp(params[0], "NO") == 0 && data->cfg.no)
		return (1);
	else if (ft_strcmp(params[0], "SO") == 0 && data->cfg.so)
		return (1);
	else if (ft_strcmp(params[0], "WE") == 0 && data->cfg.we)
		return (1);
	else if (ft_strcmp(params[0], "EA") == 0 && data->cfg.ea)
		return (1);
	else if (ft_strcmp(params[0], "S") == 0 && data->cfg.s)
		return (1);
	return (0);
}

static int	cfg_filled(t_data *data)
{
	if (data->cfg.r.x && data->cfg.no && data->cfg.so && data->cfg.we &&
		data->cfg.ea && data->cfg.s && data->cfg.f && data->cfg.c)
		return (1);
	return (0);
}

static void	params_free(char **params)
{
	size_t i;

	i = -1;
	while (params[++i])
		free(params[i]);
	free(params);
}

static void	parse_resolution(char **params, t_data *data)
{
	if (data->cfg.r.x)
		errno = ARG_EXISTS;
	else if (params_count(params) != 3 || !only_digit(params[1]) ||
		!only_digit(params[2]))
		errno = PARAM_INVALID;
	else
	{
		data->cfg.r.x = ft_atoi(params[1]);
		data->cfg.r.y = ft_atoi(params[2]);
	}
}

static void	parse_texture(char **params, t_data *data)
{
	int fd;

	if (params_count(params) != 2)
		errno = PARAM_INVALID;
	else if (arg_exists(params, data))
		errno = ARG_EXISTS;
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
		errno = TXT_ERROR;
}

static void	parse_color(char **params, t_data *data)
{
	if (ft_strcmp(params[0], "F") == 0)
		data->cfg.f = ft_strdup(params[1]);
	if (ft_strcmp(params[0], "C") == 0)
		data->cfg.c = ft_strdup(params[1]);
}

static int	is_validtile(char tile, char *tiles)
{
	size_t i;

	i = -1;
	while (tiles[++i])
		if (tiles[i] == tile)
			return (1);
	return (0);
}

static t_crd	player_position(t_data *data)
{
	t_crd	player;
	int		i;
	int		j;

	i = -1;
	while (++i < data->cfg.map_size.y)
	{
		j = -1;
		while (++j < data->cfg.map_size.x)
		{
			if (data->cfg.map[i][j] == 'N' || data->cfg.map[i][j] == 'S' ||
				data->cfg.map[i][j] == 'W' || data->cfg.map[i][j] == 'E')
				{
					player.x = j;
					player.y = i;
				}
		}
	}
	return (player);
}

static int	spread(int x, int y, t_data *data)
{
	if (data->cfg.map[y][x] == ' ' || (data->cfg.map[y][x] == '0' && (y - 1 < 0 || x - 1 < 0 ||
		y + 1 >= data->cfg.map_size.y || x + 1 >= data->cfg.map_size.x)))
		{
			data->cfg.map[y][x] = '-';
			return (1);
		}
	if (data->cfg.map[y][x] == '0' || data->cfg.map[y][x] == 'N')
	{
		data->cfg.map[y][x] = '-';
		if (spread(x, y - 1, data))
			return (1);
		if (spread(x - 1, y, data))
			return (1);
		if (spread(x, y + 1, data))
			return (1);
		if (spread(x + 1, y, data))
			return (1);
	}
	return (0);
}

static int	is_map_leaking(t_data *data)
{
	t_crd	crd;

	crd = player_position(data);
	return (spread(crd.x, crd.y, data));
}

static void map_to_mat(t_data *data)
{
	size_t 	i;
	t_list	*lst;

	lst = data->cfg.map_tmp;
	data->cfg.map = malloc(data->cfg.map_size.y * sizeof(char *));
	i = -1;
	while (++i < data->cfg.map_size.y)
	{
		data->cfg.map[i] = malloc(data->cfg.map_size.x * sizeof(char));
		ft_memset(data->cfg.map[i], ' ', data->cfg.map_size.x);
		data->cfg.map[i] = ft_memcpy(data->cfg.map[i], lst->content, ft_strlen(lst->content));
		lst = lst->next;
	}
}

static void	parse_map(char *line, t_data *data)
{
	size_t	i;
	size_t	len;
	char	*new_line;

	len = strlen(line);
	i = -1;
	while (line[++i])
	{
		if (len > data->cfg.map_size.x)
			data->cfg.map_size.x = len;
		if (!is_validtile(line[i], TILES))
		{
			errno = WRONG_TILE;
			return ;
		}
	}
	ft_lstadd_back(&data->cfg.map_tmp, ft_lstnew(ft_strdup(line)));
	data->cfg.map_size.y++;
}

static int	parse_selector(char *line, t_data *data)
{
	char **params;

	if (!(params = ft_split(line, SPACE)))
		return (0);
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
		errno = ARG_INVALID;
	else if (params[0] && cfg_filled(data))
		parse_map(line, data);
	params_free(params);
	return (!errno);
}

int			parse_file(char *file, t_data *data)
{
	char	*line;
	int		fd;

	if ((fd = open(file, O_RDONLY)) < 0)
		return (0);
	line = 0;
	while (get_next_line(fd, &line))
	{
		if (!(parse_selector(line, data)))
		{
			free(line);
			return (0);
		}
		free(line);
	}
	if (!cfg_filled(data))
	{
		errno = EMPTY_FILE;
		return (0);
	}
	map_to_mat(data);
	printf("%d\n", is_map_leaking(data));
	if (line)
		free(line);
	return (1);
}
