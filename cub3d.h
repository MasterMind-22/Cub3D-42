#ifndef CUB3D_H
#define CUB3D_H

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
    int     fd;
    char    *north_texture;
    char    *south_texture;
    char    *west_texture;
    char    *east_texture;
    int     ceiling_color;
    int     floor_color;

}cub3d_s;


int	ft_atoi(const char *str);
char	*get_next_line(int fd);
int		newline_found(char *read_line);
char	*ft_strdup(char *s1);
char	*ft_strjoin(char const *s1, char const *s2);
char	*ft_strstr(const char *str, const char *sub);
int     ft_strcmp(const char *s1, const char *s2);  
void    ft_putchar(char c);
void    ft_putstr(char *str);
size_t  ft_strlen(char *s);
void    p_error(char *error);
char    **ft_split(char *s, char c);
void	*ft_calloc(size_t count, size_t size);
int     ft_strcmp(const char *s1, const char *s2);
int     check_extension(char *av);
void    read_map_elements(cub3d_s *cub3d);
void    init_struct(cub3d_s *cub3d);

#endif