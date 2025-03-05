/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   backrooms.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: utiberto <utiberto@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/03 14:29:05 by utiberto          #+#    #+#             */
/*   Updated: 2025/03/05 17:44:44 by utiberto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BACKROOMS_H
# define BACKROOMS_H

# include "libft/libft.h"
# include <X11/X.h>
# include <X11/keysym.h>
# include <fcntl.h>
# include <mlx/mlx.h>
# include <stdio.h>
# include <stdlib.h>

/* Bonus */
# ifndef BONUS
#  define BONUS 0
# endif

typedef struct s_map
{
	char		*file[4096];
	char		*map[2048];
	char		orientation;
	int			end_index;
	int			start_index;
}				t_map;

typedef struct s_texture
{
	char		*path;
	char		*orientation;
	int			index;
}				t_texture;

typedef struct s_data
{
	void		*mlx;
	void		*mlx_window;
	t_map		map;
	t_texture	textures[4];
}				t_data;

extern t_data	g_data;

/* Defined error */
# define BADARG1 "too few arguments: use ./cub3D <path_to_map>"
# define BADARG2 "too many arguments: use ./cub3D <path_to_map>"
# define NOCUB "map must be a .cub file"
# define NOXPM "textures must be .xpm files"
# define BADREAD "couldn't read the map"
# define BADTEXTURE "couldn't read texture"
# define MISSINGTEXTURE "texture missing"
# define DOUBLETEXTURES "too many textures for an orientation"
# define BADFILE "file has too many lines"
# define BADFILECHAR "file contains bad characters"
# define MAPNOTEND "map is not at the end of file"
# define BADMAP "map is too big"
# define BADCHAR "map contains unvalid characters"
# define BADWALLS "map must be surrounded by walls"

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

/* Map infos */
# define MAX_ROW 4095

/* Cleanup */
void			cleanup(void);
void			clean_textures_path(void);
// int				on_destroy(void);

/* Error */
void			handle_error(char *err);
void			handle_file_error(char *err, int fd);
void			handle_textures_error(char *err);
void			handle_gnl_error(char *err, char *line, int fd);
void			handle_fd_error(char *err, int fd);

/* Parsing */
void			check_args(int ac, char **av);
void			check_map(char *map);
void			check_textures(void);
void			initialize_textures_paths(void);
void			check_file_chars(void);

#endif