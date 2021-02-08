/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mterkhoy <mterkhoy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/05 12:25:33 by mterkhoy          #+#    #+#             */
/*   Updated: 2021/02/07 17:27:58 by mterkhoy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	cast_horizontal(t_data *data, t_ray *ray)
{
	printf("%f\n", data->player.pos.x - (int)data->player.pos.x + cos(ray->angle));

	// h = racine(a^2 + b^2)
}

static void	cast_ray(t_data *data, t_ray *ray)
{
	if (ray->angle != 0 && ray->angle != M_PI)
		cast_horizontal(data, ray);
	//cast_vertical();
}

void		raycast(t_data *data)
{
	size_t	i;
	float	ray_angle;

	if (!(data->rays = malloc(data->cfg.r.x * sizeof(t_ray))))
		exit_failure("Error");
	/*ray_angle = data->player.angle + (FOV / 2);
	i = -1;
	while (++i < data->cfg.r.x)
	{
		data->rays[i].angle = ray_angle;
		cast_ray(data, &data->rays[i]);
		ray_angle -= (FOV / 2) / data->cfg.r.x;
	}/*
}
