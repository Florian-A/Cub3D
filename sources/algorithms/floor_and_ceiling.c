/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   floor_and_ceiling.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: y██████ <y██████@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/20 15:58:21 by y██████          #+#    #+#             */
/*   Updated: 2023/02/20 18:38:23 by y██████         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

/*
	ray_dir for leftmost ray (x = 0) and rightmost ray (x = w)
*/
static void	raydir_for_leftmost_rightmost_ray(t_data *data)
{
	(*data).rpd.ray_dir_x0 = (*data).direction.dir_x - (*data).plane.plane_x;
	(*data).rpd.ray_dir_y0 = (*data).direction.dir_y - (*data).plane.plane_y;
	(*data).rpd.ray_dir_x1 = (*data).direction.dir_x + (*data).plane.plane_x;
	(*data).rpd.ray_dir_y1 = (*data).direction.dir_y + (*data).plane.plane_y;
}

/*
	1 (cell_x, cell_y). the cell coord is simply got from the integer 
		parts of floor_x and floor_y
	2 (tx, ty, floor_x, floor_y). get the texture coordinate from 
		the fractional part
	3 (floor_texture, ceiling_texture). choose texture and draw the pixel
	4 (color_floor). floor (converted to r,g,b)
	5 (color_ceiling). ceiling (symmetrical, at SCREEN_HEIGHT - y - 1 
		instead of y)
*/
static void	draw_floor_ceiling(t_data *d, int x, int y)
{
	(*d).floor_casting.cell_x = (int)((*d).floor_casting.floor_x);
	(*d).floor_casting.cell_y = (int)((*d).floor_casting.floor_y);
	(*d).floor_casting.tx = (int)(TEX_WIDTH * ((*d).floor_casting.floor_x - \
		(*d).floor_casting.cell_x)) & (TEX_WIDTH - 1);
	(*d).floor_casting.ty = (int)(TEX_HEIGHT * ((*d).floor_casting.floor_y - \
		(*d).floor_casting.cell_y)) & (TEX_HEIGHT - 1);
	(*d).floor_casting.floor_x += (*d).floor_casting.floor_step_x;
	(*d).floor_casting.floor_y += (*d).floor_casting.floor_step_y;
	(*d).floor_casting.floor_texture = 5;
	(*d).floor_casting.ceiling_texture = 4;
	(*d).floor_casting.color_floor = ((*d).map_info.f[0] << 16) | \
		((*d).map_info.f[1] << 8) | (*d).map_info.f[2];
	my_mlx_pixel_put(&(*d), x, y, (*d).floor_casting.color_floor);
	(*d).floor_casting.color_ceiling = ((*d).map_info.c[0] << 16) | \
		((*d).map_info.c[1] << 8) | (*d).map_info.c[2];
	my_mlx_pixel_put(&(*d), x, SCREEN_HEIGHT - y - 1, \
		(*d).floor_casting.color_ceiling);
}

/*

	The code iterates over each row of the screen (from top to bottom) 
	and calculates the distance from the camera to the floor for that 
	row using the formula: rowDistance = pos_z / p, where pos_z is the 
	vertical position of the camera and p is the distance from the center 
	of the screen to the current row (measured in pixels).

	To calculate the real-world position of each pixel in the row, 
	the code first calculates the step size in the x and y directions 
	(floor_step_x and floor_step_y)

	Then, the code calculates the starting position of the 
	first pixel in the row (floor_x and floor_y)

	For each pixel in the row, the code calculates the integer coordinates 
	of the cell containing the pixel (cell_x and cell_y), 
	and the texture coordinates within that cell (tx and ty).

  1 (p). Current y position compared to the center of the screen (the horizon).
  2 (pos_z). Vertical position of the camera.
  3 (row_distance). Horizontal distance from the camera to 
  	the floor for the current row.
	  0.5 is the z position exactly in the middle between floor and ceiling.
  4 (floor_step_x, floor_step_y). calculate the real world step vector 
  	we have to add for each x (parallel to camera plane)
	  adding step by step avoids multiplications with a weight in the inner loop
  5 (floor_x, floor_y).  real world coordinates of the leftmost column. 
  	This will be updated as we step to the right.
*/
void	floor_and_ceiling(t_data *d)
{
	int	x;
	int	y;

	y = 0;
	while (y < (*d).win_size.win_h)
	{
		raydir_for_leftmost_rightmost_ray(d);
		(*d).floor_casting.p = y - SCREEN_HEIGHT / 2;
		(*d).floor_casting.pos_z = 0.5 * SCREEN_HEIGHT;
		(*d).floor_casting.row_distance = (*d).floor_casting.pos_z / \
			(*d).floor_casting.p;
		(*d).floor_casting.floor_step_x = (*d).floor_casting.row_distance * \
			((*d).rpd.ray_dir_x1 - (*d).rpd.ray_dir_x0) / SCREEN_WIDTH;
		(*d).floor_casting.floor_step_y = (*d).floor_casting.row_distance * \
			((*d).rpd.ray_dir_y1 - (*d).rpd.ray_dir_y0) / SCREEN_WIDTH;
		(*d).floor_casting.floor_x = (*d).player.pos_x + \
			(*d).floor_casting.row_distance * (*d).rpd.ray_dir_x0;
		(*d).floor_casting.floor_y = (*d).player.pos_y + \
			(*d).floor_casting.row_distance * (*d).rpd.ray_dir_y0;
		x = 0;
		while (++x < SCREEN_WIDTH)
			draw_floor_ceiling(d, x, y);
		y++;
	}
}
