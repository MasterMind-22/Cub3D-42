/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   from_a_binary_to_a_game.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: momihamm <momihamm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/10 11:41:58 by momihamm          #+#    #+#             */
/*   Updated: 2024/03/07 22:36:15 by momihamm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "raycasting.h"

void	vir_hit(t_ray *bayren, int id);

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

void	determine_ange(t_ray *jackboys, int id)
{
	jackboys->dataray[id].ray_ang = fmod ( jackboys->dataray[id].ray_ang  , (2 * M_PI));
	if (jackboys->dataray[id].ray_ang < 0)
		jackboys->dataray[id].ray_ang = (2 * M_PI) + jackboys->dataray[id].ray_ang;
	// jackboys->plays->rot_ang = fmod ( jackboys->plays->rot_ang  , (2 * M_PI));
	// if (jackboys->plays->rot_ang < 0)
	// 	jackboys->plays->rot_ang +=  (2 * M_PI);
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
	ready->plays->pixel_per_colum = 1; 
	// ready->plays->num_of_rays = ((ready->the_long_line - 4) * 32) / ready->plays->pixel_per_colum;
	ready->plays->num_of_rays = 1400;
	// printf("|%d|\n", ready->the_long_line);
	// printf("|%d|\n", ready->plays->num_of_rays);
}

void	init_cast(t_ray *starlight)
{
	starlight->plays->tile = 32;
	starlight->plays->finalya_h_wall = 0;
	starlight->plays->finalya_v_wall = 0;
	starlight->plays->x_move = 0;
	starlight->plays->y_move = 0;
	starlight->plays->i_am_wall = 0;
	// starlight->plays->ray_ang = amine->plays->rot_ang - (amine->plays->f_o_v / 2);
	
}

void	hor_hit(t_ray *bayren, int	id)
{
	bayren->dataray[id].first_hit_y = floor (bayren->plays->y_play / bayren->plays->tile);
	bayren->dataray[id].first_hit_y *= bayren->plays->tile;
	if (bayren->dataray[id].is_down == 0)
		bayren->dataray[id].first_hit_y += bayren->plays->tile;	
	// printf("a_y:    %f\n", bayren->dataray[id].first_hit_y);
	bayren->dataray[id].first_hit_x = bayren->plays->x_play;
	bayren->dataray[id].first_hit_x += (bayren->dataray[id].first_hit_y - bayren->plays->y_play) / tan(bayren->dataray[id].ray_ang);
	// calcul moves;
	bayren->plays->y_move = bayren->plays->tile;
	if (bayren->dataray[id].is_up == 0)
		bayren->plays->y_move *= -1;
	bayren->plays->x_move = bayren->plays->tile / tan(bayren->dataray[id].ray_ang);
	if (bayren->dataray[id].is_left == 0 && bayren->plays->x_move > 0)
		bayren->plays->x_move *= -1;
	if (bayren->dataray[id].is_right == 0 && bayren->plays->x_move < 0)
		bayren->plays->x_move *= -1;
	// now hit the wall;
	bayren->dataray[id].next_h_x = bayren->dataray[id].first_hit_x;
	bayren->dataray[id].next_h_y = bayren->dataray[id].first_hit_y;
	// now check is the X and Y of my pixel is wall or not;
	// if (bayren->dataray[id].is_up == 0)
	// 	bayren->dataray[id].next_h_y--;
	if (bayren->dataray[id].is_up == 0)
		bayren->dataray[id].next_h_y--;
	// printf ("X %f\t Y %f\t NX %f\t NY %f\n",bayren->dataray[id].next_h_x, bayren->dataray[id].next_h_y, bayren->dataray[id].horzwall_hit_x, bayren->dataray[id].horzwall_hit_y);
	// while (bayren->plays->finalya_h_wall == 0)
	while (bayren->dataray[id].next_h_x >= 0 && bayren->dataray[id].next_h_x <= (bayren->the_long_line * 32) && bayren->dataray[id].next_h_y >= 0 && bayren->dataray[id].next_h_y <= (bayren->the_rows * 32))
	{
		// if (bayren->dataray[id].is_up == 0)
		// 	bayren->dataray[id].next_h_y--;
		// if (bayren->dataray[id].next_h_x >(bayren->the_long_line * 32))
		// 	bayren->dataray[id].next_h_x = (bayren->the_long_line * 32);
		// if (bayren->dataray[id].next_h_x < 0)
		// 	bayren->dataray[id].next_h_x =0;
		// if (bayren->dataray[id].next_h_y > (bayren->the_rows * 32))
		// 	bayren->dataray[id].next_h_y = (bayren->the_rows * 32);
		// if (bayren->dataray[id].next_h_y < 0)
		// 	bayren->dataray[id].next_h_y = 0;
		if (is_ray_hit_wall (bayren, bayren->dataray[id].next_h_x, bayren->dataray[id].next_h_y) == -1)
		{
			bayren->plays->finalya_h_wall = 1;
			bayren->dataray[id].horzwall_hit_x = bayren->dataray[id].next_h_x;
			bayren->dataray[id].horzwall_hit_y = bayren->dataray[id].next_h_y;
			// bayren->colur = 0xFF0000;
			// dda(bayren, bayren->dataray[id].horzwall_hit_x, bayren->dataray[id].horzwall_hit_y);
			break;
		}
		else
		{
			bayren->dataray[id].next_h_x += bayren->plays->x_move;
			bayren->dataray[id].next_h_y += bayren->plays->y_move;
		}

	}
}

void	checker_of_directoins(t_ray *kmi, int id)
{
	
	if (kmi->dataray[id].ray_ang > 0 && kmi->dataray[id].ray_ang < M_PI)
	{
		// printf ("down\n");
		kmi->dataray[id].is_down = 0;
		kmi->dataray[id].is_up = 1;
	}
	else
	{
		// printf ("up\n");
		kmi->dataray[id].is_down = 1;
		kmi->dataray[id].is_up = 0;
	}
	if (kmi->dataray[id].ray_ang < (0.5 * M_PI) || kmi->dataray[id].ray_ang > (1.5 * M_PI))
	{
		// printf ("right\n");
		kmi->dataray[id].is_right = 0;
		kmi->dataray[id].is_left = 1;
	}
	else
	{
		// printf ("left\n"); 
		kmi->dataray[id].is_right = 1;
		kmi->dataray[id].is_left = 0;
	}
	
}

void	vir_hit(t_ray *bayren, int id)
{
	// determine_ange (bayren);
	bayren->dataray[id].first_hit_x = floor (bayren->plays->x_play / bayren->plays->tile) * bayren->plays->tile;
	if (bayren->dataray[id].is_right == 0)
		bayren->dataray[id].first_hit_x += bayren->plays->tile;
	bayren->dataray[id].first_hit_y = bayren->plays->y_play + (bayren->dataray[id].first_hit_x - bayren->plays->x_play) * tan(bayren->dataray[id].ray_ang);
	// calculate the increment xstep and ystep;
	bayren->plays->x_move = bayren->plays->tile;
	if (bayren->dataray[id].is_left == 0)
		bayren->plays->x_move *= -1;
		
	bayren->plays->y_move = bayren->plays->tile * tan(bayren->dataray[id].ray_ang);
	if (bayren->dataray[id].is_up == 0 && bayren->plays->y_move > 0)
		bayren->plays->y_move *= -1;
	if (bayren->dataray[id].is_down == 0 && bayren->plays->y_move < 0)
		bayren->plays->y_move *= -1;

	bayren->dataray[id].next_vir_x = bayren->dataray[id].first_hit_x;
	bayren->dataray[id].next_vir_y = bayren->dataray[id].first_hit_y;
	
	if (bayren->dataray[id].is_left == 0)
		bayren->dataray[id].next_vir_x--;

	while (bayren->dataray[id].next_vir_x >= 0 && bayren->dataray[id].next_vir_x <= (bayren->the_long_line * 32) && bayren->dataray[id].next_vir_y >= 0 && bayren->dataray[id].next_vir_y <= (bayren->the_rows * 32))
	{
		// if (bayren->dataray[id].is_left == 0)
		// 	bayren->dataray[id].next_vir_x--;
		if (is_ray_hit_wall (bayren , bayren->dataray[id].next_vir_x, bayren->dataray[id].next_vir_y) == -1)
		{
			// printf ("$$$$$$$$$$$$$$$$$$$$$\n");
			bayren->plays->finalya_v_wall = 1;
			bayren->dataray[id].vir_wall_hit_x = bayren->dataray[id].next_vir_x;
			bayren->dataray[id].vir_wall_hit_y = bayren->dataray[id].next_vir_y;
			// bayren->colur = 0x00CCCC;
			// dda(bayren, bayren->dataray[id].vir_wall_hit_x, bayren->dataray[id].vir_wall_hit_y);
			break;
		}
		else
		{
			bayren->dataray[id].next_vir_x += bayren->plays->x_move;
			bayren->dataray[id].next_vir_y += bayren->plays->y_move;
		}
		// zyada
		// if (bayren->dataray[id].next_h_x >= 0 && bayren->dataray[id].next_h_x <= (bayren->the_long_line * 32) && bayren->dataray[id].next_h_y >= 0 && bayren->dataray[id].next_h_y <= (bayren->the_rows * 32))
		// 	bayren->plays->i = -1;
		
		// else
		// {
		// 	printf ("kmi\n");
		// 	// hor_hit(bayren, ptr);
		// 	printf ("wow\n");
		// 	// printf ("mada \tX %f \tY %f\n", bayren->dataray[id].next_h_x, bayren->dataray[id].next_h_y);
		// }
		// done
	}
}

void	init_ptr (t_ray *parzi, int id)
{
	// printf ("%p\n", parzi);
	parzi->dataray[id].next_h_x = 0;
	// printf ("zr3z\n");÷
	parzi->dataray[id].next_h_y = 0;
	parzi->dataray[id].first_hit_x = 0;
	parzi->dataray[id].first_hit_y = 0;
	parzi->dataray[id].vir_wall_hit_x = 0;
	parzi->dataray[id].vir_wall_hit_y = 0;
	parzi->dataray[id].horzwall_hit_x = 0;
	parzi->dataray[id].horzwall_hit_y = 0;
	parzi->dataray[id].hor_massafa = 0;
	parzi->dataray[id].vir_massafa = 0;
	parzi->dataray[id].next_vir_x = 0;
	parzi->dataray[id].next_vir_y = 0;
	// bayren->dataray[id].x_found_wall = 0;
	// ptr->y_found_wall = 0;
	parzi->dataray[id].massafa = 0;
}

// function distanceBetweenPoints(x1, y1, x2, y2) {
//     return Math.sqrt((x2 - x1) * (x2 - x1) + (y2 - y1) * (y2 - y1));
// }

// distanceBetweenPoints(player.x, player.y, horzWallHitX, horzWallHitY)

void	calcul_hor_and_ver_dessetens(t_ray *obj, int id)
{
	obj->dataray[id].hor_massafa = (double)sqrt(((obj->dataray[id].horzwall_hit_x - obj->plays->x_play) * (obj->dataray[id].horzwall_hit_x - obj->plays->x_play)) + ((obj->dataray[id].horzwall_hit_y - obj->plays->y_play) * (obj->dataray[id].horzwall_hit_y - obj->plays->y_play)));
	obj->dataray[id].vir_massafa = (double)sqrt(((obj->dataray[id].vir_wall_hit_x - obj->plays->x_play) * (obj->dataray[id].vir_wall_hit_x - obj->plays->x_play)) + ((obj->dataray[id].vir_wall_hit_y - obj->plays->y_play) * (obj->dataray[id].vir_wall_hit_y - obj->plays->y_play)));
}

void	chose_vert_or_horz(t_ray *obj, int id)
{
	// if (obj->plays->finalya_h_wall == 1 && obj->plays->finalya_v_wall == 1)
	// {
		// printf ("vir  %f \t hor %f \n",obj->plays->finalya_v_wall,  obj->plays->finalya_h_wall);
		calcul_hor_and_ver_dessetens (obj, id);
	// if (obj->plays->i_am_wall == 0 && obj->dataray[id].vir_wall_hit_x == 0 && obj->dataray[id].vir_wall_hit_y == 0)
	// 	printf ("lferda\n");
	// if (obj->plays->i_am_wall == 0 && obj->dataray[id].horzwall_hit_x == 0 && obj->dataray[id].horzwall_hit_y == 0)
	// 	printf ("Qatar\n");
	// printf ("hor %f \t vir %f \n", collection->hor_massafa , collection->vir_massafa);
		// if (collection->hor_massafa == 0)
		// {
			
		// }
		if (obj->dataray[id].hor_massafa > obj->dataray[id].vir_massafa)
		{
			obj->dataray[id].x_found_wall = obj->dataray[id].vir_wall_hit_x;
			obj->dataray[id].y_found_wall = obj->dataray[id].vir_wall_hit_y;
			obj->dataray[id].massafa = obj->dataray[id].vir_massafa;
			// printf ("V\n");
			// printf ("*********************************\n");
			if (obj->plays->i_am_wall == 0 && obj->dataray[id].vir_wall_hit_x == 0 && obj->dataray[id].vir_wall_hit_y == 0)
			{
				printf ("kmi\n");
				obj->dataray[id].x_found_wall = obj->dataray[id].horzwall_hit_x;
			obj->dataray[id].y_found_wall = obj->dataray[id].horzwall_hit_y;
			obj->dataray[id].massafa = obj->dataray[id].hor_massafa;
			}
			obj->colur = 0xFF00FF;
			dda(obj, obj->dataray[id].x_found_wall, obj->dataray[id].y_found_wall);
		}
		else
		{
			obj->dataray[id].x_found_wall = obj->dataray[id].horzwall_hit_x;
			obj->dataray[id].y_found_wall = obj->dataray[id].horzwall_hit_y;
			obj->dataray[id].massafa = obj->dataray[id].hor_massafa;
			// printf ("H\n");
			// printf ("###################################\n");
			if (obj->plays->i_am_wall == 0 && obj->dataray[id].horzwall_hit_x == 0 && obj->dataray[id].horzwall_hit_y == 0)
			{
				printf ("Qatar\n");
				obj->dataray[id].x_found_wall = obj->dataray[id].vir_wall_hit_x;
				obj->dataray[id].y_found_wall = obj->dataray[id].vir_wall_hit_y;
				obj->dataray[id].massafa = obj->dataray[id].vir_massafa;
			}
			obj->colur = 0xCC6600;
			dda(obj, obj->dataray[id].x_found_wall, obj->dataray[id].y_found_wall);
		}
		// if (collection->x_found_wall == 0 || collection->y_found_wall == 0)
		// {
		// 	printf ("kmi\t H %f\t V%f\t", collection->hor_massafa, collection->vir_massafa);
		// 	if (collection->hor_massafa > collection->vir_massafa)
		// 		printf ("V\n");
		// 	else
		// 		printf ("H\n");
		// }
		// if (collection->hor_massafa > collection->vir_massafa)
		// {
		// 	collection->y_found_wall = collection->vir_wall_hit_y;
		// }
		// else
		// 	collection->y_found_wall = collection->horzwall_hit_y;
		// if (collection->hor_massafa > collection->vir_massafa)
		// 	collection->massafa = collection->vir_massafa;
		// else
		// 	collection->massafa = collection->hor_massafa;
		// obj->colur = 0xFFFF00;
		// dda(obj, collection->x_found_wall, collection->y_found_wall);
	// }
	// else
	// 	printf ("wa l3naba\n");
	
}

void	cast_an_ray(t_ray *bayren, int id)
{
	(void) bayren;
	init_ptr (bayren, id);
	// printf ("moudrib\n");
	// determine_ange (bayren, id); 
	checker_of_directoins (bayren, id);
	// // horizonlat hit;
	// // printf ("befor X %f\t Y %f\n", ptr->horzwall_hit_x, ptr->horzwall_hit_y);
	hor_hit(bayren, id);
	// // virtical hit;
	vir_hit(bayren, id);
	// // // massafa of points
	chose_vert_or_horz (bayren, id);
}

void	casting(t_ray *parzi)
{
	int	id;
	// t_cast	*ptr;

	init_cast (parzi);
	// ptr = parzi->dataray;
	// ptr = (t_cast *) malloc (sizeof (t_cast) * 1);
	// if (!ptr)
	// 	return ;
	id = 0;
	parzi->dataray[id].ray_ang = parzi->plays->rot_ang - (parzi->plays->f_o_v / 2);
	// determine_ange (parzi, id);
	// printf ("bra %f\n", parzi->dataray[id].ray_ang);
	// while (id < 1)


	// printf ("\t%f\n", parzi->plays->ray_ang);
	// determine_ange (parzi, id);
	// printf ("%f\n", parzi->plays->ray_ang);
	while (id < parzi->plays->num_of_rays)
	{
		parzi->colur = 0xFFFFFF;
		if (id <= 1 || id == (parzi->plays->num_of_rays - 1))
		{
			dda (parzi, ((parzi->plays->x_play) + 16) + cos(parzi->dataray[id].ray_ang) * 600, ((parzi->plays->y_play) + 16) + sin(parzi->dataray[id].ray_ang) * 600);
			// if (id == 0)
			// 	printf ("dda %f\n", parzi->dataray[id].ray_ang);
		}
		determine_ange (parzi, id);
		cast_an_ray (parzi, id);
		// if (id == 0)
		// 	exit (0);
		// parzi->plays->ray_ang += parzi->plays->f_o_v / parzi->plays->num_of_rays;
		// determine_ange (parzi);
		id++;
		parzi->dataray[id].ray_ang = parzi->dataray[id - 1].ray_ang;
		parzi->dataray[id].ray_ang += parzi->plays->f_o_v / parzi->plays->num_of_rays;
		// ptr++;
		// printf ("id %d\n", id);
	}
}

int	ft_again(t_ray *obj)
{
	int		row;
	int		clm;

	// printf (" %f \n",obj->plays->ray_ang);
	row = 0;
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
	obj->colur = 0x00FF1A;
	draw_line (obj);
	casting(obj);
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
