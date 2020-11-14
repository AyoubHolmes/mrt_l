#include "miniRT.h"

int sphereHandler(t_ray r, t_objects *p, double *distance, double *t, t_objects *lights, int color, t_p_shadow *t_shadow)
{
	t_vector newStart;
	t_vector N;

	r.id = 0;
    *t = equationSphere(r, p, distance);
    if (*t > 0 && *t <= *distance)
    {
        t_shadow->newStart = line_point(r, *t);
        N = make_unit_vector(substract(t_shadow->newStart ,(*(t_Sphere*)p->content).sphere_center));
		t_shadow->color_shadow = (*(t_Sphere*)p->content).color_sphere;
		t_shadow->object_dir = N;
		r.color_obj = t_shadow->color_shadow;
		color = colorCalculator(r, *t, lights, N);
		r.id = 1;
		color = shadowHandler(t_shadow, lights, color);
    }
    return (color);
}

int planeHandler(t_ray r, t_objects *p, double *distance, double *t, t_objects *lights, int color, t_p_shadow *t_shadow)
{
    t_Plane pl;

	r.id = 0;
    *t = equationPlane(r, p, distance);
    if (*t > 0 && *t >= *distance)
    {
		t_shadow->newStart = line_point(r, *t);
		pl = *(t_Plane*)p->content;
		t_shadow->color_shadow = pl.color_plane;
		t_shadow->object_dir = pl.plane_norm;
    	if (scalar(r.B, pl.plane_norm) > 0)
			pl.plane_norm = multiple(-1, pl.plane_norm);
		r.color_obj = t_shadow->color_shadow;
		color = colorCalculator(r, *t, lights, pl.plane_norm);
		r.id = 1;
		color = shadowHandler(t_shadow, lights, color);
	}
	return (color);
}

int squareHandler(t_ray r, t_objects *p, double *distance, double *t, t_objects *lights, int color, t_p_shadow *t_shadow)
{
    t_Square sq;

	r.id = 0;
    *t = equationSquare(r, p, distance);
	if (*t >= 0 && *t >= *distance)
	{
		t_shadow->newStart = line_point(r, *t);
		sq = *((t_Square*)p->content);
		t_shadow->color_shadow = sq.color_square;
		t_shadow->object_dir = sq.square_norm;
		if (scalar(r.B, sq.square_norm) > 0)
			sq.square_norm = multiple(-1, sq.square_norm);
		r.color_obj = t_shadow->color_shadow;
		color = colorCalculator(r, *t, lights, sq.square_norm);
		r.id = 1;
		color = shadowHandler(t_shadow, lights, color);
	}
    return (color);
}

int cylinderHandler(t_ray r, t_objects *p, double *distance, double *t, t_objects *lights, int color, t_p_shadow *t_shadow)
{
    t_Cylinder cy;
	t_passage_cy pass;

	r.id = 0;
    pass = equationCylinder(r, p, distance);
	*t = pass.t;
	if (*t >= 0 && *t >= *distance)
	{
		t_shadow->newStart = line_point(r, *t);
		cy = *((t_Cylinder*)p->content);
		t_shadow->color_shadow = cy.cylinder_color;
		t_shadow->object_dir = cy.cylinder_norm;
		r.color_obj = t_shadow->color_shadow;
		color = colorCalculator(r, *t, lights, pass.N);
		r.id = 1;
		color = shadowHandler(t_shadow, lights, color);
	}
    return (color);
}

int triangleHandler(t_ray r, t_objects *p, double *distance, double *t, t_objects *lights, int color, t_p_shadow *t_shadow)
{
    t_Triangle tr;
	t_vector V1;
	t_vector V2;
	t_vector V;

	r.id = 0;
    *t = equationTriangle(r, p, distance);
    if (*t > 0)
    {
		t_shadow->newStart = line_point(r, *t);
		tr = *(t_Triangle*)p->content;
		t_shadow->color_shadow = tr.triangle_color;
		V1 = substract(tr.second_point, tr.first_point);
		V2 = substract(tr.third_point, tr.first_point);
		V = make_unit_vector(v_product(V1, V2));
		if (scalar(r.B, V) > 0)
			V = multiple(-1, V);
		t_shadow->object_dir = V;
		r.color_obj = t_shadow->color_shadow;
		color = colorCalculator(r, *t, lights, V);
		r.id = 1;
		color = shadowHandler(t_shadow, lights, color);
	}
	return (color);
}