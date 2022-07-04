/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lhelena <lhelena@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/19 19:51:27 by lhelena           #+#    #+#             */
/*   Updated: 2022/07/03 17:14:50 by lhelena          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_BONUS_H
# define PHILO_BONUS_H

# include <limits.h>
# include <string.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <signal.h>
# include <sys/time.h>
# include <pthread.h>
# include <sys/wait.h>
# include <semaphore.h>
# include <sys/ipc.h>

typedef struct s_list
{
	int				i;
	int				n;
	int				ttl;
	int				tte;
	int				tts;
	int				iters;
	int				end;
	pid_t			p_pid;
	sem_t			*fork_sem;
	sem_t			*print_sem;
	sem_t			*kill_sem;
	sem_t			*finish_sem;
	struct timeval	start;
}t_list;

typedef struct s_phil
{
	int				i;
	int				num;
	int				iter;
	void			*lptr;
	pthread_t		rip_th;
	pthread_t		kill_th;
	struct timeval	last_eat;
}t_phil;

void	finish(void *ptr, t_phil *philos);
int		ft_atoi(const char *str);
int		ft_isdigit(int c);
int		ft_max(int a, int b);
int		ft_min(int a, int b);
void	ft_usleep(int usec, void *ptr);
int		init_main(void *ptr);
void	kill_em_all(t_phil	*p);
int		now_time(long sec, int msec);
int		now_time_usec(long sec, int msec);
int		p_eat(void *ptr);
int		p_iter_eat(void *ptr);
void	p_put_forks(void *ptr);
void	p_routine(t_phil ptr);
void	p_sleep(void *ptr);
int		p_take_forks(void *ptr);
void	p_think(void *ptr);
long	ttr(long sec, int usec, int ttl);
int		write_args(int argc, char **argv, void *ptr);

#endif
