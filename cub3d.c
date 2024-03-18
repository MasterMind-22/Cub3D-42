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

void	mlx_art(t_cub3d *usef, t_ray *strahl, t_play *parzival)
{
	strahl->start = mlx_init ();
	the_longest_line (usef, strahl);
	init_player (strahl, usef);
	get_curnt_posi (parzival, usef);
	strahl->window = mlx_new_window (strahl->start, RAYS_WINDOW_WIDTH,
			WINDOW_HEIGHT, "CUB 3D");
	strahl->my_image->mlx_img = mlx_new_image (strahl->start,
			RAYS_WINDOW_WIDTH, WINDOW_HEIGHT);
	strahl->my_image->data_addr = mlx_get_data_addr (strahl->my_image->mlx_img,
			&strahl->my_image->intperpixl, &strahl->my_image->lenofline,
			&strahl->my_image->end);
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
		strahl->cub3d = cub3d;
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
