#include "miniRT.h"

int			inter(t_ray r, t_objects *p, double *distance, double *t, int color, t_objects *lights, t_p_shadow *t_shadow)
{
	if (p->id == 4)
		return sphereHandler(r, p, distance, t, lights, color, t_shadow);
	if (p->id == 5)
		return planeHandler(r, p, distance, t, lights, color, t_shadow);
	if (p->id == 6)
		return squareHandler(r, p, distance, t, lights, color, t_shadow);
	if (p->id == 7)
		return cylinderHandler(r, p, distance, t, lights, color, t_shadow);
	if (p->id == 8)
		return triangleHandler(r, p, distance, t, lights, color, t_shadow);
	return color;
}

int			getPixelColor(t_objects *obj, t_ray r, double *distance, double *d_shadow, t_objects *lights)
{
	int			color;
	t_vector	colorShadow;
    t_objects	*p;
	double		t;
	double		t2;
	t_p_shadow	t_shadow;

	color = 0;
	*distance = INT_MAX;
	t_shadow.d_shadow = INT_MAX;
	p = obj;
	t_shadow.obj = obj;
	t_shadow.cam_dir = r.B;
    while (p != NULL)
    {
		t_shadow.p = p;
        color = inter(r, p, distance, &t, color, lights, &t_shadow);
		p = p->next;
    }
	return (color);
}