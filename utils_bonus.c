/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lhelena <lhelena@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/13 20:56:55 by lhelena           #+#    #+#             */
/*   Updated: 2022/07/03 17:04:41 by lhelena          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

int	ft_min(int a, int b)
{
	if (a < b)
		return (a);
	else
		return (b);
}

int	ft_max(int a, int b)
{
	if (a > b)
		return (a);
	else
		return (b);
}

int	ft_isdigit(int c)
{
	return (c >= '0' && c <= '9');
}

void	ft_usleep(int usec, void *ptr)
{
	struct timeval	start;
	t_list			*vl;
	t_phil			*p;

	p = (t_phil *)ptr;
	vl = (t_list *)p->lptr;
	gettimeofday(&start, NULL);
	if (usec > 0)
	{
		if (usec <= 50)
			usleep(usec);
		else
		{
			while (now_time_usec(start.tv_sec, start.tv_usec) < usec)
				usleep(50);
		}
	}
}
