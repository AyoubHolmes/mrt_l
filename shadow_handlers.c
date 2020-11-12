#include "miniRT.h"

int			shadow_cheker(t_vector a, t_vector b, t_vector c)
{
	double A;
	double B;


	A = length(substract(b, a));
	B = length(substract(c, a));
	return (A >= B);
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
	//addition(obj->light_n->light,multiplication(1e-4f,obj->light_n->normal));
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
			t_shadow->object_pos = line_point(r, t);
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
	double	t;

	p = t_shadow->obj;
	while (p != NULL)
	{
		if (p != t_shadow->p)
		{
			t = interShadowFuncs(t_shadow, p, lights);
			if (t >= 0 && shadow_cheker(t_shadow->newStart, t_shadow->light_pos, t_shadow->object_pos))
			{
				shadowColor = multiple(0.5, multiple((double)1 / 255, t_shadow->color_shadow));
				return (rgb_maker(color_clamping(shadowColor)));
			}
		}
		p = p->next;
	}
	return (color);
}
