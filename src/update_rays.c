/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update_rays.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mterkhoy <mterkhoy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/05 12:25:33 by mterkhoy          #+#    #+#             */
/*   Updated: 2021/02/23 10:38:19 by mterkhoy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	horizontal_ray_math(t_data *data, t_ray *ray,
								t_fcrd *inter, t_fcrd *step)
{
	inter->y = floor(data->player.pos.y / TILE_SIZE) * TILE_SIZE;
	if (ray->angle < 0 || ray->angle > M_PI)
		inter->y += TILE_SIZE;
	inter->x = data->player.pos.x - (inter->y - data->player.pos.y) /
						tan(ray->angle);
	step->y = TILE_SIZE;
	if (ray->angle > 0 && ray->angle < M_PI)
		step->y *= -1;
	step->x = TILE_SIZE / tan(ray->angle);
	if (step->x > 0 && ray->angle > M_PI_2 && ray->angle < (3 * M_PI) / 2)
		step->x *= -1;
	if (step->x < 0 && (ray->angle < M_PI_2 || ray->angle > (3 * M_PI) / 2))
		step->x *= -1;
}

void	cast_horizontal(t_data *data, t_ray *ray)
{
	t_fcrd	inter;
	t_fcrd	step;

	horizontal_ray_math(data, ray, &inter, &step);
	while (inter.x > 0 && inter.x < data->cfg.map_size.x * TILE_SIZE &&
			inter.y > 0 && inter.y < data->cfg.map_size.y * TILE_SIZE)
	{
		if (is_wall(data, inter.x, inter.y -
						((ray->angle > 0 && ray->angle < M_PI) ? 1 : 0)))
		{
			ray->horizontal = 1;
			ray->hit.x = inter.x;
			ray->hit.y = inter.y;
			ray->distance = hit_distance(data->player.pos.x,
									data->player.pos.y, inter.x, inter.y);
			break ;
		}
		else
		{
			inter.x += step.x;
			inter.y += step.y;
		}
	}
}

void	vertical_ray_math(t_data *data, t_ray *ray, t_fcrd *inter, t_fcrd *step)
{
	inter->x = floor(data->player.pos.x / TILE_SIZE) * TILE_SIZE;
	if (ray->angle < M_PI_2 || ray->angle > (3 * M_PI_2))
		inter->x += TILE_SIZE;
	inter->y = data->player.pos.y - (inter->x - data->player.pos.x) *
								tan(ray->angle);
	step->x = TILE_SIZE;
	if (ray->angle > M_PI_2 && ray->angle < (3 * M_PI_2))
		step->x *= -1;
	step->y = TILE_SIZE * tan(ray->angle);
	if (step->y > 0 && ray->angle < M_PI && ray->angle > 0)
		step->y *= -1;
	if (step->y < 0 && (ray->angle > M_PI && ray->angle < M_PI * 2))
		step->y *= -1;
}

void	cast_vertical(t_data *data, t_ray *ray)
{
	t_fcrd	inter;
	t_fcrd	step;

	vertical_ray_math(data, ray, &inter, &step);
	while (inter.x > 0 && inter.x < data->cfg.map_size.x * TILE_SIZE &&
			inter.y > 0 && inter.y < data->cfg.map_size.y * TILE_SIZE)
		if (is_wall(data, inter.x -
		((ray->angle > M_PI_2 && ray->angle < 3 * M_PI_2) ? 1 : 0), inter.y))
		{
			if (!ray->horizontal || (ray->horizontal && hit_distance(
	data->player.pos.x, data->player.pos.y, inter.x, inter.y) < ray->distance))
			{
				ray->horizontal = 0;
				ray->hit.x = inter.x;
				ray->hit.y = inter.y;
				ray->distance = hit_distance(data->player.pos.x,
				data->player.pos.y, inter.x, inter.y);
			}
			break ;
		}
		else
		{
			inter.x += step.x;
			inter.y += step.y;
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
		data->rays[i].horizontal = 0;
		cast_horizontal(data, &data->rays[i]);
		cast_vertical(data, &data->rays[i]);
		ray_angle -= FOV / data->cfg.r.x;
		ray_angle = normalize_angle(ray_angle);
	}
}
