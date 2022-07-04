/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   think_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lhelena <lhelena@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/19 17:26:57 by lhelena           #+#    #+#             */
/*   Updated: 2022/07/03 17:20:26 by lhelena          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	p_think(void *ptr)
{
	t_list	*vl;
	t_phil	*p;

	p = (t_phil *)ptr;
	vl = (t_list *)p->lptr;
	sem_wait(vl->print_sem);
	printf("%d \t%d is thinking\n",
		now_time(vl->start.tv_sec, vl->start.tv_usec), p->num + 1);
	sem_post(vl->print_sem);
	if (ttr(p->last_eat.tv_sec, p->last_eat.tv_usec, vl->ttl) < 0)
	{
		sem_wait(vl->print_sem);
		printf("%d \t%d dead\n",
			now_time(vl->start.tv_sec, vl->start.tv_usec), p->num + 1);
		kill_em_all(p);
	}
}
