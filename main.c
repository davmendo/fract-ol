#include "fractol.h"

int	main(int argc, char **argv)
{
	t_data	data;

	if (parse_args(argc, argv, &data) < 0)
		return (1);
	data.mlx_ptr = mlx_init();
	if (!data.mlx_ptr)
		return (1);
	data.win_ptr = mlx_new_window(data.mlx_ptr, WIN_WIDTH,
			WIN_HEIGHT, "fract-ol");
	data.img_ptr = mlx_new_image(data.mlx_ptr, WIN_WIDTH, WIN_HEIGHT);
	data.img_addr = mlx_get_data_addr(data.img_ptr,
			&data.bpp, &data.line_len, &data.endian);
	draw_fractal(&data);
	mlx_put_image_to_window(data.mlx_ptr, data.win_ptr, data.img_ptr, 0, 0);
	mlx_hook(data.win_ptr, 17, 0, close_hook, &data);
	mlx_hook(data.win_ptr, 12, 0, expose_hook, &data);
	mlx_key_hook(data.win_ptr, key_hook, &data);
	mlx_mouse_hook(data.win_ptr, mouse_hook, &data);
	mlx_loop(data.mlx_ptr);
	return (0);
}

void	print_usage(void)
{
	ft_printf("Usage:\n");
	ft_printf("  fractol mandelbrot\n");
	ft_printf("  fractol julia <real_part> <imag_part>\n");
	exit(0);
}
