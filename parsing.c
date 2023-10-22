#include "cub3d.h"

void check_extension(char *av)
{
    if (ft_strcmp(".cub", av + ft_strlen(av) - 4))
        p_error("Invalid Extension");
}

// void check_map_elements(char *av)
// {
// }
