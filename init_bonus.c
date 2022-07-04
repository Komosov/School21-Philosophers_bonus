/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lhelena <lhelena@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/26 21:21:06 by lhelena           #+#    #+#             */
/*   Updated: 2022/07/03 17:02:51 by lhelena          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

static void	second_init(void *ptr)
{
	t_list	*vl;

	vl = (t_list *)ptr;
	vl->end = vl->n;
	gettimeofday(&vl->start, NULL);
}

int	init_main(void *ptr)
{
	t_list	*vl;

	vl = (t_list *)ptr;
	sem_unlink("/forks");
	sem_unlink("/print");
	sem_unlink("/kill");
	sem_unlink("/finish");
	vl->fork_sem = sem_open("/forks", O_CREAT, S_IRWXU, vl->n);
	vl->kill_sem = sem_open("/kill", O_CREAT, S_IRWXU, vl->n);
	vl->finish_sem = sem_open("/finish", O_CREAT, S_IRWXU, 1);
	vl->print_sem = sem_open("/print", O_CREAT, S_IRWXU, 1);
	sem_wait(vl->finish_sem);
	vl->i = 1;
	while (vl->i <= vl->n)
	{
		sem_wait(vl->kill_sem);
		vl->i++;
	}
	second_init(ptr);
	return (0);
}
