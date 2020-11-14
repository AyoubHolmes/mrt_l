#ifndef t_ray_H
#define t_ray_H
#include "vector.h"

typedef struct s_ray
{
    t_vector A;
    t_vector B;
    double  distance;
    int     id;
    t_vector color_obj;

}t_ray;

t_ray initialize_t_ray(t_vector A, t_vector B);
t_vector t_ray_origine(t_ray R);
t_vector t_ray_direction(t_ray R);
t_vector line_point(t_ray R, double t);


#endif