#ifndef FRACTOL_H
# define FRACTOL_H

# include <mlx.h>
# include <stdlib.h>
# include <unistd.h>
# include <math.h>
# include <pthread.h>
# include "libft/libft.h"

# define WIN_WIDTH   800
# define WIN_HEIGHT  600
# define MAX_ITER    100
# define THREAD_COUNT 4

typedef enum e_fractype
{
	FRACT_MANDELBROT,
	FRACT_JULIA
}	t_fractype;

typedef struct s_complex
{
	double	re;
	double	im;
}	t_complex;

typedef struct s_data
{
	void		*mlx_ptr;
	void		*win_ptr;
	void		*img_ptr;
	char		*img_addr;
	int			bpp;
	int			line_len;
	int			endian;
	t_fractype	type;
	t_complex	julia_c;
	double		zoom;
	double		offset_x;
	double		offset_y;
}	t_data;

typedef struct s_thread_args
{
	t_data	*data;
	int		y_start;
	int		y_end;
}	t_thread_args;

void	print_usage(void);
int		parse_args(int argc, char **argv, t_data *data);
double	ft_atof(const char *s);

void	draw_fractal(t_data *data);
int		compute_mandelbrot(double x0, double y0);
int		compute_julia(double x0, double y0, t_complex c);
int		get_color(int iter);
void	put_pixel(t_data *data, int x, int y, int color);

int		key_hook(int keycode, t_data *data);
int		mouse_hook(int button, int x, int y, t_data *data);
int		close_hook(t_data *data);
int		expose_hook(t_data *data);

#endif
