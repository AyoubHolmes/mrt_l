#include "miniRT.h"

t_vector rotX(t_vector toRot, double theta)
{
	t_vector vec;

 	theta = theta * M_PI / 180.0;
	vec.y = toRot.y * cos(theta) - toRot.z * sin(theta);
	vec.z = toRot.y * sin(theta) + toRot.z * cos(theta);
	vec.x= toRot.x;
	return (vec);
}

t_vector rotY(t_vector toRot, double theta)
{
	t_vector vec;

	theta = theta * M_PI / 180.0;
	vec.z = toRot.z * cos(theta) - toRot.x * sin(theta);
	vec.x = toRot.z * sin(theta) + toRot.x * cos(theta);
	vec.y = toRot.y;
	return (vec);
}

t_vector rotZ(t_vector toRot, double theta)
{
	t_vector vec;

	theta = theta * M_PI / 180.0;
	vec.x = toRot.x * cos(theta) - toRot.y * sin(theta);
	vec.y = toRot.x * sin(theta) + toRot.y * cos(theta);
	vec.z = vec.z;
	return (vec);
}

t_vector rotatevect(t_vector toRot, t_vector rotVec)
{
	toRot = rotX(toRot, rotVec.x);
	toRot = rotY(toRot, rotVec.y);
	toRot = rotZ(toRot, rotVec.z);
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