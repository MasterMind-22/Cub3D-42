/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   imgpix.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: momihamm <momihamm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/03 17:19:57 by momihamm          #+#    #+#             */
/*   Updated: 2024/02/19 11:18:41 by momihamm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "raycasting.h"

void	put_pix_img(t_img *img, int x, int y, int colur)
{
	char	*puting;

	puting = img->data_addr + (y * img->lenofline + x * (img->intperpixl / 8));
	*(int *) puting = colur;
}
