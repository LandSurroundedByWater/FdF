
#ifndef FDF_H
# define FDF_H

# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <fcntl.h>
# include <sys/wait.h>
# include <sys/types.h>
# include <errno.h>
# include <string.h>
# include <limits.h>
# include <math.h>
# include "MLX42/include/MLX42/MLX42.h"
# include "libft/libft.h"
# include "libft/get_next_line.h"
# include <time.h>

# define WIDTH 1280
# define HEIGHT 720

# define CLR_DISCO          0x9A1F6AFF
# define CLR_BRICK_RED      0xC2294EFF
# define CLR_FLAMINGO       0xEC4B27FF
# define CLR_JAFFA          0xEF8633FF
# define CLR_SAFFRON        0xF3AF3DFF
# define BG_COLOR 			0x050203FF
# define SB_COLOR 			0x152238FF

# define ERR_INFILE "Invalid map"
# define ERR_ARG "Invalid amount of arguments"
# define ERR_MALLOC "Malloc error"
# define ERR_SPLIT "Invalid map"
# define ERR_MLX "MLX error"


typedef struct s_error
{
	 int line_lenght;
}	t_error;

typedef struct s_line
{
	int start_x;
	int start_y;
	int end_x;
	int end_y;
	int dy;
	int dx;
	int p;
	int swapped;
	int32_t	col;
	int col_theme;
} t_line;

typedef struct s_point
{
	int			x;
	int 		y;
	int			z;
	int32_t		col;
	int32_t		col2;
	int			col_theme;
}	t_point;

typedef struct s_proj
{
	double alpha;
	double beta;
	double gamma;
	double alphasave;
	double betasave;
	double gammasave;
	bool is_iso;
} t_proj;


typedef struct s_map {
	mlx_t *mlx;
	mlx_image_t *image;
	double z_factor;
    int rows;
    int cols;
	double size_factor;
	t_error error;
    t_point **points;
	t_point *start;
	t_point *end;
	int origox;
	int origoy;
	int startx;
	int starty;
	int offset_x;
	int offset_y;
	int pic_height;
	int pic_width;
	int pic_size_related;
	t_proj projection;
	int highest_z;
} t_map;

//Map parsing
void	allocate_map(t_map *map);
void	init_map(int fd, t_map *map, char **argv);
void	count_columns_and_rows(int fd, t_map *map, char **argv);
void	fill_map(int fd, t_map *map, char **argv);
void	init_points(t_point *p1, t_point orig1, t_point *p2, t_point orig2);
t_point *init_point(t_point *current, t_point orig);

//Map drawing
void	draw(t_map *map, mlx_image_t* image);
void	draw_map(t_map *map);
void	set_offset(t_map *map);

//texts drawing
void my_put_string(t_map *map, int x, int y);

//rotate and center
t_point correct_point_offset(t_point *point, t_map *map);
t_point rotate(t_point point, t_map *map);
t_point	rotate_x(t_point point, double angle);
t_point rotate_y(t_point point, double angle);
t_point rotate_z(t_point point, double angle);

//utils
int		ft_atoi_hex(char *str);
void	draw_pixel(mlx_image_t* image, int x, int y, int32_t col);
char	**ft_split_fdf(char const *s, char c);

//hooks
void	my_scrollhook(double xdelta, double ydelta, void *param);
void	my_ownkeyhook(void *param);



//free and error
void	ft_free_double_and_error(char **arr, char *error);
void	ft_free_single_and_error(char *arr, char *error);
void	ft_free_map(t_map *map);
void	ft_error(char *error);
void	ft_free_map_and_error(t_map *map, char *error);
void	ft_free_double_array(char **array);
void ft_free_double_array_content(char **array);

//extras
void	print_map(t_map *map);

#endif