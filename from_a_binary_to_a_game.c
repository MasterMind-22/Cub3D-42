/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   from_a_binary_to_a_game.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: momihamm <momihamm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/10 11:41:58 by momihamm          #+#    #+#             */
/*   Updated: 2024/03/01 19:45:35 by momihamm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "raycasting.h"

int	check_is_player(t_play *obj, char c)
{
	if (c == 'N' || c == 'S' || c == 'E' || c == 'W')
	{
		if (c == 'N')
			obj->rot_ang = - M_PI / 2;
		if (c == 'S')
			obj->rot_ang = M_PI / 2;
		if (c == 'E')
			obj->rot_ang = 0;
		if (c == 'W')
			obj->rot_ang = M_PI;
		return (1);
	}
	return (0);
}

void	determine_ange(t_ray *jackboys)
{
	jackboys->plays->rot_ang = fmod ( jackboys->plays->rot_ang  ,(2 * M_PI));
	if (jackboys->plays->rot_ang < 0)
		jackboys->plays->rot_ang +=  (2 * M_PI);
}

void	init_player(t_ray *ready, t_cub3d *usef)
{
	get_curnt_posi (ready->plays, usef);
	ready->plays->turn_d = 0;
	ready->plays->walk_d = 0;
	ready->plays->rot_ang = M_PI;
	ready->plays->move_speed = 60.0;
	ready->plays->rotation_speed = 2 * (M_PI / 90);
	// raycasting vars;
	ready->plays->f_o_v = deg2rad (60.00);
	// ready->i = 0;
	ready->plays->pixel_per_colum = 30; 
	// ready->plays->num_of_rays = 1.0;
	// printf ("lline %d\n", ready->the_long_line);
	// printf ("ll32ine %d\n", ready->the_long_line * 32);
	// printf ("pixel %d\n", ready->plays->pixel_per_colum);
	// printf ("numof_rays %d\n", ready->plays->num_of_rays);
	// printf ("result %d\n", (ready->the_long_line * 32) / ready->plays->pixel_per_colum);
	// printf ("pix %d\tnumofrays %d\n", ready->plays->pixel_per_colum, ready->plays->num_of_rays);
	ready->plays->num_of_rays = (ready->the_long_line * 32) / ready->plays->pixel_per_colum;
	// printf ("zre3   %d\n", (ready->the_long_line * 32) / ready->plays->num_of_rays);
	// printf ("pix %d\tnumofrays %d\n", ready->plays->pixel_per_colum, ready->plays->num_of_rays);
	// printf ("numof rays %d\n", ready->plays->num_of_rays);
	// exit (0);
	init_cast(ready);
}

void	init_cast(t_ray *amine)
{
	amine->plays->tile = 32;
	amine->plays->wall_hit_x = 0;
	amine->plays->wall_hit_y = 0;
	amine->plays->massafa = 0;
}

void	hor_hit(t_ray *bayren, t_cast *ptr)
{
	// int	x_move;
	// int	y_move;
	// int	first_hit_x;
	// int	first_hit_y;

	// finding the coleset horizontal hit;
	ptr->first_hit_y = floor (bayren->plays->y_play / bayren->plays->tile);
	if (ptr->is_down == 0)
		ptr->first_hit_y += bayren->plays->tile;	
	// printf ("kmihb000a\n");
	ptr->first_hit_y *= bayren->plays->tile;
	ptr->first_hit_x = bayren->plays->x_play + ((bayren->plays->y_play - ptr->first_hit_y) / tan(bayren->plays->ray_ang));
	// calcul moves;
	bayren->plays->yh_move = 32;
	bayren->plays->xh_move = 32 / tan(bayren->plays->ray_ang);
	if (ptr->is_up == 0)
		bayren->plays->yh_move *= -1;
	else
		bayren->plays->yh_move *= 1;
	if (ptr->is_left == 0 && bayren->plays->xh_move > 0)
		bayren->plays->xh_move *= -1;
	else
		bayren->plays->xh_move *= 1;
	if (ptr->is_right == 0 && bayren->plays->xh_move < 0)
		bayren->plays->xh_move *= -1;
	else
		bayren->plays->xh_move *= 1;
	
}

void	checker_of_directoins(t_ray *kmi, t_cast *ptr)
{
	if (kmi->plays->ray_ang > 0 && kmi->plays->ray_ang < M_PI)
	{
		ptr->is_down = 0;
		ptr->is_up = 1;
	}
	else
	{
		ptr->is_down = 1;
		ptr->is_up = 0;
	}
	if (kmi->plays->ray_ang < (0.5 * M_PI) || kmi->plays->ray_ang > (1.5 * M_PI))
	{
		ptr->is_right = 0;
		ptr->is_left = 1;
	}
	else
	{
		ptr->is_right = 1;
		ptr->is_left = 0;
	}
}

// void	vir_hit(t_ray *bayren)
// {
	
// }

void	cast_an_ray(t_ray *bayren, t_cast *ptr)
{
	determine_ange (bayren);
	checker_of_directoins (bayren, ptr);
	// if (ptr->is_right == 0)
	// 	printf ("000000000000000000000\n");
	// else
	// 	printf ("111111111111111111111\n");
	// horizonlat hit;
	hor_hit(bayren, ptr);
	// horizonlat hit;
	// virtical hit;
	// vir_hit(bayren);
	// virtical hit;
}

void	casting(t_ray *parzi)
{
	int	id;
	t_cast	*ptr;

	ptr = (t_cast *) malloc (sizeof (t_cast) * 1);
	if (!ptr)
		return ;
	id = 0;
	if (id > (int)parzi->plays->num_of_rays)
		printf ("\nkmi\n");
	parzi->plays->ray_ang = parzi->plays->rot_ang - (parzi->plays->f_o_v / 2);
	// while (id < 1)
	while (id < parzi->plays->num_of_rays)
	{
		// printf ("casting\n");
		// take the DATA of each ray; PS==> you need to figr out how to save the DATA you will need;
		// cast each ray;
		cast_an_ray (parzi, ptr);
		parzi->colur = 0xFFFFFF;
		if (id < 1000)
			dda (parzi, ((parzi->plays->x_play) + 16) + cos(parzi->plays->ray_ang ) * 80, ((parzi->plays->y_play) + 16) + sin(parzi->plays->ray_ang )  * 80);
		parzi->plays->ray_ang += parzi->plays->f_o_v / parzi->plays->num_of_rays;
		id++;
	}
}

int	ft_again(t_ray *obj)
{
	int		row;
	int		clm;

	row = 0;
	// determine_ange (obj);
	printf ("%f\n", obj->plays->ray_ang);
	creat_img (obj);
	while (obj->game_map[row])
	{
		clm = 0;
		while (obj->game_map[row][clm])
		{
			if (obj->game_map[row][clm] == '1')
				make_square(row, clm, obj);
			else if (obj->game_map[row][clm] == '+')
				make_square (row, clm, obj);
			clm++;
		}
		row++;
	}
	// obj->colur = 0xFFFFFF;
	casting(obj);
	obj->colur = 0x00FF1A;
	draw_line (obj);
	mlx_put_image_to_window (obj->start, obj->window,
		obj->my_image->mlx_img, 0, 0);
	return (0);
}

void	draw_zero(t_ray *obj, t_play *parzi)
{
	int	row;
	int	clm;

	(void) parzi;
	row = 0;
	while (obj->game_map[row])
	{
		clm = 0;
		while (obj->game_map[row][clm])
		{
			if (check_is_player (obj->plays, obj->game_map[row][clm]) == 1)
				make_square (row, clm, obj);
			clm++;
		}
		row++;
	}
}

void	ft_draw(t_ray *object, t_play *parzi)
{
	int		row;
	int		clm;

	row = 0;
	while (object->game_map[row])
	{
		clm = 0;
		while (object->game_map[row][clm])
		{
			if (object->game_map[row][clm] == '1')
				make_square(row, clm, object);
			else if (object->game_map[row][clm] == '+')
				make_square (row, clm, object);
			clm++;
		}
		row++;
	}
	draw_zero (object, parzi);
	mlx_put_image_to_window (object->start, object->window,
		object->my_image->mlx_img, 0, 0);
}
