/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yismaili <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/23 18:53:53 by yismaili          #+#    #+#             */
/*   Updated: 2022/04/23 18:54:07 by yismaili         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"
#include <stdlib.h>

void	init_philo(t_data *data)
{
	int	i;
	i = 0;
	while (i < data->number_of_philo)
	{
		data->philo[i].philo_position = i;
		data->philo[i].lift_fork = i;
		data->philo[i].right_fork = i + 1;
		if (data->philo[i].right_fork == data->number_of_philo)
			data->philo[i].right_fork = 0;
		pthread_mutex_init(&data->philo[i].mutex_philo, NULL);
		i++;
	}
}
void	*routine(void *ptr)
{
	printf("hey\n");
	return (NULL);
}
void create_pthread(t_data *data)
{
	int i;
	t_philo *ptr;
	i = 0;
	while (i < data->number_of_philo)
	{
		pthread_create(&ptr->th_philo[i], NULL, routine, (void *) &i);
		i++;
	}
	i = 0;
	while (i < data->number_of_philo)
	{
		pthread_join(ptr->th_philo[i], NULL);
		i++;
	}
}
t_data   *init_args(int ac, char **av)
{
	t_data	*data;
	int		i;

	data = malloc(sizeof(t_data));
	if (!data)
		return (0);
	data->number_of_philo =  ft_atoi(av[1]); 
	data->philo = malloc(sizeof(t_philo) * 	data->number_of_philo);
	if (!data->philo)
		return (0);
	i = 0;
	while (i < data->number_of_philo)
	{
		data->philo[i].time_to_die = ft_atoi(av[2]);
		data->philo[i].time_to_eat = ft_atoi(av[3]);
		data->philo[i].time_to_sleep = ft_atoi(av[4]);
		if (ac == 5)
			data->philo[i].number_must_eat = ft_atoi(av[5]);
		else
			data->philo[i].number_must_eat = 0; // ou bien -1
		i++;
	}
	init_philo(data);
	

	return (data);
}