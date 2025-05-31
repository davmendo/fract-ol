#include "fractol.h"

int	close_hook(t_data *data)
{
	mlx_destroy_image(data->mlx_ptr, data->img_ptr);
	mlx_destroy_window(data->mlx_ptr, data->win_ptr);
	exit(0);
	return (0);
}

int	key_hook(int keycode, t_data *data)
{
	if (keycode == 65307)
		close_hook(data);
	else if (keycode == 65361)
		data->offset_x += 50;
	else if (keycode == 65363)
		data->offset_x -= 50;
	else if (keycode == 65362)
		data->offset_y += 50;
	else if (keycode == 65364)
		data->offset_y -= 50;
	else if (keycode == 'r')
	{
		data->zoom = 200.0;
		data->offset_x = WIN_WIDTH / 2.0;
		data->offset_y = WIN_HEIGHT / 2.0;
	}
	else
		return (0);
	draw_fractal(data);
	mlx_put_image_to_window(data->mlx_ptr, data->win_ptr, data->img_ptr, 0, 0);
	return (0);
}

int	mouse_hook(int button, int x, int y, t_data *data)
{
	double	mouse_re;
	double	mouse_im;

	mouse_re = (x - data->offset_x) / data->zoom;
	mouse_im = (y - data->offset_y) / data->zoom;
	if (button == 4)
		data->zoom *= 1.1;
	else if (button == 5)
		data->zoom /= 1.1;
	else
		return (0);
	data->offset_x = x - mouse_re * data->zoom;
	data->offset_y = y - mouse_im * data->zoom;
	draw_fractal(data);
	mlx_put_image_to_window(data->mlx_ptr, data->win_ptr, data->img_ptr, 0, 0);
	return (0);
}

int	expose_hook(t_data *data)
{
	draw_fractal(data);
	mlx_put_image_to_window(data->mlx_ptr, data->win_ptr, data->img_ptr, 0, 0);
	return (0);
}
