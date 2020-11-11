#include "ray.h"

t_ray initialize_t_ray(t_vector A, t_vector B)
{
    t_ray R;
    R.A = A;
    R.B = B;
    R.distance = 1e30f;
    return (R);
}

t_vector t_ray_origine(t_ray R) { return R.A; }
t_vector t_ray_direction(t_ray R) { return R.B; }
t_vector line_point(t_ray R, double t) { return add(R.A, multiple(t, R.B));}