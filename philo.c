/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yismaili <yismaili@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/23 11:34:21 by yismaili          #+#    #+#             */
/*   Updated: 2022/05/08 18:10:53 by yismaili         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	*routine(void *ptr)
{	
	int			i;
	t_philo		*philo;
	pthread_t	thread;
	philo = (t_philo *)ptr;
	philo->eat_count = 0;
	i = 0;
	philo->last_time = philo->data->get_t + philo->data->time_to_die;
	// pthread_create(&thread, NULL, &ft_check, philo);
	// pthread_detach(thread);
	while (i < philo->data->number_of_philo)
	{
		philo_activities(philo);
		if (i == philo->data->number_must_eat)
			get_message("is thinking", philo->philo_id, philo->data);
		i++;
	}
	philo->eat_count = 1;
	return (NULL);
}

void *ft_check(void *ptr)
{
	t_philo		*philo;
	philo = (t_philo *)ptr;

	while (1)
	{
		if (get_time() >= philo->last_time + 5)
		{
			get_message("died", philo->philo_id, philo->data);
			pthread_mutex_lock(&philo->data->mut_write);
			philo->data->stut = 1;
		}
		else if (philo->eat_count == 1)
		{
			philo->data->nb++;
			break;
		}
	}
	return (NULL);
}
t_philo   *init_args(int ac, char **av, t_data	*data)
{
	t_philo	*philo;
	int		i;

	if (!data)
		return (0);
	data->get_t = get_time();
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
	if (ac == 5)
		data->number_must_eat = ft_atoi(av[5]);
	else
		data->number_must_eat = 0; // ou bien -1
	init_philo(philo, data);
	while (i < data->number_of_philo)
	{
		if (pthread_create(&philo[i].th_philo, NULL, routine, &philo[i]) != 0)
			ft_die("Failed to create thread",philo);
		usleep(10);
		i++;
	}
	i = 0;
	while(1);
	while (i < data->number_of_philo)
		pthread_detach(philo[i++].th_philo);
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
 void	ft_die(char *str , t_philo *philo)
 {
	 free(philo);
	 	printf("%s\n", str);	
	 return ;
 }
