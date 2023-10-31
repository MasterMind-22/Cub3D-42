#include "cub3d.h"

int deci_to_hexa_color(int red, int green, int blue)
{
    int  rgb = (red << 16) | (green << 8) | blue;
    return (rgb);
}

char  *check_extension(char *av)
{
    int fd;
    if (ft_strcmp(".cub", av + ft_strlen(av) - 4))
        p_error("Invalid Extension");
    else
        return (av);
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

int count_char(char *str, char c)
{
    int i;
    int count;

    i = 0;
    count = 0;
    while (str[i])
    {
        if (str[i] == c)
            count++;
        i++;
    }
    return (count);
}

void check_textures(cub3d_s *cub3d, char *str)
{
    char **split;

    split = ft_split(str, ' ');
    if (!ft_strcmp(split[0], "NO"))
        cub3d->north_texture = ft_substr(split[1], 0, ft_strlen(split[1]) - 1);
    else if (!ft_strcmp(split[0], "EA"))
        cub3d->east_texture = ft_substr(split[1], 0, ft_strlen(split[1]) - 1);
    else if (!ft_strcmp(split[0], "SO"))
        cub3d->south_texture = ft_substr(split[1], 0, ft_strlen(split[1]) - 1);
    else if (!ft_strcmp(split[0], "WE"))
        cub3d->west_texture = ft_substr(split[1], 0, ft_strlen(split[1]) - 1);
    else if (!ft_strcmp(split[0], "F") || !ft_strcmp(split[0], "C"))
        check_colors(cub3d, split);
}

void get_map(cub3d_s *cub3d, char **read)
{
    int i;

    i = 0;
    while (read[i])
        i++;
    cub3d->map = malloc(sizeof(char *) * (i + 1));
    i = 0;
    while (read[i])
    {
        if (count_char(read[i], '\n'))
            cub3d->map[i] = ft_substr(read[i], 0, ft_strlen(read[i]) - 1);
        else
            cub3d->map[i] = ft_substr(read[i], 0, ft_strlen(read[i]));
        i++;
    }
    cub3d->map[i] = NULL;
}

int get_map_layout(cub3d_s *cub3d, char **read)
{
    char    **split;
    int     i;

    i = 0;
    while (read[i])
    {
        // if (ft_strcmp(read[i], "\n"))
            check_textures(cub3d, read[i]);
        // if (!ft_strcmp(read[i], "\n") || )
        // {
        //     while (read[i] && !ft_strcmp(read[i], "\n"))
        //         i++;
            // i++;
            split = ft_split(read[i], ' ');
            if ((count_char(read[i], '1') || count_char(read[i], '0'))
                && (count_char(split[0], '1') || count_char(split[0], '0')))
                {
                get_map(cub3d, &read[i]);
                return 0;
                }
        // }
            else
                i++;
    }
}

int  file_col_num(cub3d_s *cub3d)
{
    int count;
    char *str;

    count = 0;
    int fd = open(cub3d->file_name, O_RDONLY);
    str = get_next_line(fd);
    while (str)
    {
        count++;
        free(str);
        str = get_next_line(fd);
    }
    close(fd);
    return (count);
}

char **read_file(cub3d_s *cub3d)
{
    char    **file_content;
    char    *str;
    int     i;
    int     fd;

    i = 0;
    fd = open(cub3d->file_name, O_RDONLY);
    file_content = malloc(file_col_num(cub3d) * sizeof(char *));
    str = get_next_line(fd);
    while (str)
    {
        file_content[i] = ft_strdup(str);
        i++;
        free(str);
        str = get_next_line(fd);
    }
    file_content[i] = NULL;
    close(fd);
    return (file_content);
}

void read_map_elements(cub3d_s *cub3d)
{
    int i = 0;
    char **read;

    read = read_file(cub3d);
    get_map_layout(cub3d, read);
    while (cub3d->map[i])
    {
        printf("%s\n", cub3d->map[i]);
        i++;
    }
    printf("\n\n\n");
    printf("Ceiling color: %X\n", cub3d->ceiling_color);
    printf("Floor color: %X\n", cub3d->floor_color);
    printf("NO : %s\n", cub3d->north_texture);
    printf("SO : %s\n", cub3d->south_texture);
    printf("WE : %s\n", cub3d->west_texture);
    printf("EA : %s\n", cub3d->east_texture);
    // if (open(cub3d->north_texture, O_RDONLY) == -1)
    //     printf("File not found!\n");
    // else
    //     printf("File found!\n");
}

