/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_printer.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aboulbaz <aboulbaz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/19 10:02:56 by aboulbaz          #+#    #+#             */
/*   Updated: 2020/11/20 12:17:58 by aboulbaz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

void errorPrinterHelper1(int id)
{
    if (id == -1)
        ft_putstr_fd("not a data type \n", 2);
    else if (id == -2)
        ft_putstr_fd("Resolution has wrong number of values \n", 2);
    else if (id == -3)
        ft_putstr_fd("Resolution has a wrong entry \n", 2);
    else if (id == -4)
        ft_putstr_fd("Ambient has wrong number of values \n", 2);
    else if (id == -5)
        ft_putstr_fd("Ambient has a wrong entry \n", 2);
    else if (id == -6)
        ft_putstr_fd("Camera has wrong number of values \n", 2);
    else if (id == -7)
        ft_putstr_fd("Camera has a wrong entry \n", 2);
    else if (id == -8)
        ft_putstr_fd("Light has wrong number of values \n", 2);
    else if (id == -9)
        ft_putstr_fd("Light has a wrong entry \n", 2);
    else if (id == -10)
        ft_putstr_fd("Sphere has wrong number of values \n", 2);
    else if (id == -11)
        ft_putstr_fd("Sphere has a wrong entry \n", 2);
}

void    errorPrinterHelper2(int id)
{
    if (id == -12)
        ft_putstr_fd("Plane has wrong number of values\n", 2);
    else if (id == -13)
        ft_putstr_fd("Plane has a wrong entry\n", 2);
    else if (id == -14)
        ft_putstr_fd("Square has wrong number of values\n", 2);
    else if (id == -15)
        ft_putstr_fd("Square has a wrong entry\n", 2);
    else if (id == -16)
        ft_putstr_fd("Cylinder has wrong number of values\n", 2);
     else if (id == -17)
        ft_putstr_fd("Cylinder has a wrong entry\n", 2);
    else if (id == -18)
        ft_putstr_fd("Triangle has wrong number of values\n", 2);
    else if (id == -19)
        ft_putstr_fd("Triangle has a wrong entry\n", 2);
    else if(id == -20)
        ft_putstr_fd("File not found\n", 2);
    else if(id == -21)
        ft_putstr_fd("Wrong number of inputs\n", 2);
    else if(id == -22)
        ft_putstr_fd("Do you mean \"--save\"?\n", 2);
    else if(id == -23)
        ft_putstr_fd("Resolutuion doesn't exist\n", 2);
    else if(id == -24)
        ft_putstr_fd("Ambient doesn't exist\n", 2);
    else if(id == -25)
        ft_putstr_fd("Camera doesn't exist\n", 2);
     else if(id == -26)
        ft_putstr_fd("Multiple Resolutions\n", 2);
    else if(id == -27)
        ft_putstr_fd("Multiple Ambient\n", 2);
}

void errorPrinter(t_err err)
{
    ft_putstr_fd("ERROR\n", 2);
    if (err.isChecked >= -11)
        errorPrinterHelper1(err.isChecked);
    else
        errorPrinterHelper2(err.isChecked);
    if (err.line != -1)
    {
        ft_putstr_fd(" at line: ", 2);
        ft_putnbr_fd(err.line, 2);
        ft_putstr_fd("\n", 2);
    }
    exit (1);
}