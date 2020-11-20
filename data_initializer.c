/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   data_initializer.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aboulbaz <aboulbaz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/19 13:49:43 by aboulbaz          #+#    #+#             */
/*   Updated: 2020/11/20 13:50:24 by aboulbaz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

t_objects		*ligth_initializer(char **lp, char **lc, char *brightness)
{
	t_Light		*light;
	t_objects	*obj;

	if (!(light = (t_Light*)malloc(sizeof(t_Light))))
		return (0);
	if (!(obj = (t_objects*)malloc(sizeof(t_objects))))
		return (0);
	light->light_pos = initialize_vector(atof(lp[0]), atof(lp[1]), atof(lp[2]));
	light->light_color = initialize_vector(atof(lc[0]), \
						atof(lc[1]), atof(lc[2]));
	light->brightness = strtof(brightness, NULL);
	obj->id = 3;
	obj->content = light;
	obj->next = NULL;
	return (obj);
}

t_objects		*cam_initializer(char **vp, char **cn, char *fov)
{
	t_Cam_data	*cam;
	t_objects	*obj;

	if (!(cam = (t_Cam_data*)malloc(sizeof(t_Cam_data))))
		return (0);
	if (!(obj = (t_objects*)malloc(sizeof(t_objects))))
		return (0);
	cam->view_point = initialize_vector(atof(vp[0]), atof(vp[1]), atof(vp[2]));
	cam->cam_normal = initialize_vector(atof(cn[0]), atof(cn[1]), atof(cn[2]));
	cam->fov = strtof(fov, NULL);
	obj->id = 2;
	obj->content = cam;
	obj->next = NULL;
	return (obj);
}
