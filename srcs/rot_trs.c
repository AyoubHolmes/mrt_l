#include "miniRT.h"


t_vector    rot_x(t_vector vec, double teta)
{
    double tmp;
    tmp = vec.y;
	teta = teta * M_PI / 180.0;
    vec.y = (vec.y * cos(teta)) - (vec.z * sin(teta));
    vec.z = tmp * sin(teta) + (vec.z * cos(teta));
    return (vec);
}
t_vector    rot_y(t_vector vec, double teta)
{
    double tmp;
    tmp = vec.z;
	teta = teta * M_PI / 180.0;
    vec.z = (vec.z * cos(teta)) - (vec.x * sin(teta));
    vec.x = tmp * sin(teta) + (vec.x * cos(teta));
    return (vec);
}
t_vector    rot_z(t_vector vec, double teta)
{
    double tmp;
    tmp = vec.x;
	teta = teta * M_PI / 180.0;
    vec.x = (vec.x * cos(teta)) - (vec.y * sin(teta));
    vec.y = tmp * sin(teta) + (vec.y * cos(teta));
    return (vec);
}

t_vector rotatevect(t_vector toRot, t_vector rotVec)
{
	toRot = rot_x(toRot, rotVec.x);
	toRot = rot_y(toRot, rotVec.y);
	toRot = rot_z(toRot, rotVec.z);
	return (toRot);
}

void rotate(t_data *D, char **data)
{
	t_vector rotVec;
	char **values;

	values = ft_split(data[1], ',');
	rotVec = (t_vector){atof(values[0]), atof(values[1]), \
	atof(values[2])};
	if (D->last_obj->id == 2)
	{
		((t_Cam_data*)D->last_obj->content)->cam_normal = rotatevect(\
		((t_Cam_data*)D->last_obj->content)->cam_normal, rotVec);
	}
	else if (D->last_obj->id == 5)
	{
		((t_Plane*)D->last_obj->content)->plane_norm = rotatevect(\
		((t_Plane*)D->last_obj->content)->plane_norm, rotVec);
	}
	else if (D->last_obj->id == 6)
	{
		((t_Square*)D->last_obj->content)->square_norm = rotatevect(\
		((t_Square*)D->last_obj->content)->square_norm, rotVec);
	}
	else if (D->last_obj->id == 7)
	{
		((t_Cylinder*)D->last_obj->content)->cylinder_norm = rotatevect(\
		((t_Cylinder*)D->last_obj->content)->cylinder_norm, rotVec);
	}
}

t_vector transvect(t_vector toRot, t_vector rotVec)
{
	toRot.x = toRot.x + rotVec.x;
	toRot.y = toRot.y + rotVec.y;
	toRot.z = toRot.z + rotVec.z;
	return (toRot);
}

void translate(t_data *D, char **data)
{
	t_vector tVec;
	char **values;

	values = ft_split(data[1], ',');
	tVec = (t_vector){atof(values[0]), atof(values[1]), \
	atof(values[2])};
	if (D->last_obj->id == 2)
	{
		((t_Cam_data*)D->last_obj->content)->view_point = transvect(\
		((t_Cam_data*)D->last_obj->content)->view_point, tVec);
	}
	else if (D->last_obj->id == 5)
	{
		((t_Plane*)D->last_obj->content)->plane_center = transvect(\
		((t_Plane*)D->last_obj->content)->plane_center, tVec);
	}
	else if (D->last_obj->id == 6)
	{
		((t_Square*)D->last_obj->content)->square_center = transvect(\
		((t_Square*)D->last_obj->content)->square_center, tVec);
	}
	else if (D->last_obj->id == 7)
	{
		((t_Cylinder*)D->last_obj->content)->cylinder_center = transvect(\
		((t_Cylinder*)D->last_obj->content)->cylinder_center, tVec);
	}
}