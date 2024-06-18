/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_up_player.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: f██████ <f██████@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/20 15:59:15 by y██████          #+#    #+#             */
/*   Updated: 2024/06/18 07:41:28 by f██████          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

/*
	The field of view chosen is 65 degrees.
	Plane values are modified to match the direction change. Indeed, the plane
	always has to be perpendicular to the direction.
*/
static void	start_north(t_data *data)
{
	(*data).direction.dir_x = -1.001;
	(*data).direction.dir_y = 0.001;
	(*data).plane.plane_x = 0.0;
	(*data).plane.plane_y = 0.65;
}

static void	start_south(t_data *data)
{
	(*data).direction.dir_x = 1.001;
	(*data).direction.dir_y = 0.001;
	(*data).plane.plane_x = 0.0;
	(*data).plane.plane_y = -0.65;
}

static void	start_east(t_data *data)
{
	(*data).direction.dir_x = 0.001;
	(*data).direction.dir_y = 1.001;
	(*data).plane.plane_x = 0.65;
	(*data).plane.plane_y = 0.0;
}

static void	start_west(t_data *data)
{
	(*data).direction.dir_x = 0.001;
	(*data).direction.dir_y = -1.001;
	(*data).plane.plane_x = -0.65;
	(*data).plane.plane_y = 0.0;
}

void	set_up_player(t_data *data)
{
	if ((*data).map_info.pos_start_orientation == 'N')
		start_north(data);
	else if ((*data).map_info.pos_start_orientation == 'S')
		start_south(data);
	else if ((*data).map_info.pos_start_orientation == 'E')
		start_east(data);
	else if ((*data).map_info.pos_start_orientation == 'W')
		start_west(data);
	(*data).ray_speed.move_speed = 0.1;
	(*data).ray_speed.rot_speed = 0.05;
	data->ac[0] = 0;
	data->ac[1] = 0;
}
