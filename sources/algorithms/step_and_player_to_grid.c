/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   step_and_player_to_grid.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: f██████ <f██████@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/20 15:58:24 by y██████          #+#    #+#             */
/*   Updated: 2024/01/08 03:15:28 by f██████          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

/*
	player_to_grid is the distance between the player's position and 
	the next grid line in the X or Y direction, 
	depending on the orientation of the ray.
	pos is the exact position (double)
	map is the position on the grid (int)
	Multiplied by side_to_side to have the corresponding length ratio.
*/
static void	raydir_known(t_data *data)
{
	if ((*data).rpd.ray_dir_x < 0)
	{
		(*data).dir_step.step_x = -1;
		(*data).ptg.player_to_grid_x = ((*data).player.pos_x - \
			(*data).box.map_x) * (*data).fsns.side_to_side_x;
	}
	else
	{
		(*data).dir_step.step_x = 1;
		(*data).ptg.player_to_grid_x = ((*data).box.map_x + 1.0 - \
			(*data).player.pos_x) * (*data).fsns.side_to_side_x;
	}
	if ((*data).rpd.ray_dir_y < 0)
	{
		(*data).dir_step.step_y = -1;
		(*data).ptg.player_to_grid_y = ((*data).player.pos_y - \
			(*data).box.map_y) * (*data).fsns.side_to_side_y;
	}
	else
	{
		(*data).dir_step.step_y = 1;
		(*data).ptg.player_to_grid_y = ((*data).box.map_y + 1.0 - \
			(*data).player.pos_y) * (*data).fsns.side_to_side_y;
	}
}

/*

	1 (camera_x). -1 or 0 or 1
	1 (camera_x, ray_dir_x, ray_dir_y). calculate ray position and direction
	2 (map_x, map_y). which box of the map we're in
	3 (side_to_side_x, side_to_side_y). length of ray from one x or y-side 
	  to next x or y-side. These are expressed as a ratio.
	  side_to_side_x is the ratio length the ray goes from one x grid line to
	  the next.
*/
void	step_and_player_to_grid(t_data *data, int x)
{
	(*data).rpd.camera_x = 2 * x / (double)(*data).win_size.win_w - 1;
	(*data).rpd.ray_dir_x = (*data).direction.dir_x + (*data).plane.plane_x * \
		(*data).rpd.camera_x;
	(*data).rpd.ray_dir_y = (*data).direction.dir_y + (*data).plane.plane_y * \
		(*data).rpd.camera_x;
	(*data).box.map_x = (int)(*data).player.pos_x;
	(*data).box.map_y = (int)(*data).player.pos_y;
	if ((*data).rpd.ray_dir_x == 0.0)
		(*data).fsns.side_to_side_x = 1e30;
	else
		(*data).fsns.side_to_side_x = fabs(1 / (*data).rpd.ray_dir_x);
	if ((*data).rpd.ray_dir_y == 0.0)
		(*data).fsns.side_to_side_y = 1e30;
	else
		(*data).fsns.side_to_side_y = fabs(1 / (*data).rpd.ray_dir_y);
	raydir_known(data);
}
