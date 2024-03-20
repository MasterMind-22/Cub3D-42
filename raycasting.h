/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: momihamm <momihamm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/06 17:36:19 by momihamm          #+#    #+#             */
/*   Updated: 2024/03/20 03:03:46 by momihamm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RAYCASTING_H
# define RAYCASTING_H

# include "cub3d.h"
# include <stdbool.h>
# include <mlx.h>

# define RAYS_WINDOW_WIDTH 1440
# define WINDOW_HEIGHT 860
# define GRID_SIZE 64

typedef struct image
{
	void	*mlx_img;
	char	*data_addr;
	int		intperpixl;
	int		lenofline;
	int		end;
	int		x;
	int		y;
	double	win_w;
	double	win_h;
}	t_img;

typedef struct casting
{
	double	first_hit_x;
	double	first_hit_y;
	bool	is_up;
	bool	is_down;
	bool	is_left;
	bool	is_right;
	double	hor_massafa;
	double	vir_massafa;
	double	horzwall_hit_x;
	double	horzwall_hit_y;
	double	vir_wall_hit_x;
	double	vir_wall_hit_y;
	double	next_h_x;
	double	next_h_y;
	double	next_vir_x;
	double	next_vir_y;
	double	x_found_wall;
	double	y_found_wall;
	double	massafa;
	double	ray_ang;
	double	wall_length;
	bool	virt;
	bool	horz;
}	t_cast;

typedef struct player
{
	int		turn_d;
	int		walk_d;
	int		left_walk;
	int		right_walk;
	int		num_of_rays;
	double	fake_angle;
	double	x_play;
	double	x_pixels;
	double	y_pixels;
	double	y_play;
	double	rot_ang;
	double	move_speed;
	double	rotation_speed;
	double	new_x;
	double	new_y;
	double	vars_of_rays;
	double	f_o_v;
	double	pixel_per_colum;
	double	tile;
	double	x_move;
	double	y_move;
	double	finalya_h_wall;
	double	finalya_v_wall;
}	t_play;

typedef struct dda
{
	double	x_zero;
	double	y_zero;
	double	dx;
	double	dy;
	double	steps;
	double	x_incre;
	double	y_incre;
	double	flo_x;
	double	flo_y;
}	t_dda;

typedef struct ray
{
	void			*start;
	void			*window;
	char			**game_map;
	int				colur;
	int				the_long_line;
	int				the_rows;
	// int				rad;
	int				ceiling;
	int				f_flor;
	int				id;
	double			window_width;
	double			window_height;
	double			dest_por_wall;
	t_img    		*north_texture;
    t_img    		*south_texture;
    t_img    		*west_texture;
    t_img    		*east_texture;
	t_img			*right_texture;
	t_cub3d			*cub3d;
	t_img			*my_image;
	t_play			*plays;
	t_dda			*algo;
	t_cast			dataray[RAYS_WINDOW_WIDTH];
}	t_ray;

/******************************** RAYCASTING **********************************/
void	the_longest_line(t_cub3d *usef, t_ray *my_struct);
void	init_player(t_ray *ready, t_cub3d *usef);
void	put_pix_img(t_img *img, int x, int y, int colur);
void	get_curnt_posi(t_play *parzival, t_cub3d *yous);
void	dda(t_ray *obj, double x1, double y1);
void	ft_draw(t_ray *object, t_play *parzival);
void	mlx_art(t_cub3d *usef, t_ray *strahl, t_play *parzival);
void	make_valus(t_play *blanka, t_ray *obj);
void	make_square(int row, int clm, t_ray *object);
void	draw_line(t_ray *obj);
void	creat_img(t_ray *obj);
void	init_cast(t_ray *amine);
void	calcul_hor_and_ver_dessetens(t_ray *obj, int id);
void	the_first_vir_hit(t_ray *obj, int id);
void	the_first_hor_hit(t_ray *obj, int id);
void	determine_ange(t_ray *jackboys, int id);
void	init_player(t_ray *ready, t_cub3d *usef);
void	init_cast(t_ray *starlight);
void	init_ptr(t_ray *parzi, int id);
void	ft_draw(t_ray *object, t_play *parzi);
void	draw_zero(t_ray *obj, t_play *parzi);
void	right(t_ray *obj);
void	left(t_ray *obj);
void	make_rege(t_ray *obj, double tol, double ard, int id);
void	ceiling_floor(t_ray *obj);
void	become_3d(t_ray *obj);
int		check_is_player(t_play *obj, char c);
int		close_the_win(void);
int		ft_move(int events, void *object);
int		ft_again(t_ray *obj);
int		ft_mover(int events, void *object);
int		is_wall(t_ray *obj, double x, double y);
int		is_ray_hit_wall(t_ray *obj, double x, double y);
int		is_ray_down(double ray_angle);
int		is_ray_up(double ray_angle);
int		is_ray_right(double ray_angle);
int		is_ray_left(double ray_angle);
int		vir_hit(t_ray *bayren, int id);
int		hor_hit(t_ray *bayren, int id);
int		check_is_player(t_play *obj, char c);
double	deg2rad(double degrees);
double	rad2deg(double radians);
/******************************************************************************/

#endif