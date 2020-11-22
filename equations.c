#include "miniRT.h"

double equationSphere(t_ray R, t_objects *obj, double *distance)
{
	t_Sphere	*sp = ((t_Sphere*)obj->content);
	t_vector oc = substract(R.A, sp->sphere_center);
	double a = scalar(R.B, R.B);
	double b = 2.0 * scalar(oc, R.B);
	double c = scalar(oc, oc) - ((double)(sp->sphere_diametre / 2) * (double)(sp->sphere_diametre / 2));
	double dis = (b * b) - 4 * a * c;
	double t;

	oc = substract(R.A, sp->sphere_center);
	a = scalar(R.B, R.B);
	if (dis < 0)
	{
		return -1.0;
	}
	else
	{
		t = (-b - sqrt(dis) ) / (2.0*a);
		if (t <= *distance && t >= 0)
		{
			if (R.id == 0)
				*distance = t;
			return (t);
		}
		return (-1);
	}
}

double equationPlane(t_ray R, t_objects *obj,double *distance)
{
	t_Plane *pl = ((t_Plane*)obj->content);
	t_vector oc = substract(R.A, pl->plane_center);
	pl->plane_norm = make_unit_vector(pl->plane_norm);
	double x = scalar(R.B, pl->plane_norm);
	double y = scalar(oc, pl->plane_norm);
	double t;
	if (x != 0)
	{
		t = -y / x;
		if (t <= *distance && t >= 0)
		{
			if (R.id == 0)
				*distance = t;
			return (t);
		}
	}
	return -1;
}

double equationSquare(t_ray R, t_objects *obj,double *distance)
{
	t_Square *sq = ((t_Square*)obj->content);
	t_vector oc = substract(R.A, sq->square_center);
	sq->square_norm = make_unit_vector(sq->square_norm);
	double x = scalar(R.B, (sq->square_norm));
	double y = scalar(oc, (sq->square_norm));
	double t;
	double	u_distance;
    double	v_distance;
	t_vector u;
	t_vector v;
	if (x != 0)
	{
		t = -y / x;
		oc = substract(line_point(R, t), sq->square_center);
		u = (v_product((t_vector){0, 1, 0}, make_unit_vector(sq->square_norm)));
		v = (v_product(make_unit_vector(sq->square_norm), u));
		u_distance = (double)(scalar(oc, u) / (double)(sq->size / 2));
		v_distance = (double)(scalar(oc, v) / (double)(sq->size / 2));	
		if (fabs(u_distance) <= 1 && fabs(v_distance) <= 1 && t <= *distance && t >= 0)
		{
			if (R.id == 0)
				*distance = t;
			return (t);
		}
	}
	return -1;
}

t_passage_cy equationCylinder(t_ray R, t_objects *obj,double *distance)
{
	t_Cylinder *cy;
	t_vector oc;
	double a;
	double b;
	double c;
	double des;
	double t1;
	double t2;
	double m1;
	double m2;
	t_passage_cy pass;

	pass.t = -1;
	cy = ((t_Cylinder*)obj->content);
	cy->cylinder_norm = make_unit_vector(cy->cylinder_norm);
	oc = substract(R.A, cy->cylinder_center);
	a = scalar(R.B, R.B) - (double)(scalar(R.B, cy->cylinder_norm) \
		* scalar(R.B, cy->cylinder_norm));
	b = 2 * (scalar(R.B, oc) - (scalar(R.B, cy->cylinder_norm) \
		* scalar(oc, cy->cylinder_norm)));
	c = scalar(oc, oc) - (scalar(oc, cy->cylinder_norm) * scalar(oc, cy->cylinder_norm)) \
		- ((double)(cy->cylinder_diametre / 2) * (double)(cy->cylinder_diametre / 2));
	des = (b * b) - 4 * (a * c);
	if (des > 0)
	{
		t1 = (-b - sqrt(des)) / (2 * a);
		t2 = (-b + sqrt(des)) / (2 * a); 
		m1 = scalar(R.B, cy->cylinder_norm) * t1 + scalar(oc, cy->cylinder_norm);
		m2 = scalar(R.B, cy->cylinder_norm) * t2 + scalar(oc, cy->cylinder_norm);
		if (m1 >= (double)(-1 * cy->cylinder_height / 2) && m1 \
			<= (double)(cy->cylinder_height / 2))
			m2 = m1;
		if(t1 < t2)
			t2 = t1;
		if (t2 != 0)
		{
			if (m2 >= (double)(-1 * cy->cylinder_height / 2) && m2 <= (double)(cy->cylinder_height / 2))
			{
				if (t2 <= *distance && t2 >= 0)
				{
					pass.t = t2;
					if (R.id == 0)
						*distance = t2;
					pass.N = substract(substract(line_point(R, t1), cy->cylinder_center), \
							multiple(m2, cy->cylinder_norm));
					pass.N = make_unit_vector(pass.N);
				}
			}
		}
	}
	return pass;
}

double equationTriangle(t_ray R, t_objects *obj,double *distance)
{
	double EPSILON = 0.0000001;
	t_Triangle	*tr;
	t_vector	edge1;
	t_vector	edge2;
	t_vector	h;
	t_vector	s;
	t_vector	q;
	double		a;
	double		f;
	double		u;
	double		v;
	double		t;

	tr = ((t_Triangle*)obj->content);
	edge1 = substract(tr->second_point, tr->first_point);
	edge2 = substract(tr->third_point, tr->first_point);
	h = v_product(R.B, edge2);
	a = scalar(edge1, h);
	if (a > -EPSILON && a < EPSILON)
		return -1;
	f = (double)(1.0 / a);
	s = substract(R.A, tr->first_point);
	u = f * scalar(s, h);
	if (u < 0.0 || u > 1.0)
		return -1;
	q = v_product(s, edge1);
	v = f * scalar(R.B, q);
	if (v < 0.0 || u + v > 1.0)
        return -1;
	t = f * scalar(edge2, q);
	if (t <= *distance && t > EPSILON)
	{
		if (R.id == 0)
				*distance = t;
		return t;
	}
	return -1;
}
