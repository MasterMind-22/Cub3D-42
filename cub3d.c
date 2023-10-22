#include "cub3d.h"

int main(int ac, char **av)
{
    if (ac == 2)
    {
        check_extension(av[1]);
    }
    else
		ft_putstr("Error\nPlease input a valid argument");
}