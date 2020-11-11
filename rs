/* p2 = obj;
		while (p2 != NULL)
		{
			if (p2 != p)
			{
				colorShadow = interShadowUpgraded(t_shadow, p2, lights, d_shadow);
				//colorShadow = interShadow(line_point(r, t), p2, lights, color, d_shadow);
				if (colorShadow != -1)
					color = colorShadow;
			}
			p2 = p2->next;
		} */
        '
    

int			shadow_cheker(t_vector a, t_vector b, t_vector c)
{
	double A;
	double B;


	A = length(substract(b, a));
	B = length(substract(c, a));
	return (A > B);
}

t_vector approCorrector(t_vector v)
{
	return (add(v, (t_vector){1e-4f,1e-4f,1e-4f}));
}

double		interShadowFuncs(t_p_shadow  *t_shadow, t_objects *p, t_objects *lights, double *d_shadow)
{
	double t;
	t_objects *l;
	t_ray r;

	t = -1;
	r.A = approCorrector(t_shadow->newStart);
	l = lights;
	while (l != NULL)
	{
		t_shadow->light_pos = (*(t_Light*)l->content).light_pos;
		r.B = make_unit_vector(approCorrector(\
			substract(t_shadow->light_pos, t_shadow->newStart)));
		if (p->id == 4)
			t = equationSphere(r, p, d_shadow);
		else if (p->id == 5)
			t = equationPlane(r, p, d_shadow);
		else if (p->id == 6)
			t = equationSquare(r, p, d_shadow);
		else if (p->id == 7)
			t = equationCylinder(r, p, d_shadow).t;
		else if (p->id == 8)
			t = equationTriangle(r, p, d_shadow);
		if (t > 0 && t <= *d_shadow )
		{
			t_shadow->object_pos = line_point(r, t);
			return (t);
		}
		l = l->next;
	}
	return (-1);
}