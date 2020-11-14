#ifndef MINIRT_H
# define MINIRT_H
# include <stdio.h>
# include <math.h>
# include <unistd.h>
# include <stdlib.h>
# include <fcntl.h>
# include <limits.h>
# include "camera.h"
# define BUFFER_SIZE 100

/*
**  ------------------- Structures -----------------------
*/

typedef struct	s_window
{   
    void *mlx_ptr;
    void *win_ptr;
    void *img_ptr;
    int *img_data;
    int bpp;
    int size_l;
    int img_endian;
}				t_window;
typedef struct	s_Resolution
{
	int x;
	int y;
	int done;
}				t_Resolution;

typedef struct	s_Ambient
{
	double perc;
	t_vector t_ambient_color;
	int done;
}				t_Ambient;

typedef struct	s_Cam_data
{
	t_vector	view_point;
	t_vector	cam_normal;
	double	fov;
}				t_Cam_data;
 
typedef struct			s_Light
{
	t_vector			light_pos;
	double				brightness;
	t_vector			light_color;
}						t_Light;

typedef struct			s_Sphere
{
	t_vector			sphere_center;
	double				sphere_diametre;
	t_vector			color_sphere;
}						t_Sphere;

typedef struct			s_Plane
{
	t_vector			plane_center;
	t_vector			plane_norm;
	t_vector			color_plane;
}						t_Plane;

typedef struct			s_Square
{
	t_vector			square_center;
	t_vector			square_norm;
	double				size;
	t_vector			color_square;
}						t_Square;

typedef struct			s_Cylinder
{
	t_vector			cylinder_center;
	t_vector			cylinder_norm;
	t_vector			cylinder_color;
	double				cylinder_diametre;
	double				cylinder_height;
}						t_Cylinder;

typedef struct			s_Triangle
{
	t_vector			first_point;
	t_vector			second_point;
	t_vector			third_point;
	t_vector			triangle_color;
}						t_Triangle;

typedef struct			s_objects
{
	void				*content;
	int					id;
	struct s_objects	*next;
}						t_objects;

typedef struct			s_doubleCameraList
{
	t_Cam_data					cam;
	struct s_doubleCameraList	*next;
	struct s_doubleCameraList	*prev;
}t_camlist;

typedef struct			s_data
{
	t_Resolution		R;
	t_Ambient			A;
	t_camlist			*cameras;
	t_objects			*lights;
	t_objects			*obj;
	t_objects			*last_obj;
	int					pixel;
}						t_data;

typedef struct			s_passage_cy
{
	t_vector N;
	double t;
}						t_passage_cy;

typedef struct s_p_shadow
{
	t_vector newStart;
	t_vector color_shadow;
	t_vector light_pos;
	t_vector object_pos;
	t_vector object_dir;
	double	d_shadow;
	t_objects *obj;
	t_objects *p;
}t_p_shadow;

typedef struct s_main
{
	t_data d;
	t_window w;
}t_main;

typedef struct s_err
{
	int isChecked;
	int line;
}t_err;

typedef struct s_icam
{
	t_camera cam;
	t_vector up;
	t_vector u;
	t_vector v;
	t_vector w;
	double aspect;
	double theta;
	double half_height;
	double half_width;
	t_vector v1;
	t_vector v2;

}t_icam;


/*
** ----------------------------
*/

/*
** --- LINKED LIST FUNCTIONS --
*/

t_objects	*ft_lstnew(void *content);
void		ft_lstadd_back(t_objects **alst, t_objects *new);
t_camlist	*ft_double_lst_cam_new(t_Cam_data cam);
void		fcam_add(t_camlist **alst, t_camlist *new);
t_camlist	*fcam_last(t_camlist **alst);
t_camlist	*get_cam_previous(t_camlist **alst);
t_camlist	*get_cam_next(t_camlist **alst);
t_camlist	*getcams(t_data d);
t_ray			get_t_ray(t_data d, double u, double v);
t_objects	*getLigths(t_objects *obj);
/*
** -------------------------------------------------------
*/

/*
** --------------- INITIALIZER FUNCTION ------------------
*/

t_objects *camInitializer(char **vp, char **cn, char *fov);
t_objects *ligthInitializer(char **lp, char **lc, char *brightness);
t_objects *sphereInitialize(char **sc, char **color_sphere, char *sphere_diametre);
t_Plane *planeInitialize(char **plane_center, char **plane_norm, char **color_plane);
t_Square *squareInitialize(char **square_center, char **square_norm, char **color_square, char *size);
t_Cylinder *cylinderInitialize(char **cylinder_center, char **cylinder_norm, char **color_cylinder, char *cylinder_diametre, char *cylinder_height);
t_Triangle *triangleInitialize(char **first_point, char **second_point, char **third_point, char **triangle_color);

/*
** -------------------------------------------------------
*/

