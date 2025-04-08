/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   backrooms.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khadj-me <khalilhadjmes1@gmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/03 14:29:05 by utiberto          #+#    #+#             */
/*   Updated: 2025/04/08 16:52:59 by khadj-me         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BACKROOMS_H
# define BACKROOMS_H

# include "libft/libft.h"
# include <X11/X.h>
# include <X11/keysym.h>
# include <fcntl.h>
# include <math.h>
# include <mlx/mlx.h>
# include <mlx/mlx_int.h>
# include <stdio.h>
# include <stdlib.h>

/* Bonus */
# ifndef BONUS
#  define BONUS 0
# endif

typedef int		key;

typedef struct s_player
{
	float		coor[2];
	key			w;
	key			s;
	key			a;
	key			d;
	key			l_arr;
	key			r_arr;

	float		view;
}				t_player;

typedef struct s_map
{
	char		*map[2048];
	char		orientation;
	int			end_index;
	int			start_index;
	int			size;
}				t_map;

typedef struct s_texture
{
	void		*spr;
	char		*path;
	char		*orientation;
	int			index;
	int			bpp;
	int			size_line;
	int			endian;
	int			width;
	int			height;
	char		*data;
}				t_texture;

typedef struct s_color
{
	char		*material;
	int			red;
	int			green;
	int			blue;
	int			index;
}				t_color;

typedef struct s_data
{
	void		*mlx;
	void		*mlx_window;
	void		*mlx_img;
	char		*screen;
	char		*file[4096];
	int			bits_pr_pxl;
	int			line_length;
	int			endian;
	t_player	player;
	t_map		map;
	t_texture	textures[4];
	t_color		colors[2];
}				t_data;

extern t_data	g_data;
extern int		spr_size;

/* Defined error */
# define BADARG1 "too few arguments: use ./cub3D <path_to_map>"
# define BADARG2 "too many arguments: use ./cub3D <path_to_map>"
# define NOCUB "map must be a .cub file"
# define NOXPM "textures must be .xpm files"
# define BADREAD "couldn't read the map"
# define BADTEXTURE "couldn't read texture"
# define MISSINGTEXTURE "texture missing"
# define DOUBLETEXTURES "too many textures for an orientation"
# define BADCOLOR "bad color syntax"
# define BADNUMBERCOLOR "color must be between 0 and 255"
# define MISSINGCOLOR "color missing"
# define DOUBLECOLORS "too many color for a material"
# define BADFILE "file has too many lines"
# define BADFILECHAR "file contains bad characters"
# define MAPNOTEND "map is not at the end of file"
# define BADMAP "map is too big"
# define BADCHAR "map contains unvalid characters"
# define BADWALLS "map must be surrounded by walls"
# define DOUBLEORIENTATION "too many orientation in map"
# define NOORIENTATION "no orientation was found to start"

/* Keys */
# define KEY_W 119
# define KEY_A 97
# define KEY_S 115
# define KEY_D 100
# define KEY_ESC 65307
# define KEY_CC 65507
# define ARROW_UP 65362
# define ARROW_DOWN 65364
# define ARROW_LEFT 65361
# define ARROW_RIGHT 65363

/* Player defines */
# define X 0
# define Y 1
# define PI 3.14159265359
# define PRESSED 1
# define RELEASED 0
# define SPEED 1
# define ROTATE_SPEED 0.01

/* Map infos */
# define VER_TOUCH 1
# define HOR_TOUCH 2
# define TILE_SIZE 32
# define MAX_ROW 4095
# define MAX_ROW_MAP 2046
# define NO 0
# define SO 1
# define WE 2
# define EA 3

/* Game infos */
# define WIN_WIDTH 1280
# define WIN_HEIGHT 720
# define DEBUG 0

/* Cleanup */
void			cleanup(void);
void			clean_textures_path(void);
void			clean_colors(void);
// int				on_destroy(void);

/* Error */
void			handle_error(char *err);
void			handle_file_error(char *err, int fd);
void			handle_textures_error(char *err);
void			handle_colors_error(char *err);
void			handle_map_error(char *err);

/* Parsing */
void			check_args(int ac, char **av);
void			check_file(char *map);
void			check_textures(void);
void			initialize_textures_paths(void);
void			check_colors(void);
void			initialize_colors(void);
void			check_file_chars(void);
void			check_map(void);
void			check_borders(char **map);
void			check_orientation(char **map);

/* Utils */
int				is_orientation(char c);
int				is_floor(char c);
int				is_wall(char c);
int				tblotbl_len(char **tbl);

/* Draw */
void			draw_square(int x, int y, int color, int size);
void			draw_map(void);
void			clear_screen(void);
void			draw_fov(float start_x, int i);
u_int32_t		*get_pixel(t_texture *img, int ray_x, int ray_y);

/* Inits */
void			init_textures(void);
void			init_data(int ac, char **av);

/* Inputs */
int				destroy_game(t_data *data);
int				on_keypress(int input, t_data *data);
int				on_keyrelease(int input, t_data *data);

/* Main */

void			find_spawn_coor(void);
int				wall_col(float obj_x, float obj_y, float start_x);
void			put_pixel(int x, int y, int color);
float			find_norm(float x1, float x2, float y1, float y2);
void			move_player(t_player *player);
int				game_loop(t_data *data);

#endif
