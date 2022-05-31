/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yismaili <yismaili@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/16 12:39:11 by yismaili          #+#    #+#             */
/*   Updated: 2022/05/31 20:46:18 by yismaili         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

t_data	*init_data(int ac, char **av, t_data	*data)
{
	int			i;
	t_philo		*philo;

	philo->count_eat = 0;
	data->number_of_philo = ft_atoi(av[1]);
	data->time_to_die = ft_atoi(av[2]);
	data->time_to_eat = ft_atoi(av[3]);
	data->time_to_sleep = ft_atoi(av[4]);
	if (ac == 6)
		data->number_must_eat = ft_atoi(av[5]);
	else
		data->number_must_eat = -1;
	if (data->number_of_philo <= 0 || data->number_of_philo > 200
		|| data->number_must_eat == 0 || data->time_to_eat < 60
		|| data->time_to_sleep < 60 || data->time_to_die < 60)
		ft_die("error args");
	create_process(philo, data);
	return (data);
}

void	create_process(t_philo	*philo, t_data *data)
{
	int		i;
	pid_t	*pid;

	i = 0;
	philo = (t_philo *)malloc(sizeof(t_philo) * data->number_of_philo);
	pid = (pid_t *)malloc(sizeof(int) * data->number_of_philo);
	i = 0;
	init_sem(data);
	data->get_t = get_time();
	start_process(philo, data, pid);
	sem_wait(data->ext);
	ft_kill(data, &pid, philo);
}

void	start_process(t_philo *philo, t_data *data, pid_t *pid)
{
	int			i;
	pthread_t	temp;

	i = 0;
	while (i < data->number_of_philo)
	{
		pid[i] = fork();
		philo[i].philo_id = i + 1;
		philo[i].data = data;
		if (pid[i] == 0)
		{
			start_philo(&philo[i]);
			break ;
		}
		i++;
	}
	if (philo->data->number_must_eat != -1)
	{
		if (pthread_create(&temp, NULL, check_eat, philo) != 0)
			ft_die("Failed to create thread");
		pthread_detach(temp);
	}
}
