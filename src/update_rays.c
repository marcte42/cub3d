/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update_rays.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mterkhoy <mterkhoy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/05 12:25:33 by mterkhoy          #+#    #+#             */
/*   Updated: 2021/02/22 20:24:09 by mterkhoy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int		is_wall(t_data *data, float x, float y)
{
	if (ft_strchr("1 ", data->cfg.map[(int)y / TILE_SIZE][(int)x / TILE_SIZE]))
		return (1);
	return (0);
}

float	hit_distance(float p1_x, float p1_y, float p2_x, float p2_y)
{
	float	x;
	float	y;

	x = p1_x - p2_x;
	if (x < 0)
		x *= -1;
	y = p1_y - p2_y;
	if (y < 0)
		y *= -1;
	return (sqrtf(pow(x, 2) + pow(y, 2)));
}

void	cast_ray(t_data *data, t_ray *ray)
{
	float	x_intercept;
	float	y_intercept;
	float	x_step;
	float	y_step;
	float	h_x;
	float	h_y;
	float	v_x;
	float	v_y;
	int		h_found = 0;
	int		v_found = 0;
	float	y_dst;
	float	x_dst;
	float	h_dst;
	float	v_dst;

	y_intercept = floor(data->player.pos.y / TILE_SIZE) * TILE_SIZE;
	if (ray->angle < 0 || ray->angle > M_PI)
		y_intercept += TILE_SIZE;
	x_intercept = data->player.pos.x - (y_intercept - data->player.pos.y) / tan(ray->angle);
	y_step = TILE_SIZE;
	if (ray->angle > 0 && ray->angle < M_PI)
		y_step *= -1;
	x_step = TILE_SIZE / tan(ray->angle);
	if (x_step > 0 && ray->angle > M_PI_2 && ray->angle < (3 * M_PI) / 2)
		x_step *= -1;
	if (x_step < 0 && (ray->angle < M_PI_2 || ray->angle > (3 * M_PI) / 2))
		x_step *= -1;
	while (x_intercept > 0 && x_intercept < data->cfg.map_size.x * TILE_SIZE &&
			y_intercept > 0 && y_intercept < data->cfg.map_size.y * TILE_SIZE)
	{
		if (is_wall(data, x_intercept, y_intercept - ((ray->angle > 0 && ray->angle < M_PI) ? 1 : 0)))
		{
			h_found = 1;
			h_x = x_intercept;
			h_y = y_intercept;
			break ;
		}
		else
		{
			x_intercept += x_step;
			y_intercept += y_step;
		}
	}
	if (h_found)
		h_dst = hit_distance(data->player.pos.x, data->player.pos.y, h_x, h_y);
	x_intercept = floor(data->player.pos.x / TILE_SIZE) * TILE_SIZE;
	if (ray->angle < M_PI_2 || ray->angle > (3 * M_PI_2))
		x_intercept += TILE_SIZE;
	y_intercept = data->player.pos.y - (x_intercept - data->player.pos.x) * tan(ray->angle);
	x_step = TILE_SIZE;
	if (ray->angle > M_PI_2 && ray->angle < (3 * M_PI_2))
		x_step *= -1;
	y_step = TILE_SIZE * tan(ray->angle);
	if (y_step > 0 && ray->angle < M_PI && ray->angle > 0)
		y_step *= -1;
	if (y_step < 0 && (ray->angle > M_PI && ray->angle < M_PI * 2))
		y_step *= -1;
	while (x_intercept > 0 && x_intercept < data->cfg.map_size.x * TILE_SIZE &&
			y_intercept > 0 && y_intercept < data->cfg.map_size.y * TILE_SIZE)
	{
		if (is_wall(data, x_intercept - ((ray->angle > M_PI_2 && ray->angle < 3 * M_PI_2) ? 1 : 0), y_intercept))
		{
			v_found = 1;
			v_x = x_intercept;
			v_y = y_intercept;
			break ;
		}
		else
		{
			x_intercept += x_step;
			y_intercept += y_step;
		}
	}
	if (v_found)
		v_dst = hit_distance(data->player.pos.x, data->player.pos.y, v_x, v_y);
	if ((h_found && h_dst <= v_dst) || !v_found)
	{
		ray->horizontal = 1;
		ray->distance = h_dst;
		ray->hit.x = h_x;
		ray->hit.y = h_y;
	}
	else
	{
		ray->horizontal = 0;
		ray->distance = v_dst;
		ray->hit.x = v_x;
		ray->hit.y = v_y;
	}
}

void	update_rays(t_data *data)
{
	size_t	i;
	float	ray_angle;

	if (data->rays)
		free(data->rays);
	if (!(data->rays = malloc(data->cfg.r.x * sizeof(t_ray))))
		exit_failure(data, "Malloc failed");
	ray_angle = normalize_angle(data->player.angle + (FOV / 2));
	i = -1;
	while (++i < data->cfg.r.x)
	{
		data->rays[i].angle = ray_angle;
		if (ray_angle != 0 && ray_angle != M_PI)
			cast_ray(data, &data->rays[i]);
		ray_angle -= FOV / data->cfg.r.x;
		ray_angle = normalize_angle(ray_angle);
	}
}
