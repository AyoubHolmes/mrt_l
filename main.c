#include "miniRT.h"
#include <mlx.h>
//gcc -Wall -Werror -Wextra  -I /usr/local/include -L /usr/local/lib -lmlx -framework OpenGl -framework AppKit tracing_t_ray.c && ./a.out
// gcc -I /usr/local/include -L /usr/local/lib -lmlx -framework OpenGl -framework AppKit tracing_t_ray.c && ./a.out


t_objects *getLigths(t_objects *obj)
{
	t_objects	*p;
	t_objects	*q;
	t_objects	*lst;

	p = obj;
	lst = NULL;
	if (!(q = (t_objects*)malloc(sizeof(t_objects))))
		return (0);
	while (p != NULL)
	{
		if (p->id == 3)
		{
			q->content = p->content;
			q->id = 3;
			q->next = NULL;
			ft_lstadd_back(&lst, q);
		}
		p = p->next;
	}
	return (lst);
}

t_err		file_checker(char *file)
{
    int		isChecked;
    char	**data;
    char	*line;
    int		fd;
    int		rest;
	t_err	err;

    fd = open(file, O_RDONLY);
    rest = 1;
	err.line = 0;
    while(rest == 1)
    {
        rest = get_next_line(fd, &line);
        if (line[0] == '\0')
            continue;
		err.line++;
		err.isChecked = data_checker(line);
		if (err.isChecked != 1)
			return (err);
    }
    close(fd);
	err.isChecked = 1;
    return (err);
}

t_data		file_parser(char *file)
{
    t_data d;
    char **data;
    char *line;
    int fd;
    int rest;

	d.obj = NULL;
    fd = open(file, O_RDONLY);
    rest = 1;
    while(rest == 1)
    {
        rest = get_next_line(fd, &line);
        if (line[0] == '\0')
            continue;
        data = ft_split_whitespaces(line);
		data_insertion(&d, data);
    }
    close(fd);
    return (d);
}

void		graphicDrawer(t_data d,t_window w)
{
	int i;
	int j;
	double u;
	double v;
	double distance[2];
	int k;

	j = 0;
	k = 0;
	while(j < d.R.y)
	{
		i = d.R.x - 1;
		while (i >= 0)
		{
			u = (double)i / (double)d.R.x;
			v = (double)j / (double)d.R.y;
			t_ray r = get_t_ray(d, u, v);
			w.img_data[k++] = getPixelColor(d.obj, r, &distance[0], &distance[1], d.lights);
			i--;
		}
		j++;
	}
	mlx_put_image_to_window(w.mlx_ptr, w.win_ptr, w.img_ptr,0,0);
}

int key_press(int keycode, t_main *m)
{
	if(keycode == 53 || keycode == 12)
		exit(0);
	if (keycode == 123)
	{
		m->d.cameras = get_cam_previous(&m->d.cameras);
		graphicDrawer(m->d, m->w);
		printf("test here 1 \n");
	}
	if (keycode == 124)
	{
		m->d.cameras = get_cam_next(&m->d.cameras);
		printf("test here 2 \n");
		graphicDrawer(m->d, m->w);
	}
	return (0);
}

t_data parse(char *filename)
{
	t_data d;

	d = file_parser(filename);
	objectsDebugger(d);
	d.cameras = getCams(d);
	d.lights = getLigths(d.obj);
	/*if (d.lights == 0 || d.cameras == 0 || d.obj == 0)
		return (0);*/
	return (d);
}

int			main()
{
	t_main	m;
	t_err err;

	err = file_checker("test.rt");
	if (err.isChecked == 1)
	{
		m.d = parse("test.rt");
		m.w.mlx_ptr = mlx_init();
		m.w.win_ptr = mlx_new_window(m.w.mlx_ptr,m.d.R.x,m.d.R.y,"miniRT");
		m.w.img_ptr = mlx_new_image(m.w.mlx_ptr,m.d.R.x,m.d.R.y);
		m.w.img_data = (int *)mlx_get_data_addr(m.w.img_ptr, &m.w.bpp, &m.w.size_l, &m.w.img_endian);
		graphicDrawer(m.d, m.w);
		mlx_hook(m.w.win_ptr, 2, 0, key_press, &m);
		mlx_loop(m.w.mlx_ptr);
	}
	else
	{
		errorPrinter(err);
		exit(1);
	}
	return (0);
}
