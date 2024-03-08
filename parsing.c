/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: momihamm <momihamm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/07 18:26:34 by yonadry           #+#    #+#             */
/*   Updated: 2024/02/11 01:49:50 by momihamm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// #include "cub3d.h"
#include "raycasting.h"

int is_that_char(char *str)
{
    int i;

    i = 0;
    while (str[i])
    {
        if (str[i] != '1' && str[i] != '0' && str[i] != ' ' && str[i] != 'E' && str[i] != 'W' && str[i] != 'N' && str[i] != 'S' && str[i] != '+')
            return (1);
        i++;
    }
    return (0);
}
int deci_to_hexa_color(int red, int green, int blue)
{
    int rgb = (red << 16) | (green << 8) | blue;
    return (rgb);
}

char *check_extension(char *av)
{
    int fd;

    fd = open(av, O_RDONLY);
    if (ft_strncmp(".cub", av + (ft_strlen(av) - 4), 4) || fd == -1)
    {
        close(fd);
        p_error("Invalid Extension");
    }
    close(fd);
    return (av);
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
int save_colors(t_cub3d *cub3d, char **colors, char c)
{
    int i;
    int j;

    i = -1;
    while (colors[++i])
    {
        j = -1;
        while (colors[i][++j])
        {
            if (colors[i][j] < '0' || colors[i][j] > '9')
                return (1);
        }
        if (ft_atoi(colors[i]) < 0 || ft_atoi(colors[i]) > 255)
            return (1);
    }
    if (c == 'C')
        cub3d->ceiling_color = deci_to_hexa_color(
            ft_atoi(colors[0]), ft_atoi(colors[1]), ft_atoi(colors[2]));
    if (c == 'F')
        cub3d->floor_color = deci_to_hexa_color(
            ft_atoi(colors[0]), ft_atoi(colors[1]), ft_atoi(colors[2]));
    free_strs(colors, 0);
    return (0);
}

int check_colors(t_cub3d *cub3d, char **split)
{
    int i;
    int start;
    int c;
    char **colors;

    i = 0;
    c = 0;
    colors = malloc(sizeof(char *) * 4);
    while (i < (int) ft_strlen(split[1]))
    {
        if (split[1][i] != 32)
        {
            start = i;
            while ((split[1][i] && split[1][i] != ',') || (split[1][i] && !split[1][i + 1]))
                i++;
            // if (i < (int) ft_strlen(split[1]) &&  ((split[1][i] && split[1][i] == ',') || !split[1][i + 1]))
                colors[c++] = ft_substr(split[1], start, i - start);
        }
        i++;
    }
    colors[c] = NULL;
    if (c != 3 || save_colors(cub3d, colors, split[0][0]))
        return (free_strs(colors, 0), 1);
    return (0);
}

void check_textures(t_cub3d *cub3d, char **split)
{
    if (split[2])
        p_error("Invalid Resources");
    if ((!ft_strncmp(split[0], "NO", 2) && cub3d->north_texture) || (!ft_strncmp(split[0], "SO", 2) && cub3d->south_texture) || (!ft_strncmp(split[0], "WE", 2) && cub3d->west_texture) || (!ft_strncmp(split[0], "EA", 2) && cub3d->east_texture) || (!ft_strncmp(split[0], "F", 1) && cub3d->floor_color >= 0) || (!ft_strncmp(split[0], "C", 1) && cub3d->ceiling_color >= 0))
        p_error("Duplicated Resources");
    else if (!ft_strncmp(split[0], "NO", 2))
        cub3d->north_texture = ft_strdup(split[1]);
    else if (!ft_strncmp(split[0], "EA", 2))
        cub3d->east_texture = ft_strdup(split[1]);
    else if (!ft_strncmp(split[0], "SO", 2))
        cub3d->south_texture = ft_strdup(split[1]);
    else if (!ft_strncmp(split[0], "WE", 2))
        cub3d->west_texture = ft_strdup(split[1]);
    else if (!ft_strncmp(split[0], "F", 1) || !ft_strncmp(split[0], "C", 1))
    {
        if (count_char(split[1], ',') > 2 || check_colors(cub3d, split))
            p_error("Invalid color");
    }
}
char *fill_empty_space_in_map(t_cub3d *cub3d, char *str, char **read)
{
    size_t i;
    size_t longest;
    char *result;

    i = -1;
    longest = 0;
    while (++i < cub3d->map_length)
    {
        if (ft_strlen(read[i]) > longest)
            longest = ft_strlen(read[i]);
    }
    result = malloc(sizeof(char) * (longest + 1));
    if (!result)
        return (NULL);
    i = -1;
    while (str[++i])
    {
        if (str[i] == ' ')
            result[i] = '+';
        else
            result[i] = str[i];
    }
    while (i < longest)
        result[i++] = '+';
    result[i] = '\0';
    return (result);
}

void get_map(t_cub3d *cub3d, char **read)
{
    int i;
    char *tmp;

    i = 0;
    while (read[i])
        i++;
    cub3d->map_length = i;
    cub3d->map = malloc(sizeof(char *) * (i + 2));
    i = 0;
    while (read[i])
    {
        tmp = ft_strtrim(read[i], "\n");
        cub3d->map[i] = fill_empty_space_in_map(cub3d, tmp, read);
        free(tmp);
        if (!ft_strlen(cub3d->map[i]) || (count_char(read[i], '\n') && !read[i + 1]) || is_that_char(cub3d->map[i]))
            p_error("Invalid map");
        i++;
    }
    cub3d->map[i] = NULL;
}

void get_map_layout(t_cub3d *cub3d, char **read)
{
    char *str;
    char **split;
    int i;

    i = 0;
    while (read[i])
    {
        str = ft_strtrim(read[i], "\n ");
        split = ft_split(str, ' ');
        free(str);
        if (split[0] && split[1])
            check_textures(cub3d, split);
        if ((count_char(read[i], '1') || count_char(read[i], '0')) && (count_char(split[0], '1') || count_char(split[0], '0')))
        {
            free_strs(split, 0);
            get_map(cub3d, &read[i]);
            return;
        }
        free_strs(split, 0);
        i++;
    }
}

int file_col_num(t_cub3d *cub3d)
{
    int count;
    char *str;

    count = 1;
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

char **read_file(t_cub3d *cub3d)
{
    char **file_content;
    char *str;
    int i;
    int fd;

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
void more_checks(t_cub3d *cub3d)
{
    size_t i;

    i = -1;
    while (++i < cub3d->map_length)
    {
        cub3d->count += count_char(cub3d->map[i], 'E');
        cub3d->count += count_char(cub3d->map[i], 'W');
        cub3d->count += count_char(cub3d->map[i], 'N');
        cub3d->count += count_char(cub3d->map[i], 'S');
    }
    if (cub3d->ceiling_color == -1 || cub3d->floor_color == -1)
        p_error("Invalid color");
}

int check_wall(char c)
{
    if (c == '1' || c == 'N' || c == '0' || c == 'E' || c == 'W' || c == 'S')
        return (1);
    return (0);
}

void parse_map(t_cub3d *cub3d)
{
    size_t i;
    size_t j;

    i = 0;
    more_checks(cub3d);
    while (i < cub3d->map_length)
    {
        j = 0;
        while (j < ft_strlen(cub3d->map[i]))
        {
            if (cub3d->map[i][j] == '0' || cub3d->map[i][j] == 'N'
                || cub3d->map[i][j] == 'S'
                || cub3d->map[i][j] == 'E' || cub3d->map[i][j] == 'W')
            {
                if (i == 0 || i == cub3d->map_length - 1
                    || !check_wall(cub3d->map[i][j + 1]) || !check_wall(cub3d->map[i][j - 1])
                    || !check_wall(cub3d->map[i + 1][j]) || !check_wall(cub3d->map[i - 1][j])
                    || cub3d->count != 1)
                    p_error("Invalid map");
            }
            j++;
        }
        i++;
    }
}

void is_txt_avail(t_cub3d *cub3d)
{
    if (open(cub3d->west_texture, O_RDONLY) == -1 || open(cub3d->north_texture, O_RDONLY) == -1 || open(cub3d->east_texture, O_RDONLY) == -1 || open(cub3d->south_texture, O_RDONLY) == -1)
        p_error("Invalid Resources");
}
void fun()
{
    system("leaks cub3D");
}
void read_map_elements(t_cub3d *cub3d)
{
    int i = 0;
    char **read;

    // atexit(fun);
    cub3d->count = 0;
    cub3d->east_texture = NULL;
    cub3d->west_texture = NULL;
    cub3d->south_texture = NULL;
    cub3d->north_texture = NULL;
    cub3d->ceiling_color = -1;
    cub3d->floor_color = -1;
    read = read_file(cub3d);
    get_map_layout(cub3d, read);
    free_strs(read, 0);
    parse_map(cub3d);
    is_txt_avail(cub3d);
    printf("%d\n\n", cub3d->count);
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
}
