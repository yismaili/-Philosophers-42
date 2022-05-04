/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yismaili <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/23 11:34:21 by yismaili          #+#    #+#             */
/*   Updated: 2022/04/23 11:34:59 by yismaili         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	init_philo(t_philo *philo, t_data *data)
{
	int	i;
	i = 0;
	while (i < data->number_of_philo)
	 {
		philo[i].philo_position = i;
		philo[i].lift_fork = philo[i].fork;
		philo[i].right_fork = philo[i + 1].fork;
		if (i == data->number_of_philo)
	 		philo[i].right_fork = philo[0].fork;
		i++;
	}
}
void	*routine(void *ptr)
{	
	int i = 0;
	t_philo		*philo;

	philo = (t_philo *)ptr;
	take_forks(philo);

	
	return (NULL);
}
void create_pthread(t_data *data)
{
	int i;
	t_philo *ptr;
	pthread_t	th_philo;
	i = 0;
	while (i < data->number_of_philo)
	{
		pthread_create(&th_philo, NULL, routine, (void *) &i);
		i++;
	}
	i = 0;
	while (i < data->number_of_philo)
	{
		pthread_join(th_philo, NULL);
		i++;
	}
}

t_data   *init_args(int ac, char **av)
{
	t_data	*data;
	t_philo	*philo;
	int		i;

	data = malloc(sizeof(t_data));
	if (!data)
		return (0);
	data->number_of_philo =  ft_atoi(av[1]); 
	philo = malloc(sizeof(t_philo) * 	data->number_of_philo);
	if (!philo)
		return (0);
	i = 0;
	while (i < data->number_of_philo)
	{
		data->time_to_die = ft_atoi(av[2]);
		data->time_to_eat = ft_atoi(av[3]);
		data->time_to_sleep = ft_atoi(av[4]);
		if (ac == 5)
			data->number_must_eat = ft_atoi(av[5]);
		else
			data->number_must_eat = 0; // ou bien -1
		i++;
	}
	init_philo(philo, data);

	return (data);
}

