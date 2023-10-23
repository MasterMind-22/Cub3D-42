#include "cub3d.h"

int main(int ac, char **av)
{
    cub3d_s *cub3d;
    if (ac == 2)
    {
        cub3d = malloc(sizeof(cub3d_s));
        // init_struct(cub3d);
        cub3d->fd = check_extension(av[1]);
        read_map_elements(cub3d);
    }
    else
		ft_putstr("Error\nPlease input a valid argument");
}