/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: momihamm <momihamm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/06 17:36:19 by momihamm          #+#    #+#             */
/*   Updated: 2024/02/29 01:53:32 by momihamm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RAYCASTING_H
# define RAYCASTING_H

# include "cub3d.h"
# include <mlx.h>

typedef struct image
{
	void	*mlx_img;
	char	*data_addr;
	int		intperpixl;
	int		lenofline;
	int		end;
}	t_img;

typedef struct casting
{
	int	first_hit_x;
	int	first_hit_y;
	double	is_up;
	double	is_down;
	double	is_left;
	double	is_right;
}	t_cast;


typedef struct player
{
	int			turn_d;
	int			walk_d;
	double		x_play;
	double		x_pixels;
	double		y_pixels;
	double		y_play;
	double		rot_ang;
	double		move_speed;
	double		rotation_speed;
	double		new_x;
	double		new_y;
	int			i;
	// rays
	double		f_o_v;
	double		ray_ang;
	int			num_of_rays;
	int			pixel_per_colum;
	double		tile;
	int			wall_hit_x;
	int			wall_hit_y;
	double		massafa;
	double		xh_move;
	double		yh_move;
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
	float	flo_x;
	float	flo_y;
}	t_dda;

typedef struct ray
{
	void			*start;
	void			*window;
	char			**game_map;
	int				colur;
	int				the_long_line;
	int				the_rows;
	int				rad;
	// int				i;
	t_img			*my_image;
	t_play			*plays;
	t_dda			*algo;
	// t_cast			*demantion;
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
int		check_is_player(t_play *obj, char c);
int		close_the_win(void);
int		ft_move(int events, void *object);
int		ft_again(t_ray *obj);
int		ft_mover(int events, void *object);
int		is_wall(t_ray *obj, double x, double y);
double	deg2rad(double degrees);
double	rad2deg(double radians);




void	init_cast(t_ray *amine);
/******************************************************************************/

#endif