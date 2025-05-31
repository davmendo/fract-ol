#include "fractol.h"

void	put_pixel(t_data *data, int x, int y, int color)
{
	char	*dst;

	if (x < 0 || x >= WIN_WIDTH || y < 0 || y >= WIN_HEIGHT)
		return ;
	dst = data->img_addr + (y * data->line_len + x * (data->bpp / 8));
	*(unsigned int *)dst = color;
}

static void	*thread_draw(void *arg)
{
	t_thread_args	*targ;
	t_data			*data;
	int				x;
	int				y;
	int				iter;
	double			xr;
	double			yi;

	targ = (t_thread_args *)arg;
	data = targ->data;
	y = targ->y_start;
	while (y < targ->y_end)
	{
		x = 0;
		while (x < WIN_WIDTH)
		{
			xr = (x - data->offset_x) / data->zoom;
			yi = (y - data->offset_y) / data->zoom;
			if (data->type == FRACT_MANDELBROT)
				iter = compute_mandelbrot(xr, yi);
			else
				iter = compute_julia(xr, yi, data->julia_c);
			put_pixel(data, x, y, get_color(iter));
			x++;
		}
		y++;
	}
	return (NULL);
}

void	draw_fractal(t_data *data)
{
	pthread_t		threads[THREAD_COUNT];
	t_thread_args	args[THREAD_COUNT];
	int				i;
	int				slice_height;

	slice_height = WIN_HEIGHT / THREAD_COUNT;
	i = 0;
	while (i < THREAD_COUNT)
	{
		args[i].data = data;
		args[i].y_start = i * slice_height;
		if (i == THREAD_COUNT - 1)
			args[i].y_end = WIN_HEIGHT;
		else
			args[i].y_end = (i + 1) * slice_height;
		pthread_create(&threads[i], NULL, thread_draw, &args[i]);
		i++;
	}
	i = 0;
	while (i < THREAD_COUNT)
	{
		pthread_join(threads[i], NULL);
		i++;
	}
}

int	compute_mandelbrot(double x0, double y0)
{
	double	x;
	double	y;
	double	xtemp;
	int		iter;

	x = 0.0;
	y = 0.0;
	iter = 0;
	while (x * x + y * y <= 4.0 && iter < MAX_ITER)
	{
		xtemp = x * x - y * y + x0;
		y = 2 * x * y + y0;
		x = xtemp;
		iter++;
	}
	return (iter);
}

int	compute_julia(double x0, double y0, t_complex c)
{
	double	x;
	double	y;
	double	xtemp;
	int		iter;

	x = x0;
	y = y0;
	iter = 0;
	while (x * x + y * y <= 4.0 && iter < MAX_ITER)
	{
		xtemp = x * x - y * y + c.re;
		y = 2 * x * y + c.im;
		x = xtemp;
		iter++;
	}
	return (iter);
}

int	get_color(int iter)
{
	int	color;

	if (iter == MAX_ITER)
		return (0x000000);
	color = ((iter * 15) % 256) << 16;
	color |= ((iter * 7) % 256) << 8;
	color |= ((iter * 3) % 256);
	return (color);
}
