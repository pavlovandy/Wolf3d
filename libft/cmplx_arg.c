/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmplx_arg.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apavlov <apavlov@student.unit.ua>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/09 14:23:34 by apavlov           #+#    #+#             */
/*   Updated: 2019/03/09 14:23:35 by apavlov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <math.h>

double		cmplx_arg(double x, double y)
{
	if (x > 0)
		return (atan(y / x));
	else if (x == 0)
		return (y > 0 ? M_PI / 2 : -M_PI / 2);
	else
		return (y >= 0 ? M_PI + atan(y / x) : -M_PI + atan(y / x));
}
