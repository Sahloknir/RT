#include "rtv1.h"
#include <math.h>

t_color	real_lerp(t_color c1, t_color c2, float factor)
{
	t_color	color;

	color.r = (int)ft_clamp(c1.r + (factor / 100) * (c2.r - c1.r), 0, 255);
	color.g = (int)ft_clamp(c1.g + (factor / 100) * (c2.g - c1.g), 0, 255);
	color.b = (int)ft_clamp(c1.b + (factor / 100) * (c2.b - c1.b), 0, 255);
	return (color);
}

int		color_diff(t_color c1, t_color c2)
{
	int		res;
	int		res2;
	int		res3;

	res = abs(c1.r - c2.r);
	res2 = abs(c1.g - c2.g);
	res3 = abs(c1.b - c2.b);
	res += res2;
	res += res3;
	return (res);
}
