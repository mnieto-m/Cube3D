#include "../Include/cube.h"

int	parsing(t_data *data, char *map)
{
    int		fd;
    char	*line;
    char	**lines;
    int		i;

    fd = open(map, O_RDONLY);
    if (fd < 0)
        print_error("No se pudo abrir el archivo");

    // Cuenta líneas para malloc
    i = 0;
    while ((line = get_next_line(fd)))
    {
        free(line);
        i++;
    }
    close(fd);

    lines = malloc(sizeof(char *) * (i + 1));
    if (!lines)
        print_error("Malloc error");

    fd = open(map, O_RDONLY);
    if (fd < 0)
        print_error("No se pudo abrir el archivo");

    i = 0;
    while ((line = get_next_line(fd)))
    {
        lines[i++] = line;
    }
    lines[i] = NULL;
    close(fd);

    // Llama al parsing de texturas
    parsing_textures(data, lines);

    // Libera las líneas si ya no las necesitas
    i = 0;
    while (lines[i])
        free(lines[i++]);
    free(lines);

    return (1);
}