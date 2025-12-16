#ifndef RENDER_H
# define RENDER_H

# include <mlx.h>
# include <X11/keysym.h>

// init.c
bool	render_game(t_data *game);

// hooks.c
int	key_hook(int key_code, t_data *game);
int	quit_game(t_data *game);

// clean_up.c
void	clean_up_mlx(t_data *game);

#endif
