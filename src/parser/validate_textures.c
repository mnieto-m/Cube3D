#include "../Include/cube.h"
#include <fcntl.h>
#include <sys/stat.h>

static int	is_valid_xpm_file(const char *path)
{
	int	len;

	if (!path)
		return (0);
	len = ft_strlen(path);
	if (len < 4)
		return (0);
	return (ft_strncmp(path + len - 4, ".xpm", 4) == 0);
}

int validate_textures(t_data *data)
{
    if (!data || !data->path)
        return (0);
    
    if (!data->path->no)
        print_error("TEXTURES: Missing NO texture", data);
    else if (!is_valid_xpm_file(data->path->no))
        print_error("TEXTURES: NO must be .xpm file", data);
    
    if (!data->path->so)
        print_error("TEXTURES: Missing SO texture", data);
    else if (!is_valid_xpm_file(data->path->so))
        print_error("TEXTURES: SO must be .xpm file", data);
    
    if (!data->path->we)
        print_error("TEXTURES: Missing WE texture", data);
    else if (!is_valid_xpm_file(data->path->we))
        print_error("TEXTURES: WE must be .xpm file", data);
    
    if (!data->path->ea)
        print_error("TEXTURES: Missing EA texture", data);
    else if (!is_valid_xpm_file(data->path->ea))
        print_error("TEXTURES: EA must be .xpm file", data);
    
    return (1);
}
