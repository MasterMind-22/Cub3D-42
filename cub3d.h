/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yonadry <yonadry@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/07 18:40:09 by yonadry           #+#    #+#             */
/*   Updated: 2024/03/23 06:26:00 by yonadry          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# ifndef BUFFER_SIZE

#  define BUFFER_SIZE 20

# endif

# include <stdio.h>
# include <unistd.h>
# include <math.h>
# include <stdlib.h>
# include <string.h>
# include <fcntl.h>
# include <stdint.h>

typedef struct cub3d_t
{
	char	**map;
	int		flag;
	char	*file_name;
	char	*north_texture;
	char	*south_texture;
	char	*west_texture;
	char	*east_texture;
	int		ceiling_color;
	int		floor_color;
	size_t	map_length;
	int		count;
	int		f_c_flag;
	int		txt_flag;
}	t_cub3d;

/******************** LIBFT/GNL FUNCS ********************/

char	*ft_substr(char const *s, unsigned int start, size_t len);
int		ft_atoi(const char *str);
char	*get_next_line(int fd);
int		newline_found(char *read_line);
char	*ft_strdup(char *s1);
char	*ft_strjoin(char const *s1, char const *s2);
char	*ft_strstr(const char *str, const char *sub);
void	ft_putchar(char c);
void	ft_putstr(char *str);
size_t	ft_strlen(char *s);
void	p_error(char *error);
char	**ft_split(char *s, char c);
void	*ft_calloc(size_t count, size_t size);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
int		ft_issame(char find, char *str);
char	*ft_strtrim(char const *s1, char const *set);
void	*ft_calloc(size_t count, size_t size);
void	free_strs(char **strs, int i);
int		file_col_num(t_cub3d *cub3d);
int		count_char(char *str, char c);
char	*check_extension(char *av);
int		is_that_char(char *str);
int		deci_to_hexa_color(int red, int green, int blue);
int		save_colors(t_cub3d *cub3d, char **colors, char c);
int		check_colors(t_cub3d *cub3d, char **split);
void	check_textures_norm(t_cub3d *cub3d, char **split);
void	check_textures(t_cub3d *cub3d, char **split);
char	*fill_empty_space_in_map(t_cub3d *cub3d, char *str, char **read);
void	get_map(t_cub3d *cub3d, char **read);
void	get_map_layout(t_cub3d *cub3d, char **read);
void	more_checks(t_cub3d *cub3d);
int		check_wall(char c);
char	**read_file(t_cub3d *cub3d);
/******************** Cub3D FUNCS ********************/
char	*check_extension(char *av);
void	read_map_elements(t_cub3d *cub3d);
void	init_struct(t_cub3d *cub3d);

#endif