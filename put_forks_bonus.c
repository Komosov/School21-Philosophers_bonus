/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   put_forks_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lhelena <lhelena@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/19 16:19:47 by lhelena           #+#    #+#             */
/*   Updated: 2022/07/03 17:19:54 by lhelena          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	p_put_forks(void *ptr)
{
	t_list	*vl;
	t_phil	*p;

	p = (t_phil *)ptr;
	vl = (t_list *)p->lptr;
	if (ttr(p->last_eat.tv_sec, p->last_eat.tv_usec, vl->ttl) < 0)
	{
		sem_wait(vl->print_sem);
		printf("%d \t%d dead\n",
			now_time(vl->start.tv_sec, vl->start.tv_usec), p->num + 1);
		kill_em_all(p);
	}
	sem_post(vl->fork_sem);
	sem_post(vl->fork_sem);
}