/*
** --------------- DEBUGGING FUNCTION --------------------
*/

void vectorPrinter (t_vector V);
void resolutionPrinter(t_Resolution res);
void ambientPrinter (t_Ambient ab);
void cameraPrinter (t_Cam_data *cam);
void lightPrinter (t_Light *light);
void spherePrinter (t_Sphere *S);
void planePrinter (t_Plane *P);
void squarePrinter (t_Square *P);
void cylinderPrinter(t_Cylinder *cy);
void trianglePrinter(t_Triangle *tr);
void objectsDebugger(t_data d);

/*
** -------------------------------------------------------
*/

/*
** --------------- CHECKING FUNCTION ----------------------
*/

int		ft_isdigit(int c);
int		ft_isint(char *c);
int		ft_ispositiveint(char *c);
int		ft_isfloat(char *c);
int		ft_ispositivefloat(char *c);
int		ft_isintensityfloat(char *c);
int		ft_iscolorfloat(char *c);
int		ft_isvector(char *c, int (*func)());
int		data_checker(char *line);
int		R_checker(char *line);
int		A_checker(char *line);
int		c_checker(char *line);
int		l_checker(char *line);
int		sp_checker(char *line);
int		pl_checker(char *line);
int		sq_checker(char *line);
int		cy_checker(char *line);
int		tr_checker(char *line);
int		ft_putstr_fd(char *s, int fd);
void	errorPrinter(t_err err);

/*
** -------------------------------------------------------
*/

/*
** --------------- PARSING FUNCTION ----------------------
*/

int			ft_nbr_words(char *str, char c);
void		*ft_memcpy(void *dst, const void *src, size_t n);
size_t		ft_strlen(const char *s);
char		*ft_substr(char const *src, unsigned int start, size_t n);
char		*ft_strchr(char *str, int c);
char		*ft_strjoin(char const *s1, char const *s2);
int			get_next_line(int fd, char **line);
char		**ft_split(char const *s, char c);
char		**ft_split_whitespaces(char *str);
int			data_id(char **data);
void		data_insertion(t_data *D, char **data);
void		R_insertion(t_data *D, char **data);
void		A_insertion(t_data *D, char **data);
void		c_insertion(t_data *D, char **data);
void		l_insertion(t_data *D, char **data);
void		sp_insertion(t_data *D, char **data);
void		pl_insertion(t_data *D, char **data);
void		sq_insertion(t_data *D, char **data);
void		cy_insertion(t_data *D, char **data);
void		tr_insertion(t_data *D, char **data);

/*
** -------------------------------------------------------
*/

/*
**  ------------- Color Functions ----------
*/

t_vector color_diffuse(t_vector color_sphere, t_vector light_color, t_vector L, t_vector N, double brighness);
t_vector color_spec(t_vector light_color, t_vector R, t_vector V, double brighness);
int rgb_maker(t_vector rgb);
t_vector color_clamping(t_vector color);

/*
** -----------------------------------------
*/

/*
**  ---------- Equations Functions ---------
*/

double equationSphere(t_ray R, t_objects *obj, double *distance);
double equationPlane(t_ray R, t_objects *obj,double *distance);
double equationSquare(t_ray R, t_objects *obj,double *distance);
t_passage_cy equationCylinder(t_ray R, t_objects *obj,double *distance);
double equationTriangle(t_ray R, t_objects *obj,double *distance);

/*
** -----------------------------------------
*/

/*
**  ---------- Handler Functions ------------
*/

int sphereHandler(t_ray r, t_objects *p, double *distance, double *t, t_objects *lights, int color, t_p_shadow *t_shadow);
int planeHandler(t_ray r, t_objects *p, double *distance, double *t, t_objects *lights, int color, t_p_shadow *t_shadow);
int squareHandler(t_ray r, t_objects *p, double *distance, double *t, t_objects *lights, int color, t_p_shadow *t_shadow);
int cylinderHandler(t_ray r, t_objects *p, double *distance, double *t, t_objects *lights, int color, t_p_shadow *t_shadow);
int triangleHandler(t_ray r, t_objects *p, double *distance, double *t, t_objects *lights, int color, t_p_shadow *t_shadow);

/*
** -----------------------------------------
*/

/*
**  ---------- Shadow Handler Functions ------------
*/

int	shadowHandler(t_p_shadow *t_shadow, t_objects *lights, int color);

/*
** -----------------------------------------
*/

/*
**  ---------- Executers Functions ---------
*/

int colorCalculator(t_ray R, double t, t_objects *lights, t_vector N);
int	getPixelColor(t_objects *obj, t_ray r, double *distance, double *d_shadow, t_objects *lights);

/*
** -----------------------------------------
*/

/*
**  ---------- Rot_Trans Functions ---------
*/

void rotate(t_data *D, char **data);
void translate(t_data *D, char **data);

/*
** -----------------------------------------
*/

#endif

