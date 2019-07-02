/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   count_number.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apavlov <apavlov@student.unit.ua>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/09 12:01:44 by apavlov           #+#    #+#             */
/*   Updated: 2019/01/09 12:01:45 by apavlov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int			count_num(int num)
{
	int res;

	if (num == 0)
		return (1);
	res = 0;
	while (num)
	{
		num /= 10;
		res++;
	}
	return (res);
}