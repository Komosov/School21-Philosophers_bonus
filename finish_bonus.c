/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   finish_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lhelena <lhelena@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/27 19:45:08 by lhelena           #+#    #+#             */
/*   Updated: 2022/07/03 17:01:30 by lhelena          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

static void	clear(void *ptr, t_phil *philos)
{
	int		i;
	t_list	*vl;

	vl = (t_list *)ptr;
	i = 0;
	free(philos);
	sem_close(vl->print_sem);
	sem_close(vl->fork_sem);
	sem_close(vl->kill_sem);
	sem_close(vl->finish_sem);
	sem_unlink("/forks");
	sem_unlink("/print");
	sem_unlink("/kill");
	sem_unlink("/finish");
}

void	finish(void *ptr, t_phil *philos)
{
	int		i;
	t_list	*vl;

	vl = (t_list *)ptr;
	if (vl->p_pid == 0)
		exit(EXIT_SUCCESS);
	else
	{
		while (vl->end-- != 0)
			sem_wait(vl->finish_sem);
		i = 0;
		while (i++ < vl->n)
			sem_post(vl->kill_sem);
		clear(vl, philos);
		exit (EXIT_SUCCESS);
	}
}
