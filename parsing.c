#include "cub3d.h"

int deci_to_hexa_color(int red, int green, int blue)
{
    int  rgb = (red << 16) | (green << 8) | blue;
    return (rgb);
}

// void init_struct(cub3d_s *cub3d)
// {
// }

int check_extension(char *av)
{
    int fd;
    if (ft_strcmp(".cub", av + ft_strlen(av) - 4))
        p_error("Invalid Extension");
    else
        {
            fd = open(av, O_RDONLY);
            return (fd);
        }
    return (0);
}

void check_colors(cub3d_s *cub3d, char **split)
{
    char **colors;
    int i;

    i = 0;
    colors = ft_split(split[1], ',');
    while (colors[i])
    {
        if (ft_atoi(colors[i]) > 255 || ft_atoi(colors[i]) < 0
        || i >= 3)
            p_error("Invalid Color.");
        i++;
    }
    if (!ft_strcmp(split[0], "F"))
        cub3d->floor_color = deci_to_hexa_color(
            ft_atoi(colors[0]), ft_atoi(colors[1]), ft_atoi(colors[2]));
    if (!ft_strcmp(split[0], "C"))
        cub3d->ceiling_color = deci_to_hexa_color(
            ft_atoi(colors[0]), ft_atoi(colors[1]), ft_atoi(colors[2]));
}

int check_textures(cub3d_s *cub3d, char *str, int i)
{
    char **split;

    split = ft_split(str, ' ');
    if (!ft_strcmp(split[0], "NO"))
        cub3d->north_texture = ft_strdup(split[1]);
    else if (!ft_strcmp(split[0], "EA"))
        cub3d->east_texture = ft_strdup(split[1]);
    else if (!ft_strcmp(split[0], "SO"))
        cub3d->south_texture = ft_strdup(split[1]);
    else if (!ft_strcmp(split[0], "WE"))
        cub3d->west_texture = ft_strdup(split[1]);
    else if (!ft_strcmp(split[0], "F") || !ft_strcmp(split[0], "C"))
        check_colors(cub3d, split);
    return i;
}

void read_map_elements(cub3d_s *cub3d)
{
    int i = 0;
    char *str =  get_next_line(cub3d->fd);
    while (str)
    {
        i = check_textures(cub3d, str, i);
        str = get_next_line(cub3d->fd);
    }
    printf("Ceiling color: %X\n", cub3d->ceiling_color);
    printf("Floor color: %X\n", cub3d->floor_color);
    printf("%s", cub3d->north_texture);
    printf("%s", cub3d->south_texture);
    printf("%s", cub3d->west_texture);
    printf("%s", cub3d->east_texture);
}

