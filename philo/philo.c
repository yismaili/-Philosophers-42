/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yismaili <yismaili@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/23 11:34:21 by yismaili          #+#    #+#             */
/*   Updated: 2022/05/16 18:53:48 by yismaili         ###   ########.fr       */
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
	philo->time_to_kill = philo->data->get_t + philo->data->time_to_die;
	pthread_create(&thread, NULL, &ft_check, philo);
	pthread_detach(thread);
	while (1)
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
	return (NULL);
}

void *ft_check(void *ptr)
{
	t_philo		*philo;
	philo = (t_philo *)ptr;

	while (1)
	{
		if (philo->time_to_kill  <= get_time() && philo->data->time_to_die <= 310)
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
void *check_eat(void *ptr)
{
	t_philo *philo;
	philo = (t_philo *)ptr;
	while (1)
	{
		if (philo->data->eaten == philo->data->number_of_philo)
			philo->data->st = 1;
    	usleep(500);
	}
	return(NULL);
	
}
t_philo   *init_args(int ac, char **av, t_data	*data)
{
	t_philo	*philo;
	int		i;
	pthread_t temp;
	
	if (!data)
		return (0);
	data->get_t = get_time();
	data->count_philo = 0;
	data->st = 0;
	data->eaten = 0;
	data->number_of_philo =  ft_atoi(av[1]); 
	philo = malloc(sizeof(t_philo) * data->number_of_philo);
	if (!philo)
		return (0);
	i = 0;
	while (i < data->number_of_philo)
	{
		pthread_mutex_init(&philo[i].fork, NULL);
		i++;
	}
	i = 0;
	data->time_to_die = ft_atoi(av[2]);
	data->time_to_eat = ft_atoi(av[3]);
	data->time_to_sleep = ft_atoi(av[4]);
	if (ac == 6)
	{
		data->number_must_eat = ft_atoi(av[5]);
	}
	else
		data->number_must_eat = -1;
	if (data->number_of_philo <= 0 || data->number_of_philo > 200 || data->number_must_eat == 0)
		ft_die("ArgumentError\n");
	init_philo(philo, data);

	while (i < data->number_of_philo )
	{
		if (pthread_create(&philo[i].th_philo, NULL, routine, &philo[i]) != 0)
			ft_die("Failed to create thread");
		pthread_detach(philo[i].th_philo);
		usleep(100);
		i++;
	}
	if (data->number_must_eat != -1)
	{
		if (pthread_create(&temp, NULL, check_eat, philo) != 0)
			ft_die("Failed to create thread");
		pthread_detach(temp);
	}
	i = 0;
	while(data->st == 0)
	{
		usleep(100);
	}
	return (philo);
}

void init_philo(t_philo *philo, t_data *data)
{
	int i;

	i = 0;
	while (i < data->number_of_philo)
	 {
		philo[i].philo_id = i + 1;
		philo[i].data = data;
		 if (i == (data->number_of_philo - 1))
	 	 	philo[i].right_fork = &philo[0].fork;
		 else
		 	philo[i].right_fork = &philo[i + 1].fork;
		i++;
	}
}
 int 	ft_die(char *str)
 {
	printf("%s\n", str);	
	return (0);
 }
