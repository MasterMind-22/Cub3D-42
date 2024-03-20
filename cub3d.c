/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: momihamm <momihamm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/07 18:26:57 by yonadry           #+#    #+#             */
/*   Updated: 2024/03/16 08:29:07 by momihamm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "raycasting.h"

void	mr(void)
{
	system ("leaks cub3D");
}

void	free_all(t_cub3d *cub3d)
{
	free(cub3d->east_texture);
	free(cub3d->north_texture);
	free(cub3d->west_texture);
	free(cub3d->south_texture);
	free_strs(cub3d->map, 0);
	free(cub3d);
}
void open_textures(t_ray *strahl)
{
	strahl->north_texture->mlx_img = mlx_xpm_file_to_image(strahl->start,
			strahl->cub3d->north_texture, &strahl->north_texture->x, &strahl->north_texture->y);
	strahl->east_texture->mlx_img = mlx_xpm_file_to_image(strahl->start,
			strahl->cub3d->east_texture, &strahl->east_texture->x, &strahl->east_texture->y);
	strahl->south_texture->mlx_img = mlx_xpm_file_to_image(strahl->start,
			strahl->cub3d->south_texture, &strahl->south_texture->x, &strahl->south_texture->y);
	strahl->west_texture->mlx_img = mlx_xpm_file_to_image(strahl->start,
			strahl->cub3d->west_texture, &strahl->west_texture->x, &strahl->west_texture->y);
	if (!strahl->north_texture->mlx_img || !strahl->east_texture->mlx_img
		|| !strahl->south_texture->mlx_img || !strahl->west_texture->mlx_img)
	{
		printf("Error\n");
		exit(0);
	}
	strahl->north_texture->data_addr = mlx_get_data_addr(strahl->north_texture->mlx_img,
			&strahl->north_texture->intperpixl, &strahl->north_texture->lenofline,
			&strahl->north_texture->end);
	strahl->east_texture->data_addr = mlx_get_data_addr(strahl->east_texture->mlx_img,
			&strahl->east_texture->intperpixl, &strahl->east_texture->lenofline,
			&strahl->east_texture->end);
	strahl->south_texture->data_addr = mlx_get_data_addr(strahl->south_texture->mlx_img,
			&strahl->south_texture->intperpixl, &strahl->south_texture->lenofline,
			&strahl->south_texture->end);
	strahl->west_texture->data_addr = mlx_get_data_addr(strahl->west_texture->mlx_img,
			&strahl->west_texture->intperpixl, &strahl->west_texture->lenofline,
			&strahl->west_texture->end);
	if (!strahl->north_texture->data_addr || !strahl->east_texture->data_addr
		|| !strahl->south_texture->data_addr || !strahl->west_texture->data_addr)
	{
		printf("Error\n");
		exit(0);
	}
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
		strahl->algo = malloc (sizeof (t_dda));
		strahl->cub3d  = cub3d;
		strahl->north_texture = malloc (sizeof (t_img));
		strahl->west_texture = malloc (sizeof (t_img));
		strahl->south_texture = malloc (sizeof (t_img));
		strahl->east_texture = malloc (sizeof (t_img));
		strahl->right_texture = malloc (sizeof (t_img));
		if (!cub3d || !strahl || !strahl->plays
			|| !strahl->my_image || !strahl->algo)
		{
			printf ("bad pass!\n");
			return (0);
		}
		cub3d->file_name = check_extension(av[1]);
		read_map_elements(cub3d);
		strahl->game_map = cub3d->map;
		mlx_art (cub3d, strahl, strahl->plays);
		free_all(cub3d);
	}
	else
		ft_putstr("Error\nPlease input a valid argument");
}
