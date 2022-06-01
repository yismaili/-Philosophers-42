/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yismaili <yismaili@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/23 11:34:21 by yismaili          #+#    #+#             */
/*   Updated: 2022/06/01 18:28:54 by yismaili         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	*routine(void *ptr)
{	
	int			i;
	t_philo		*philo;
	pthread_t	thread;

	philo = (t_philo *)ptr;
	i = 0;
	if (philo->philo_id % 2 == 0)
	{
		usleep(100);
	}
	philo->time_to_kill = philo->data->get_t + philo->data->time_to_die;
	if (pthread_create(&thread, NULL, &check_died, philo) != 0)
		ft_die("Failed to create thread");
	pthread_detach(thread);
	while (1)
	{
		philo_activities(philo);
	}
	return (NULL);
}

void	philo_activities(t_philo *philo)
{
	pthread_mutex_lock(&philo->fork);
	get_message("has taken a fork", philo->philo_id, philo->data, KGRN);
	pthread_mutex_lock(philo->right_fork);
	get_message("has taken a fork", philo->philo_id, philo->data, KGRN);
	philo->count_eat++;
	if (philo->count_eat == philo->data->number_must_eat)
		philo->data->eaten++;
	philo->time_to_kill = get_time() + philo->data->time_to_die;
	get_message("is eating", philo->philo_id, philo->data, KYEL);
	usleep(1000 * philo->data->time_to_eat);
	get_message("is sleeping", philo->philo_id, philo->data, KBLU);
	pthread_mutex_unlock(&philo->fork);
	pthread_mutex_unlock(philo->right_fork);
	usleep(philo->data->time_to_sleep * 1000);
	get_message("is thinking", philo->philo_id, philo->data, KCYN);
}

void	*check_died(void *ptr)
{
	t_philo	*philo;

	philo = (t_philo *)ptr;
	while (1)
	{
		if (philo->time_to_kill <= get_time() && philo->data->time_to_die
			<= 310)
		{
			get_message("died", philo->philo_id, philo->data, KRED);
			pthread_mutex_lock(&philo->data->mut_write);
			philo->data->st = 1;
		}
		else if ((philo->time_to_kill + 8) == get_time())
		{
			get_message("died", philo->philo_id, philo->data, KRED);
			pthread_mutex_lock(&philo->data->mut_write);
			philo->data->st = 1;
		}
		else
		{
			philo->data->count_philo++;
		}
	}
	return (NULL);
}

void	*check_eat(void *ptr)
{
	t_philo	*philo;

	philo = (t_philo *)ptr;
	while (1)
	{
		if (philo->data->eaten == philo->data->number_of_philo)
			philo->data->st = 1;
		usleep(100);
	}
	return (NULL);
}

void	create_thread(t_philo *philo, t_data *data)
{
	int			i;
	pthread_t	temp;

	i = 0;
	while (i < data->number_of_philo)
	{
		if (pthread_create(&philo[i].th_philo, NULL, routine, &philo[i]) != 0)
			ft_die("Failed to create thread");
		pthread_detach(philo[i].th_philo);
		i++;
	}
	if (data->number_must_eat != -1)
	{
		if (pthread_create(&temp, NULL, check_eat, philo) != 0)
			ft_die("Failed to create thread");
		pthread_detach(temp);
	}
	i = 0;
	while (data->st == 0)
	{
		usleep(100);
	}
}
