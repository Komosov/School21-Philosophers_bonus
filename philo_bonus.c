/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lhelena <lhelena@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/19 19:51:16 by lhelena           #+#    #+#             */
/*   Updated: 2022/07/03 17:00:17 by lhelena          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

int	main(int argc, char **argv)
{
	t_phil	*philos;
	t_list	vlist;

	if ((write_args(argc, argv, &vlist) != 0) || (init_main(&vlist) != 0))
		exit(EXIT_FAILURE);
	philos = (t_phil *)malloc(sizeof(t_phil) * vlist.n);
	if (!philos)
		exit(EXIT_FAILURE);
	vlist.i = 0;
	while (vlist.i < vlist.n)
	{
		philos[vlist.i].lptr = &vlist;
		philos[vlist.i].num = vlist.i;
		vlist.p_pid = fork();
		if (vlist.p_pid == -1)
			exit(EXIT_FAILURE);
		else if (vlist.p_pid == 0)
		{
			p_routine(philos[vlist.i]);
			break ;
		}
		vlist.i++;
	}
	finish(&vlist, philos);
}
