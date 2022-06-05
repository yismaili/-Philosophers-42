/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utiles_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yismaili <yismaili@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/31 20:44:53 by yismaili          #+#    #+#             */
/*   Updated: 2022/06/05 14:37:53 by yismaili         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	*check_eat(void *ptr)
{
	t_philo	*philo;
	int		i;

	i = 0;
	philo = (t_philo *)ptr;
	while (i < philo->data->number_of_philo)
	{
		sem_wait(philo->data->eaten);
		i++;
	}
	sem_post(philo->data->ext);
	return (NULL);
}

void	init_sem(t_data *data)
{
	sem_unlink("/fork");
	data->fork = sem_open("/fork", O_CREAT, 0777, data->number_of_philo);
	sem_unlink("/dead_lock");
	data->mut_write = sem_open("/dead_lock", O_CREAT, 0777, 1);
	sem_unlink("/ext");
	data->ext = sem_open("/ext", O_CREAT, 0777, 0);
	sem_unlink("/dead");
	data->dead = sem_open("/dead", O_CREAT, 0777, 1);
	sem_unlink("/eat");
	data->eaten = sem_open("/eat", O_CREAT, 0777, 0);
}

void	*check_died(void *ptr)
{
	t_philo		*philo;

	philo = (t_philo *)ptr;
	while (1)
	{
		if (philo->time_to_kill <= get_time())
		{
			sem_wait(philo->data->dead);
			get_message("died", philo->philo_id, philo->data, KRED);
			sem_post(philo->data->ext);
		}
		usleep(100);
	}
	return (NULL);
}

void	*start_philo(void *ptr)
{
	t_philo		*philo;
	pthread_t	thread;

	philo = (t_philo *)ptr;
	philo->time_to_kill = philo->data->get_t + philo->data->time_to_die;
	if (pthread_create(&thread, NULL, &check_died, philo) != 0)
		ft_die("Failed to create thread");
	pthread_detach(thread);
	if (philo->philo_id % 2 == 0)
	{
		usleep(100);
	}
	philo->count_eat = 0 ;
	while (1)
	{
		philo_activities(philo);
	}
	return (NULL);
}
