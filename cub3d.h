/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yonadry <yonadry@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/07 18:40:09 by yonadry           #+#    #+#             */
/*   Updated: 2024/01/07 18:40:26 by yonadry          ###   ########.fr       */
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
    char    **map;
    int     flag;
    char    *file_name;
    char    *north_texture;
    char    *south_texture;
    char    *west_texture;
    char    *east_texture;
    int     ceiling_color;
    int     floor_color;
    size_t  map_length;
    int     count;
} t_cub3d;


/******************** LIBFT/GNL FUNCS ********************/

char	*ft_substr(char const *s, unsigned int start, size_t len);
int     ft_atoi(const char *str);
char	*get_next_line(int fd);
int		newline_found(char *read_line);
char	*ft_strdup(char *s1);
char	*ft_strjoin(char const *s1, char const *s2);
char	*ft_strstr(const char *str, const char *sub);
void    ft_putchar(char c);
void    ft_putstr(char *str);
size_t  ft_strlen(char *s);
void    p_error(char *error);
char    **ft_split(char *s, char c);
void	*ft_calloc(size_t count, size_t size);
int     ft_strncmp(const char *s1, const char *s2, size_t n);
int     ft_issame(char find, char *str);
char	*ft_strtrim(char const *s1, char const *set);
void	*ft_calloc(size_t count, size_t size);
void	free_strs(char **strs, int i);

/******************** Cub3D FUNCS ********************/

char    *check_extension(char *av);
void    read_map_elements(t_cub3d *cub3d);
void    init_struct(t_cub3d *cub3d);

#endif