/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aboulbaz <aboulbaz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/19 09:57:49 by aboulbaz          #+#    #+#             */
/*   Updated: 2020/11/25 14:32:12 by aboulbaz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"
#include <mlx.h>

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
	free(p);
	free(q);
	return (lst);
}

t_err		file_checker(char *file)
{
    int		isChecked;
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
		{
			free(line);
            continue;
		}
		err.line++;
		err.isChecked = data_checker(line);
		if (err.isChecked != 1)
			return (err);
		free(line);
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
		{
			free(line);
            continue;
		}
        data = ft_split_whitespaces(line);
		data_insertion(&d, data);
		free(line);
    }
    close(fd);
    return (d);
}

void		graphicDrawer(t_main *m)
{
	int i;
	int j;
	double u[2];
	double distance[2];
	int k;

	j = 0;
	k = 0;
	while(j < m->d.R.y)
	{
		i = m->d.R.x - 1;
		while (i >= 0)
		{
			u[0] = (double)i / (double)m->d.R.x;
			u[1] = (double)j / (double)m->d.R.y;
			t_ray r = get_t_ray(m->d, u[0], u[1]);
			m->w.img_data[k++] = getPixelColor(m->d.obj, r, &distance[0], &distance[1], m->d.lights);
			i--;
		}
		j++;
	}
	if (m->isSave == 1)
		save_bmp_image(*m);
	else
		mlx_put_image_to_window(m->w.mlx_ptr, m->w.win_ptr, m->w.img_ptr,0,0);
}

int key_press(int keycode, t_main *m)
{
	if(keycode == 53 || keycode == 12)
		exit(0);
	if (keycode == 123)
	{
		m->d.cameras = get_cam_previous(&m->d.cameras);
		graphicDrawer(m);
	}
	if (keycode == 124)
	{
		m->d.cameras = get_cam_next(&m->d.cameras);
		graphicDrawer(m);
	}
	return (0);
}

t_data parse(char **argv, t_main *m, int ac)
{
	t_data d;

	m->isSave = 0;
	d = file_parser(argv[1]);
	if (ac == 3 && ft_strncmp(argv[2], "--save", 6) == 0)
		m->isSave = 1;
	d.cameras = getcams(d);
	d.lights = getLigths(d.obj);
	return (d);
}

int			main(int argc, char **argv)
{
	t_main	m;
	t_err err;
	int	a;
	int b;

	m.w.mlx_ptr = mlx_init();
	mlx_get_screen_size(m.w.mlx_ptr, &a, &b);
	
	if (argc == 2 || argc == 3 )
	{
		err = file_checker(argv[1]);
		if (err.isChecked == 1)
		{
			m.d = parse(argv, &m, argc);
			if ((m.d.R.x >= 0 && m.d.R.x <= a)&& (m.d.R.y >= 0 && m.d.R.y <= b))
			{
				m.w.win_ptr = mlx_new_window(m.w.mlx_ptr,m.d.R.x,m.d.R.y,"miniRT");
				m.w.img_ptr = mlx_new_image(m.w.mlx_ptr,m.d.R.x,m.d.R.y);
				m.w.img_data = (int *)mlx_get_data_addr(m.w.img_ptr, &m.w.bpp, &m.w.size_l, &m.w.img_endian);
				graphicDrawer(&m);
				if (m.isSave == 0)
				{
					mlx_hook(m.w.win_ptr, 2, 0, key_press, &m);
					mlx_loop(m.w.mlx_ptr);
				}
			}
		}
		else
			errorPrinter(err);
	}
	return (0);
}
