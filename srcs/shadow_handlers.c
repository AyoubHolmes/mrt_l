#include "miniRT.h"

int			shadow_checker(t_p_shadow *t_shadow)
{
	t_vector V1;
	t_vector V2;
	double A;
	double B;

	V1 = substract(t_shadow->newStart, t_shadow->pos_hit);
	V2 = substract(t_shadow->light_pos, t_shadow->newStart);
	A = scalar(V1, V2);
	if (A >= 0)
		return (0);
	return (1);
	//return (A >= B);
}

t_vector approCorrector(t_vector v)
{
	return (add(v, (t_vector){1e-4f,1e-4f,1e-4f}));
}

double		interShadowFuncs(t_p_shadow  *t_shadow, t_objects *p, t_objects *lights)
{
	double t;
	t_objects *l;
	t_ray r;

	t = -1;
	t_shadow->newStart = add(t_shadow->newStart, multiple(1e-4f, t_shadow->object_dir));
	r.A = approCorrector(t_shadow->newStart);
	l = lights;
	while (l != NULL)
	{
		t_shadow->light_pos = (*(t_Light*)l->content).light_pos;
		r.B = make_unit_vector(approCorrector(\
			substract(t_shadow->light_pos, t_shadow->newStart)));
		if (p->id == 4)
			t = equationSphere(r, p, &t_shadow->d_shadow);
		else if (p->id == 5)
			t = equationPlane(r, p, &t_shadow->d_shadow);
		else if (p->id == 6)
			t = equationSquare(r, p, &t_shadow->d_shadow);
		else if (p->id == 7)
			t = equationCylinder(r, p, &t_shadow->d_shadow).t;
		else if (p->id == 8)
			t = equationTriangle(r, p,&t_shadow->d_shadow);
		if (t > 0)
		{
			t_shadow->pos_hit = line_point(r, t);
			return (t);
		}
		l = l->next;
	}
	return (-1);
}

int shadowHandler(t_p_shadow *t_shadow, t_objects *lights, int color)
{
	t_vector shadowColor;
	t_objects *p;
	int colorInit;
	double	t;
	int i;

	// t_shadow->d_shadow = INT_MAX;
	p = t_shadow->obj;
	i = 0;
	colorInit = color;
	while (p != NULL)
	{
		if (p != t_shadow->p)
		{
			t = interShadowFuncs(t_shadow, p, lights);
			if (t >= 0 && shadow_checker(t_shadow))
			{
				shadowColor = multiple(0.5, multiple((double)1 / 255, t_shadow->color_shadow));
				color = (rgb_maker(color_clamping(shadowColor)));
			}
		}
		p = p->next;
	}
	return (color);
}