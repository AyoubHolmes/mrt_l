/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color_func.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aboulbaz <aboulbaz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/14 12:54:17 by aboulbaz          #+#    #+#             */
/*   Updated: 2020/11/19 11:34:01 by aboulbaz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// TO RECHECK 

#include "miniRT.h"

t_vector		color_diffuse(t_vector color_sphere, t_vector light_color, t_vector L, t_vector N, double brighness)
{
	t_vector	color;
	double		l;

	l = scalar(L, N);
	l = l < 0 ? 0 : l;
	color.x = color_sphere.x * light_color.x * l * brighness;
	color.y = color_sphere.y * light_color.y * l * brighness;
	color.z = color_sphere.z * light_color.z * l * brighness;
	return (color);
}

t_vector		color_spec(t_vector light_color,\
				t_vector r, t_vector v, double brighness)
{
	t_vector	color;
	double		l;
	double		alpha;

	alpha = 800;
	l = scalar(r, v);
	l = l < 0 ? 0 : l;
	color.x = light_color.x * pow(l, alpha);
	color.y = light_color.y * pow(l, alpha);
	color.z = light_color.z * pow(l, alpha);
	return (color);
}

int				rgb_maker(t_vector rgb)
{
	return (((int)(rgb.x * 255.99) << 16) + \
		((int)(rgb.y * 255.99) << 8) + (int)(rgb.z * 255.99));
}

t_vector		color_clamping(t_vector color)
{
	color.x = (color.x < 1) ? color.x : 1;
	color.x = (color.x >= 0) ? color.x : 0;
	color.y = (color.y < 1) ? color.y : 1;
	color.y = (color.y >= 0) ? color.y : 0;
	color.z = (color.z < 1) ? color.z : 1;
	color.z = (color.z >= 0) ? color.z : 0;
	return (color);
}
