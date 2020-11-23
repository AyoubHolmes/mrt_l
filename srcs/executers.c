#include "miniRT.h"

t_vector light_dif_spec(t_vector newStart, t_vector N, t_vector V, t_objects *lights, t_vector color)
{
	t_vector	diffuse;
	t_objects	*l;
	t_Light		light;
	t_vector	L;
	t_vector	R1;

	diffuse = (t_vector){0, 0, 0};
	l = lights;
	color = multiple((double)1 / 255, color);
	while (l != NULL)
	{
		light = *(t_Light*)l->content;
		L = make_unit_vector(substract(light.light_pos, newStart));
		R1 = make_unit_vector(substract(multiple(2 * scalar(N, L), N), L));
		diffuse = add(diffuse, color_diffuse(multiple((double)1 / 255, color), light.light_color, L, N, light.brightness));
		diffuse = add(diffuse, color_spec(multiple((double)1 / 255, light.light_color), R1, V, light.brightness));
		l = l->next;
	}
	return (diffuse);
}

int colorCalculator(t_ray R, double t, t_objects *lights, t_vector N)
{
	t_vector a_dif_spec[2];
	t_objects *l;
	t_vector color;
	t_vector newStart;
	t_vector V;

	a_dif_spec[0] = (t_vector){0, 0, 0};
	color = (t_vector){0, 0, 0};
	l = lights;
	a_dif_spec[0] = multiple(0.5, multiple((double)1 / 255, R.color_obj));
	newStart = line_point(R, t);
	V = make_unit_vector(multiple(-1, R.B));
	a_dif_spec[1] = light_dif_spec(newStart, N, V, lights, R.color_obj);
	color = add(a_dif_spec[0], a_dif_spec[1]);
	return (rgb_maker(color_clamping(color)));
}
