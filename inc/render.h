#ifndef RENDER_H
# define RENDER_H

# include <mlx.h>
// more for key hooks then
# include <X11/keysym.h>

typedef struct s_img_data
{
	void	*image;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}				t_img_data;

int	create_base_window(void);

#endif
