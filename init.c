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

void	init_philo(t_data *data)
{
	int	i;
	t_philo *ptr;

	while (i < ptr->number_of_philo)
	{
		data->philo[i].time_to_eat = 0;
		data->philo[i].philo_position = i;
		data->philo[i].lift_fork = i;
		data->philo[i].right_fork = (i + 1) % (ptr->number_of_philo);
		data->philo[i].number_must_eat = 0;
		pthread_mutex_init(data->philo[i].mutex_philo, NULL);
		i++;
	}	
}

int   init_args(t_data *data, int ac, char **av)
{
    t_philo *ptr;
    if (ac > 4)
        exit(1);
    ptr->number_of_philo = ft_atoi(av[1]);
    ptr->time_to_die = ft_atoi(av[2]);
    ptr->time_to_eat = ft_atoi(av[3]);
    ptr->time_to_sleep = ft_atoi(av[4]);

    if (ac == 5)
        ptr->number_must_eat = ft_atoi(av[5]);
    else
        ptr->number_must_eat = 0; // ou bien -1
	data->philo = (t_philo*)malloc(sizeof(t_philo) * ptr->number_of_philo);
	if (!data->philo)
		return (0);
	init_philo(data);

	return (0);
}