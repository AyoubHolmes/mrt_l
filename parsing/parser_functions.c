#include "miniRT.h"

void R_insertion(t_data *D, char **data)
{
    D->R.x = atoi(data[1]);
    D->R.y = atoi(data[2]);
    D->R.done = 1;
    D->last_obj = NULL;
}

void A_insertion(t_data *D, char **data)
{
    char **ambient_color;
    D->A.perc = strtof(data[1], NULL);
    ambient_color = ft_split(data[2], ',');
    D->A.t_ambient_color = (t_vector){ strtof(ambient_color[0], NULL)\
        , strtof(ambient_color[1], NULL), strtof(ambient_color[2], NULL) };
    D->last_obj = NULL;
}

void c_insertion(t_data *D, char **data)
{
    char **view_point;
    char **cam_normal;
    t_objects *p;

    view_point = ft_split(data[1], ',');
    cam_normal = ft_split(data[2], ',');
	if (!D->obj)
    {
		if (!(D->obj = (t_objects*)malloc(sizeof(t_objects))))
			return ;
		D->obj = cam_initializer(view_point, cam_normal, data[3]);
        D->last_obj = D->obj;
    }
    else
    {
        p = D->obj;
        while (p->next != NULL)
            p = p->next;
		if (!(p->next = (t_objects*)malloc(sizeof(t_objects))))
			return ;
		p->next = cam_initializer(view_point, cam_normal, data[3]);
        D->last_obj = p->next;

    }
}


void l_insertion(t_data *D, char **data)
{
    char		**light_pos;
    char		**light_color;
    t_objects	*p;

    light_pos = ft_split(data[1], ',');
    light_color = ft_split(data[3], ',');
    if (!D->obj)
    {
		if (!(D->obj = (t_objects*)malloc(sizeof(t_objects))))
			return ;
        if(!(D->obj->content = (t_Light*)malloc(sizeof(t_Light))))
            return ;
        D->obj = ligth_initializer(light_pos, light_color, data[2]);
        D->last_obj = D->obj;
    }
    else
    {
        p = D->obj;
        while (p->next != NULL)
            p = p->next;
		if (!(p->next = (t_objects*)malloc(sizeof(t_objects))))
			return ;
        if(!(p->next->content = (t_Light*)malloc(sizeof(t_Light))))
            return ;
        p->next = ligth_initializer(light_pos, light_color, data[2]);
        D->last_obj = p->next;

    }
}

void sp_insertion(t_data *D, char **data)
{
    char		**sphere_center;
    char		**color_sphere;
    t_objects	*p;

    sphere_center = ft_split(data[1], ',');
    color_sphere = ft_split(data[3], ',');
    if (!D->obj)
    {
        
		if (!(D->obj = (t_objects*)malloc(sizeof(t_objects))))
			return ;
        D->obj= sphere_initialize(sphere_center, color_sphere, data[2]);
        D->last_obj = D->obj;
    }
    else
    {
        p = D->obj;
        while (p->next != NULL)
            p = p->next;
		if (!(p->next = (t_objects*)malloc(sizeof(t_objects))))
			return ;
        p->next = sphere_initialize(sphere_center, color_sphere, data[2]);
        D->last_obj = p->next;

    }
}

void pl_insertion(t_data *D, char **data)
{
    char **plane_center;
	char **plane_norm;
	char **color_plane;
	t_objects *p;

	plane_center = ft_split(data[1], ',');
	plane_norm = ft_split(data[2], ',');
	color_plane = ft_split(data[3], ',');
    if (!D->obj)
    {
		if (!(D->obj = (t_objects*)malloc(sizeof(t_objects))))
			return ;
        D->obj= plane_initialize(plane_center, plane_norm, color_plane);
        D->last_obj = D->obj;
    }
    else
    {
        p = D->obj;
        while (p->next != NULL)
            p = p->next;
		if (!(p->next = (t_objects*)malloc(sizeof(t_objects))))
			return ;
        p->next= plane_initialize(plane_center, plane_norm, color_plane);
        D->last_obj = p->next;
    }
}
void sq_insertion(t_data *D, char **data)
{
    char **square_center;
	char **square_norm;
	char **color_square;
	t_objects *p;

	square_center = ft_split(data[1], ',');
	square_norm = ft_split(data[2], ',');
	color_square = ft_split(data[4], ',');
    if (!D->obj)
    {
		if (!(D->obj = (t_objects*)malloc(sizeof(t_objects))))
			return ;
        D->obj= square_initialize(square_center, square_norm, color_square, data[3]);
        D->last_obj = D->obj;
    }
    else
    {
        p = D->obj;
        while (p->next != NULL)
            p = p->next;
		if (!(p->next = (t_objects*)malloc(sizeof(t_objects))))
			return ;
        p->next= square_initialize(square_center, square_norm, color_square, data[3]);
        D->last_obj = p->next;
    }
}

void cy_insertion(t_data *D, char **data)
{
    t_cy_init cy_init;
	t_objects *p;

	cy_init.cylinder_center = ft_split(data[1], ',');
	cy_init.cylinder_norm = ft_split(data[2], ',');
    cy_init.cylinder_diametre = data[4];
    cy_init.cylinder_height = data[5];
	cy_init.color_cylinder = ft_split(data[3], ',');
    if (!D->obj)
    {
		if (!(D->obj = (t_objects*)malloc(sizeof(t_objects))))
			return ;
        D->obj= cylinder_initialize(cy_init);
        D->last_obj = D->obj;
    }
    else
    {
        p = D->obj;
        while (p->next != NULL)
            p = p->next;
		if (!(p->next = (t_objects*)malloc(sizeof(t_objects))))
			return ;
        p->next= cylinder_initialize(cy_init);
        D->last_obj = p->next;
    }
}

void tr_insertion(t_data *D, char **data)
{
    char **first_point;
	char **second_point;
	char **third_point;
    char **triangle_color;
	t_objects *p;

	first_point = ft_split(data[1], ',');
	second_point = ft_split(data[2], ',');
	third_point = ft_split(data[3], ',');
    triangle_color = ft_split(data[4], ',');
    if (!D->obj)
    {
		if (!(D->obj = (t_objects*)malloc(sizeof(t_objects))))
			return ;
        D->obj= triangle_initialize(first_point, second_point, third_point, triangle_color);
        D->last_obj = D->obj;
    }
    else
    {
        p = D->obj;
        while (p->next != NULL)
            p = p->next;
		if (!(p->next = (t_objects*)malloc(sizeof(t_objects))))
			return ;
        p->next= triangle_initialize(first_point, second_point, third_point, triangle_color);
        D->last_obj = p->next;
    }
}
