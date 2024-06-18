/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   look_player.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: f██████ <f██████@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/20 15:59:10 by y██████          #+#    #+#             */
/*   Updated: 2024/06/18 07:41:28 by f██████          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

void	look_right(t_data *data)
{
	double	old_dir_x;
	double	old_plane_x;

	old_dir_x = (*data).direction.dir_x;
	(*data).direction.dir_x = (*data).direction.dir_x * \
		cos(-(*data).ray_speed.rot_speed) - (*data).direction.dir_y * \
		sin(-(*data).ray_speed.rot_speed);
	(*data).direction.dir_y = old_dir_x * \
		sin(-(*data).ray_speed.rot_speed) + (*data).direction.dir_y * \
		cos(-(*data).ray_speed.rot_speed);
	old_plane_x = (*data).plane.plane_x;
	(*data).plane.plane_x = (*data).plane.plane_x * \
		cos(-(*data).ray_speed.rot_speed) - (*data).plane.plane_y * \
		sin(-(*data).ray_speed.rot_speed);
	(*data).plane.plane_y = old_plane_x * \
		sin(-(*data).ray_speed.rot_speed) + (*data).plane.plane_y * \
		cos(-(*data).ray_speed.rot_speed);
}

void	look_left(t_data *data)
{
	double	old_dir_x;
	double	old_plane_x;

	old_dir_x = (*data).direction.dir_x;
	(*data).direction.dir_x = (*data).direction.dir_x * \
		cos((*data).ray_speed.rot_speed) - (*data).direction.dir_y * \
		sin((*data).ray_speed.rot_speed);
	(*data).direction.dir_y = old_dir_x * \
		sin((*data).ray_speed.rot_speed) + (*data).direction.dir_y * \
		cos((*data).ray_speed.rot_speed);
	old_plane_x = (*data).plane.plane_x;
	(*data).plane.plane_x = (*data).plane.plane_x * \
		cos((*data).ray_speed.rot_speed) - (*data).plane.plane_y * \
		sin((*data).ray_speed.rot_speed);
	(*data).plane.plane_y = old_plane_x * \
		sin((*data).ray_speed.rot_speed) + (*data).plane.plane_y * \
		cos((*data).ray_speed.rot_speed);
}
