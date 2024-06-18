/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: f██████ <f██████@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/20 15:58:12 by y██████          #+#    #+#             */
/*   Updated: 2024/06/18 07:41:28 by f██████          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include <math.h>
# include <stdbool.h>
# include "../libft/includes/libft.h"

# ifdef __linux__
#  include "../mlx-linux/mlx.h"
#  define OS "linux"
#  define LETTER_KEY_MOVE_LEFT			97
#  define LETTER_KEY_MOVE_RIGHT			100
#  define LETTER_KEY_MOVE_FORWARD       119
#  define LETTER_KEY_MOVE_BACKWARD      115
#  define ARROW_KEY_LOOK_LEFT 			65361
#  define ARROW_KEY_LOOK_RIGHT			65363
#  define ARROW_KEY_MOVE_FORWARD		126
#  define ARROW_KEY_MOVE_BACKWARD		125
#  define KEY_ESC						65307
# elif __APPLE__
#  include "../mlx-opengl/mlx.h"
#  define OS "macos"
#  define LETTER_KEY_MOVE_LEFT        	0
#  define LETTER_KEY_MOVE_RIGHT       	2
#  define LETTER_KEY_MOVE_FORWARD 		13
#  define LETTER_KEY_MOVE_BACKWARD		1
#  define ARROW_KEY_LOOK_LEFT			123
#  define ARROW_KEY_LOOK_RIGHT			124
#  define ARROW_KEY_MOVE_FORWARD		126
#  define ARROW_KEY_MOVE_BACKWARD		125
#  define KEY_ESC						53
# endif

# define SCREEN_WIDTH 	960
# define SCREEN_HEIGHT	720
# define TEX_WIDTH 		64
# define TEX_HEIGHT 	64

typedef struct s_vector2_d
{
	int	x;
	int	y;
}	t_vector2_d;

typedef struct s_vector2_f
{
	float	x;
	float	y;
}	t_vector2_f;

typedef struct s_player
{
	double	pos_x;
	double	pos_y;
}	t_player;

typedef struct s_direction
{
	double	dir_x;
	double	dir_y;
}	t_direction;

typedef struct s_plane
{
	double	plane_x;
	double	plane_y;
}	t_plane;

typedef struct s_window_size
{
	int	win_w;
	int	win_h;
}	t_window_size;

typedef struct s_ray_pos_and_dir
{
	double	camera_x;
	double	ray_dir_x;
	double	ray_dir_y;
	float	ray_dir_x0;
	float	ray_dir_y0;
	float	ray_dir_x1;
	float	ray_dir_y1;
}	t_ray_pos_and_dir;

typedef struct s_box
{
	int	map_x;
	int	map_y;
}	t_box;

// length of ray from current position to next x or y-side
typedef struct s_player_to_grid
{
	double	player_to_grid_x;
	double	player_to_grid_y;
}	t_player_to_grid;

// length of ray from one x or y-side to next x or y-side
typedef struct s_from_side_to_next_side
{
	double	side_to_side_x;
	double	side_to_side_y;
}	t_from_side_to_next_side;

// what direction to step in x or y-direction (either +1 or -1)
typedef struct s_dir_step
{
	int	step_x;
	int	step_y;
}	t_dir_step;

typedef struct s_ray_speed
{
	double	move_speed;
	double	rot_speed;
}	t_ray_speed;

typedef struct s_floor_casting
{
	int		p;
	float	pos_z;
	float	row_distance;
	float	floor_step_x;
	float	floor_step_y;
	float	floor_x;
	float	floor_y;
	int		cell_x;
	int		cell_y;
	int		tx;
	int		ty;
	int		floor_texture;
	int		ceiling_texture;
	int		color_floor;
	int		color_ceiling;
}	t_floor_casting;

typedef struct s_texture
{
	void	*text;
	char	*text_adr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
	int		width_img;
	int		height_img;
}	t_texture;

typedef struct s_dda
{
	double	perp_w_d;
	int		hit;
	int		side;
	int		line_height;
	int		draw_start;
	int		draw_end;
	double	wall_x;
	int		tex_x;
	int		tex_y;
	double	step;
	double	tex_pos;
	int		color;
}	t_dda;

typedef struct s_map_info
{
	char	*no;
	char	*so;
	char	*we;
	char	*ea;
	int		*f;
	int		*c;
	char	**map;
	char	pos_start_orientation;
	int		pos_start_count;
}	t_map_info;

typedef struct s_parsing
{
	int		count_identifiers;
	size_t	map_max_width;
	int		map_height;
}	t_parsing;

typedef struct s_data {
	void						*img;
	char						*addr;
	int							bits_per_pixel;
	int							line_length;
	int							endian;
	t_window_size				win_size;
	void						*mlx;
	void						*mlx_win;
	t_player					player;
	t_direction					direction;
	t_plane						plane;
	t_ray_pos_and_dir			rpd;
	t_floor_casting				floor_casting;
	t_box						box;
	t_player_to_grid			ptg;
	t_from_side_to_next_side	fsns;
	t_dir_step					dir_step;
	t_ray_speed					ray_speed;
	t_texture					texture[6];
	t_dda						dda;
	t_map_info					map_info;
	t_parsing					parsing;
	int							which_tex;
	unsigned int				color;
	int							ac[2];
}	t_data;

// algorithms
void	floor_and_ceiling(t_data *data);
void	step_and_player_to_grid(t_data *data, int x);
void	dda(t_data *data, int x);

// hooks
int		update(t_data *data);

// player
void	set_up_player(t_data *data);
void	move_forward(t_data *data);
void	move_backward(t_data *data);
void	move_right(t_data *data);
void	move_left(t_data *data);
void	look_right(t_data *data);
void	look_left(t_data *data);

// mlx
void	set_up_image(t_data *data);
void	my_mlx_pixel_put(t_data *data, int x, int y, int color);
int		exit_game(t_data *data);
int		close_window(int keycode, t_data *data);

// textures
int		load_texture(t_data *data, char *texture_path, int text_num);
int		load_textures(t_data *data);

// parsing
int		parsing_main(t_data *data, char **argv);
int		is_the_map_surrounded_by_walls(t_data *data);
int		parse_map(t_data *data, char *line, int *l);
void	add_extra_top_bottom_borders(t_data *data);
void	get_map_height_max_width(t_data *data, char *map_file);
void	check_extension_cub(char *map_file);
int		malloc_data_info(t_data *data);
void	parse_floor_color(t_data *data, char *line);
void	parse_ceiling_color(t_data *data, char *line);
void	parse_texture_no(t_data *data, char *line);
void	parse_texture_so(t_data *data, char *line);
void	parse_texture_we(t_data *data, char *line);
void	parse_texture_ea(t_data *data, char *line);
void	set_action(int keycode, t_data *data);
void	unset_action(int keycode, t_data *data);
int		keydown_hook(int keycode, t_data *data);
int		keyup_hook(int keycode, t_data *data);
void	hook_key_register(t_data *data);
void	player_action(t_data *data);

#endif