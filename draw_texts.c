
#include "fdf.h"

void my_put_string(t_map *map, int x, int y)
{
	mlx_image_t *tmp_text;

	if (!(tmp_text = mlx_new_image(map->mlx, (WIDTH / 6), HEIGHT)))
			ft_free_map_and_error(map, ERR_MLX);
	char *strings[] = {"Hello, please use these keys:", "Rotation: W, A, S, D, Q, E", "Altitude: L, K ", \
	"Parallel / isometric: P", "Picture size: Mouse wheel", "Color change: 1, 2, 3", "HAVE FUN!", "SEE YA!"};
	int i = 0;
	while(i <= 7)
	{
		tmp_text = mlx_put_string(map->mlx, strings[i], x, y);

		i++;
		y += 60;
	}
	if (mlx_image_to_window(map->mlx, tmp_text, 0, 0) == -1)
			ft_free_map_and_error(map, ERR_MLX);
	mlx_delete_image(map->mlx, tmp_text);
}