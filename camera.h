/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aboulbaz <aboulbaz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/14 11:45:18 by aboulbaz          #+#    #+#             */
/*   Updated: 2020/11/14 11:46:47 by aboulbaz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CAMERA_H
# define CAMERA_H
# include "vector.h"
# include "ray.h"

typedef struct		s_camera
{
	t_vector		start_point;
	t_vector		horizontal;
	t_vector		vertical;
	t_vector		origine;
}					t_camera;

#endif
