/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_player.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: y██████ <y██████@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/20 15:59:12 by y██████          #+#    #+#             */
/*   Updated: 2023/02/20 18:39:27 by y██████         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

void	move_forward(t_data *d)
{
	if ((*d).map_info.map[(int)((*d).player.pos_x + \
		(*d).direction.dir_x * \
		(*d).ray_speed.move_speed)][(int)((*d).player.pos_y)] != '1')
		(*d).player.pos_x += (*d).direction.dir_x * \
		(*d).ray_speed.move_speed;
	if ((*d).map_info.map[(int)((*d).player.pos_x)][(int)((*d).player.pos_y \
		+ (*d).direction.dir_y * (*d).ray_speed.move_speed)] != '1')
		(*d).player.pos_y += (*d).direction.dir_y * \
		(*d).ray_speed.move_speed;
}

void	move_backward(t_data *d)
{
	if ((*d).map_info.map[(int)((*d).player.pos_x - \
		(*d).direction.dir_x * \
		(*d).ray_speed.move_speed)][(int)((*d).player.pos_y)] != '1')
		(*d).player.pos_x -= (*d).direction.dir_x * \
		(*d).ray_speed.move_speed;
	if ((*d).map_info.map[(int)((*d).player.pos_x)][(int)((*d).player.pos_y \
		- (*d).direction.dir_y * (*d).ray_speed.move_speed)] != '1')
		(*d).player.pos_y -= (*d).direction.dir_y * \
		(*d).ray_speed.move_speed;
}

void	move_left(t_data *d)
{
	if ((*d).map_info.map[(int)((*d).player.pos_x - \
		(*d).direction.dir_y * \
		(*d).ray_speed.move_speed)][(int)((*d).player.pos_y)] != '1')
		(*d).player.pos_x -= (*d).direction.dir_y * \
		(*d).ray_speed.move_speed;
	if ((*d).map_info.map[(int)((*d).player.pos_x)][(int)((*d).player.pos_y \
		+ (*d).direction.dir_x * (*d).ray_speed.move_speed)] != '1')
		(*d).player.pos_y += (*d).direction.dir_x * \
		(*d).ray_speed.move_speed;
}

void	move_right(t_data *d)
{
	if ((*d).map_info.map[(int)((*d).player.pos_x + \
		(*d).direction.dir_y * \
		(*d).ray_speed.move_speed)][(int)((*d).player.pos_y)] != '1')
		(*d).player.pos_x += (*d).direction.dir_y * \
		(*d).ray_speed.move_speed;
	if ((*d).map_info.map[(int)((*d).player.pos_x)][(int)((*d).player.pos_y \
		- (*d).direction.dir_x * (*d).ray_speed.move_speed)] != '1')
		(*d).player.pos_y -= (*d).direction.dir_x * \
		(*d).ray_speed.move_speed;
}
