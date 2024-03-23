/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yonadry <yonadry@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/07 18:26:57 by yonadry           #+#    #+#             */
/*   Updated: 2024/03/23 08:45:47 by yonadry          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "raycasting.h"

void	become_3d(t_ray *obj)
{
	int				id;
	double			corect_lenght;
	int				walltoppixel;
	int				wallbottompixel;

	id = 0;
	while (id < RAYS_WINDOW_WIDTH)
	{
		corect_lenght = obj->dataray[id].massafa
			* cos (obj->dataray[id].ray_ang - obj->plays->rot_ang);
		obj->dataray[id].wall_length = (obj->plays->tile / corect_lenght)
			* obj->dest_por_wall;
		walltoppixel = (WINDOW_HEIGHT / 2) - (obj->dataray[id].wall_length / 2);
		if (walltoppixel < 0)
			walltoppixel = 0;
		wallbottompixel = (WINDOW_HEIGHT / 2)
			+ (obj->dataray[id].wall_length / 2);
		if (wallbottompixel > WINDOW_HEIGHT)
			wallbottompixel = WINDOW_HEIGHT;
		select_texture(obj, id);
		draw_wall(obj, id, walltoppixel, wallbottompixel);
		id++;
	}
}

void	free_all(t_ray *strahl)
{
	free(strahl->cub3d->east_texture);
	free(strahl->cub3d->north_texture);
	free(strahl->cub3d->west_texture);
	free(strahl->cub3d->south_texture);
	free_strs(strahl->cub3d->map, 0);
	free(strahl->plays);
	free(strahl->my_image);
	free(strahl->algo);
	free(strahl->north_texture);
	free(strahl->west_texture);
	free(strahl->south_texture);
	free(strahl->east_texture);
	free(strahl->right_texture);
	free(strahl->cub3d);
}

void	mlx_art(t_cub3d *usef, t_ray *strahl, t_play *parzival)
{
	strahl->start = mlx_init ();
	the_longest_line (usef, strahl);
	init_player (strahl, usef);
	get_curnt_posi (parzival, usef);
	strahl->window = mlx_new_window (strahl->start, RAYS_WINDOW_WIDTH,
			WINDOW_HEIGHT, "CUB3D");
	strahl->my_image->mlx_img = mlx_new_image (strahl->start,
			RAYS_WINDOW_WIDTH, WINDOW_HEIGHT);
	strahl->my_image->data_addr = mlx_get_data_addr (strahl->my_image->mlx_img,
			&strahl->my_image->intperpixl, &strahl->my_image->lenofline,
			&strahl->my_image->end);
	open_textures(strahl);
	mlx_hook (strahl->window, 2, 0, ft_move, strahl);
	mlx_hook (strahl->window, 3, 0, ft_mover, strahl);
	mlx_hook (strahl->window, 17, 0, close_the_win, NULL);
	mlx_loop_hook(strahl->start, ft_again, strahl);
	mlx_loop (strahl->start);
}

void	call_main(t_ray *strahl, char **av)
{
	if (!strahl || !strahl->plays
		|| !strahl->my_image || !strahl->algo)
		p_error("Malloc failed\n");
	strahl->cub3d->file_name = check_extension(av[1]);
	read_map_elements(strahl->cub3d);
	strahl->game_map = strahl->cub3d->map;
	mlx_art (strahl->cub3d, strahl, strahl->plays);
	free_all(strahl);
}

int	main(int ac, char **av)
{
	t_cub3d	*cub3d;
	t_ray	*strahl;

	if (ac == 2)
	{
		cub3d = malloc(sizeof(t_cub3d));
		strahl = malloc (sizeof(t_ray));
		strahl->plays = malloc (sizeof(t_play));
		strahl->my_image = malloc (sizeof (t_img));
		strahl->cub3d = cub3d;
		strahl->algo = malloc (sizeof (t_dda));
		strahl->north_texture = malloc (sizeof (t_img));
		strahl->west_texture = malloc (sizeof (t_img));
		strahl->south_texture = malloc (sizeof (t_img));
		strahl->east_texture = malloc (sizeof (t_img));
		strahl->right_texture = malloc (sizeof (t_img));
		call_main(strahl, av);
	}
	else
		ft_putstr("Error\nPlease input a valid argument");
}
