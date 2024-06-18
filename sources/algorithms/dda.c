/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dda.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: y██████ <y██████@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/20 15:57:37 by y██████          #+#    #+#             */
/*   Updated: 2023/02/20 18:38:01 by y██████         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

/*
	A loop incrementing the ray with 1 square every time, until a wall is hit.

	1. (hit). was there a wall hit?
	2. (side). was a NS or a EW wall hit? When the ray has hit a wall, 
		the loop ends, and then we'll know whether an x-side or y-side of 
		a wall was hit in the variable "side", and what wall was hit with 
		map_x and map_y.
	3. (if player_to_grid_x else). Jump to next map square, either in x-direction, 
		or in y-direction
	4. (if map). Check if ray has hit a wall
*/
static void	was_a_wall_hit(t_data *data)
{
	(*data).dda.hit = 0;
	while ((*data).dda.hit == 0)
	{
		if ((*data).ptg.player_to_grid_x < (*data).ptg.player_to_grid_y)
		{
			(*data).ptg.player_to_grid_x += (*data).fsns.side_to_side_x;
			(*data).box.map_x += (*data).dir_step.step_x;
			(*data).dda.side = 0;
		}
		else
		{
			(*data).ptg.player_to_grid_y += (*data).fsns.side_to_side_y;
			(*data).box.map_y += (*data).dir_step.step_y;
			(*data).dda.side = 1;
		}
		if ((*data).map_info.map[(*data).box.map_x][(*data).box.map_y] == '1')
			(*data).dda.hit = 1;
	}
}

static void	which_texture(t_data *data)
{
	(*data).which_tex = 0;
	if ((*data).dda.side == 0)
	{
		if ((*data).rpd.ray_dir_x >= 0)
			(*data).which_tex = 0;
		else
			(*data).which_tex = 1;
	}
	else if ((*data).dda.side == 1)
	{
		if ((*data).rpd.ray_dir_y >= 0)
			(*data).which_tex = 2;
		else
			(*data).which_tex = 3;
	}
}

/*
	1. (step). How much to increase the texture coordinate per screen pixel
	2. (tex_pos). Starting texture coordinate
	3. (tex_y). Cast the texture coordinate to integer, and mask with 
		(TEX_HEIGHT - 1) in case of overflow
	4. // Check out of texture coordinates
		if ((*data).dda.tex_x < 0 || (*data).dda.tex_x >= \
			(*data).texture[(*data).text_orientation].width_img)
			return ; // Returning black color
*/
static void	drawing(t_data *d, int x)
{
	int	y;

	(*d).dda.step = 1.0 * TEX_HEIGHT / (*d).dda.line_height;
	(*d).dda.tex_pos = ((*d).dda.draw_start - (*d).win_size.win_h / \
		2 + (*d).dda.line_height / 2) * (*d).dda.step;
	y = (*d).dda.draw_start;
	while (y < (*d).dda.draw_end)
	{
		(*d).dda.tex_y = (int)(*d).dda.tex_pos & (TEX_HEIGHT - 1);
		(*d).dda.tex_pos += (*d).dda.step;
		if ((*d).dda.tex_x < 0 || (*d).dda.tex_x >= \
			(*d).texture[(*d).which_tex].width_img)
			return ;
		if ((*d).dda.tex_y < 0 || (*d).dda.tex_y >= \
			(*d).texture[(*d).which_tex].height_img)
			return ;
		(*d).dda.color = \
		(*(int *)((*d).texture[(*d).which_tex].text_adr + \
		((*d).dda.tex_y * (*d).texture[(*d).which_tex].line_length) + \
		((*d).dda.tex_x * (*d).texture[(*d).which_tex].bits_per_pixel / 8)));
		my_mlx_pixel_put(&(*d), x, y, (*d).dda.color);
		y++;
	}
}

/*
	perform DDA

	1. (if side == 0 else). Calculate distance projected on camera 
		direction
		The length of sideDist already almost equals perp_wall_dist. 
		We just need to subtract side_to_side once from it, 
		going one step back, because in the DDA steps above 
		we went one step further to end up inside the wall.
	2. (line_height). Calculate height of line to draw on screen.
	3. (draw_start, draw_end). Calculate lowest and highest pixel 
		to fill in current stripe
	4. (wall_x if else). The value wall_x represents the exact value where 
		the wall was hit, not just the integer coordinates of the wall.
	5. (wall_x line only). Where exactly the wall was hit
	6. (tex_x). x coordinate on the texture
*/
void	dda(t_data *d, int x)
{
	was_a_wall_hit(d);
	if (d->dda.side == 0)
		d->dda.perp_w_d = (d->ptg.player_to_grid_x - d->fsns.side_to_side_x);
	else
		d->dda.perp_w_d = (d->ptg.player_to_grid_y - d->fsns.side_to_side_y);
	d->dda.line_height = (int)(d->win_size.win_h / d->dda.perp_w_d);
	d->dda.draw_start = -d->dda.line_height / 2 + d->win_size.win_h / 2;
	if (d->dda.draw_start < 0)
		d->dda.draw_start = 0;
	d->dda.draw_end = d->dda.line_height / 2 + d->win_size.win_h / 2;
	if (d->dda.draw_end >= d->win_size.win_h)
		d->dda.draw_end = d->win_size.win_h - 1;
	which_texture(d);
	if (d->dda.side == 0)
		d->dda.wall_x = d->player.pos_y + d->dda.perp_w_d * d->rpd.ray_dir_y;
	else
		d->dda.wall_x = d->player.pos_x + d->dda.perp_w_d * d->rpd.ray_dir_x;
	d->dda.wall_x -= floor((d->dda.wall_x));
	d->dda.tex_x = (int)(d->dda.wall_x * (double)(TEX_WIDTH));
	if (d->dda.side == 0 && d->rpd.ray_dir_x > 0)
		d->dda.tex_x = TEX_WIDTH - d->dda.tex_x - 1;
	if (d->dda.side == 1 && d->rpd.ray_dir_y < 0)
		d->dda.tex_x = TEX_WIDTH - d->dda.tex_x - 1;
	drawing(d, x);
}
