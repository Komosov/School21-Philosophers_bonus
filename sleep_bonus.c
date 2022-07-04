/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sleep_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lhelena <lhelena@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/19 17:25:34 by lhelena           #+#    #+#             */
/*   Updated: 2022/07/03 17:20:05 by lhelena          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	p_sleep(void *ptr)
{
	t_list	*vl;
	t_phil	*p;

	p = (t_phil *)ptr;
	vl = (t_list *)p->lptr;
	sem_wait(vl->print_sem);
	printf("%d \t%d is sleeping\n",
		now_time(vl->start.tv_sec, vl->start.tv_usec), p->num + 1);
	sem_post(vl->print_sem);
	if (ttr(p->last_eat.tv_sec, p->last_eat.tv_usec, vl->ttl) < vl->tts)
	{
		ft_usleep(ttr(p->last_eat.tv_sec, p->last_eat.tv_usec, vl->ttl)
			* 1000, ptr);
		sem_wait(vl->print_sem);
		printf("%d \t%d dead\n",
			now_time(vl->start.tv_sec, vl->start.tv_usec), p->num + 1);
		kill_em_all(p);
	}
	else
		ft_usleep(vl->tts * 1000, ptr);
}
