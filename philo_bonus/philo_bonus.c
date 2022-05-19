/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yismaili <yismaili@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/16 12:39:11 by yismaili          #+#    #+#             */
/*   Updated: 2022/05/19 19:32:46 by yismaili         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

t_data    *init_data(int ac, char **av, t_data	*data)
{
	int		i;
	pthread_t temp;
	if (!data)
		return (0);
	data->number_of_philo =  ft_atoi(av[1]); 
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
		ft_die("error args");
	i = 0;
	t_philo *philo;

	philo = (t_philo *)malloc(sizeof(t_philo) * data->number_of_philo);
	philo->pid = malloc(sizeof(pid_t) * data->number_of_philo);
	while (i < data->number_of_philo)
	 {
	exit(1);
		data->pid[i] = fork();
		philo[i].philo_id = i + 1;
		philo[i].data = data;
		philo[i].fork = i;
		 if (i == (data->number_of_philo - 1))
	 	 	philo[i].right_fork = philo[0].fork;
		 else
		 	philo[i].right_fork = philo[i + 1].fork;
		if (data->pid[i] == 0)
			start_philo(&philo[i]);
		i++;
	}		
	return (data);
}

void *check_died(void *ptr)
{
	t_philo		*philo;
	philo = (t_philo *)ptr;

	while (1)
	{
		if (philo->time_to_kill  <= get_time() && philo->data->time_to_die <= 310)
		{
			get_message("died", philo->philo_id, philo->data, KRED);
			sem_wait(&philo->data->mut_write);
			philo->data->st = 1;
		}
		else if ((philo->time_to_kill + 8) == get_time())
		{
			get_message("died", philo->philo_id, philo->data, KRED);
			sem_wait(&philo->data->mut_write);
			philo->data->st = 1;
		}
		else 
		{
			philo->data->count_philo++;
		}
	}
	return (NULL);
}

void *start_philo(void *ptr)
{
	t_philo		*philo;
	pthread_t	thread;
	philo = (t_philo *)ptr;
	philo->time_to_kill = philo->data->get_t + philo->data->time_to_die;
	pthread_create(&thread, NULL, &check_died, philo);
	pthread_detach(thread);
	philo_activities(philo);
	 return(NULL);
}

int	ft_atoi(const char *str)
{
	int	res;
	int	sgn;
	int	i;

	res = 0;
	sgn = 1;
	i = 0;
	while (str[i] == 32 || (str[i] >= 9 && str[i] <= 13))
		i++;
	if ((str[i] == '-' || str[i] == '+' ))
	{
		if (str[i] == '-')
			sgn *= -1;
		if (str[i + 1] == '\0')
			ft_die("Error");
		i++;
	}
	while (str[i])
	{
		if (str[i] >= '0' && str[i] <= '9')
			res = (res * 10) + (str[i++] - '0');
		else
			ft_die("Error");
	}
	return (res * sgn);
}
