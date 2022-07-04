/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   eat_bonus.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lhelena <lhelena@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/19 17:24:02 by lhelena           #+#    #+#             */
/*   Updated: 2022/07/03 19:44:37 by lhelena          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

static void	died_while_eating(void *ptr)
{
	t_list	*vl;
	t_phil	*p;

	p = (t_phil *)ptr;
	vl = (t_list *)p->lptr;
	ft_usleep(ttr(p->last_eat.tv_sec, p->last_eat.tv_usec, vl->ttl) * 1000,
		ptr);
	sem_wait(vl->print_sem);
	printf("%d \t%d dead\n",
		now_time(vl->start.tv_sec, vl->start.tv_usec), p->num + 1);
	kill_em_all(p);
}

int	p_eat(void *ptr)
{
	t_list	*vl;
	t_phil	*p;

	p = (t_phil *)ptr;
	vl = (t_list *)p->lptr;
	sem_wait(vl->print_sem);
	gettimeofday(&p->last_eat, NULL);
	printf("%d \t%d is eating\n",
		now_time(vl->start.tv_sec, vl->start.tv_usec), p->num + 1);
	sem_post(vl->print_sem);
	if (ttr(p->last_eat.tv_sec, p->last_eat.tv_usec, vl->ttl) < vl->tte)
		died_while_eating(p);
	else
		ft_usleep(vl->tte * 1000, ptr);
	return (0);
}

int	p_iter_eat(void *ptr)
{
	t_list	*vl;
	t_phil	*p;

	p = (t_phil *)ptr;
	vl = (t_list *)p->lptr;
	sem_wait(vl->print_sem);
	gettimeofday(&p->last_eat, NULL);
	printf("%d \t%d is eating\n",
		now_time(vl->start.tv_sec, vl->start.tv_usec), p->num + 1);
	sem_post(vl->print_sem);
	if (ttr(p->last_eat.tv_sec, p->last_eat.tv_usec, vl->ttl) < vl->tte)
		died_while_eating(p);
	else
		ft_usleep(vl->tte * 1000, ptr);
	sem_wait(vl->print_sem);
	sem_post(vl->finish_sem);
	printf("%d \t%d is reached %d iterations\n",
		now_time(vl->start.tv_sec, vl->start.tv_usec), p->num + 1, p->iter);
	usleep(400);
	sem_post(vl->print_sem);
	return (0);
}
