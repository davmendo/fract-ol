#include "fractol.h"

/*
** Converte string para double (sem usar strtod). 
** Apenas suportamos sinais e parte decimal.
*/
double	ft_atof(const char *s)
{
	double	res;
	double	sign;
	double	frac;
	double	div;

	res = 0.0;
	sign = 1.0;
	if (*s == '-' || *s == '+')
	{
		if (*s == '-')
			sign = -1.0;
		s++;
	}
	while (*s >= '0' && *s <= '9')
		res = res * 10.0 + (*s++ - '0');
	if (*s == '.')
	{
		s++;
		frac = 0.0;
		div = 1.0;
		while (*s >= '0' && *s <= '9')
		{
			frac = frac * 10.0 + (*s++ - '0');
			div *= 10.0;
		}
		res += frac / div;
	}
	return (res * sign);
}

/*
** Preenche t_data com valores default de zoom e deslocamento.
*/
static void	init_data(t_data *data)
{
	data->zoom = 200.0;
	data->offset_x = WIN_WIDTH / 2.0;
	data->offset_y = WIN_HEIGHT / 2.0;
}

int	parse_args(int argc, char **argv, t_data *data)
{
	init_data(data);
	if (argc < 2)
		print_usage();
	if (ft_strncmp(argv[1], "mandelbrot", 11) == 0)
		data->type = FRACT_MANDELBROT;
	else if (ft_strncmp(argv[1], "julia", 6) == 0)
	{
		if (argc != 4)
			print_usage();
		data->type = FRACT_JULIA;
		data->julia_c.re = ft_atof(argv[2]);
		data->julia_c.im = ft_atof(argv[3]);
	}
	else
		print_usage();
	return (0);
}
