/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   take_forks_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lhelena <lhelena@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/13 21:06:01 by lhelena           #+#    #+#             */
/*   Updated: 2022/07/03 17:20:22 by lhelena          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

static int	is_rip_after_mutex_1(void *ptr)
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
		return (1);
	}
	else
		return (0);
}

static int	is_rip_after_mutex_2(void *ptr)
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
		return (1);
	}
	return (0);
}

static void	check_only_one_fork(void *ptr)
{
	t_list	*vl;
	t_phil	*p;

	p = (t_phil *)ptr;
	vl = (t_list *)p->lptr;
	if (vl->n == 1)
	{
		ft_usleep(vl->ttl * 1000, p);
		sem_wait(vl->print_sem);
		printf("%d \t%d dead\n",
			now_time(vl->start.tv_sec, vl->start.tv_usec), p->num + 1);
		kill_em_all(p);
	}
}

int	p_take_forks(void *ptr)
{
	t_list	*vl;
	t_phil	*p;

	p = (t_phil *)ptr;
	vl = (t_list *)p->lptr;
	sem_wait(vl->fork_sem);
	is_rip_after_mutex_1(p);
	sem_wait(vl->print_sem);
	printf("%d \t%d has taken a fork 1\n",
		now_time(vl->start.tv_sec, vl->start.tv_usec), p->num + 1);
	sem_post(vl->print_sem);
	check_only_one_fork(p);
	sem_wait(vl->fork_sem);
	is_rip_after_mutex_2(p);
	sem_wait(vl->print_sem);
	printf("%d \t%d has taken a fork 2\n",
		now_time(vl->start.tv_sec, vl->start.tv_usec), p->num + 1);
	sem_post(vl->print_sem);
	return (0);
}
