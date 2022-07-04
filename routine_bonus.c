/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lhelena <lhelena@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/26 15:09:12 by lhelena           #+#    #+#             */
/*   Updated: 2022/07/03 17:27:26 by lhelena          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	kill_em_all(t_phil	*p)
{
	t_list	*vl;
	int		i;

	vl = (t_list *)p->lptr;
	i = 0;
	while (i < vl->n)
	{
		sem_post(vl->kill_sem);
		i++;
	}
	sem_post(vl->finish_sem);
}

static void	*rip_routine(void *ptr)
{
	t_list	*vl;
	t_phil	*p;

	p = (t_phil *)ptr;
	vl = (t_list *)p->lptr;
	while (1)
	{
		sem_wait(vl->print_sem);
		if (ttr(p->last_eat.tv_sec, p->last_eat.tv_usec, vl->ttl) < 0)
		{
			printf("%d \t%d dead\n",
				now_time(vl->start.tv_sec, vl->start.tv_usec), p->num + 1);
			kill_em_all(p);
		}
		sem_post(vl->print_sem);
		usleep(100);
	}
	return (NULL);
}

static void	*kill_routine(void *ptr)
{
	t_list	*vl;
	t_phil	*p;

	p = (t_phil *)ptr;
	vl = (t_list *)p->lptr;
	sem_wait(vl->kill_sem);
	kill_em_all(p);
	exit(EXIT_SUCCESS);
}

void	p_routine(t_phil ph)
{
	t_list	*vl;

	vl = (t_list *)ph.lptr;
	gettimeofday(&ph.last_eat, NULL);
	ph.iter = 0;
	if (ph.num % 2 != 0)
		ft_usleep(vl->tte / 2 * 1000, &ph);
	if (pthread_create(&ph.rip_th, NULL, &rip_routine, &ph))
		exit (EXIT_FAILURE);
	if (pthread_create(&ph.kill_th, NULL, &kill_routine, &ph))
		exit (EXIT_FAILURE);
	while (1)
	{
		p_take_forks(&ph);
		ph.iter++;
		if (ph.iter == INT_MAX)
			ph.iter = 0;
		if (ph.iter == vl->iters)
			p_iter_eat(&ph);
		else
			p_eat(&ph);
		p_put_forks(&ph);
		p_sleep(&ph);
		p_think(&ph);
	}
}
