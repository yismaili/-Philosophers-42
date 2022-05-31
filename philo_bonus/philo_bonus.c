/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yismaili <yismaili@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/16 12:39:11 by yismaili          #+#    #+#             */
/*   Updated: 2022/05/31 17:28:23 by yismaili         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

t_data    *init_data(int ac, char **av, t_data	*data)
{
	int		i;
	t_philo *philo;
	pid_t           *pid;
	pthread_t temp;
	
	data->status = 0;
	philo->count_eat = 0;
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
	philo = (t_philo *)malloc(sizeof(t_philo) * data->number_of_philo);
	pid = (pid_t *)malloc(sizeof(int) * data->number_of_philo);
	i = 0;
	init_sem(data);
	data->get_t = get_time();
	while (i < data->number_of_philo)
	 {
		pid[i] = fork();
		philo[i].philo_id = i + 1;
		philo[i].data = data;
		if (pid[i] == 0)
		{
			start_philo(&philo[i]);
			break;
		}
		i++;
	}
	if (philo->data->number_must_eat != -1)
	{
		if (pthread_create(&temp, NULL, check_eat, philo) != 0)
			ft_die("Failed to create thread");
		pthread_detach(temp);
	}
	sem_wait(data->ext);
	ft_kill(data, &pid, philo);
	return (data);
}

void	*check_eat(void *ptr)
{
	t_philo	*philo;
	int		i; 
	
	philo = (t_philo *)ptr;
	while ( i < philo->data->number_of_philo)
	{
		sem_wait(philo->data->eaten);
		i++;
	}
	sem_post(philo->data->ext);
	return(NULL);
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

void *check_died(void *ptr)
{
	t_philo		*philo;
	philo = (t_philo *)ptr;
	int count_eat = 0;
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

void *start_philo(void *ptr)
{
	t_philo		*philo;
	pthread_t	thread;

	philo = (t_philo *)ptr;
	philo->time_to_kill = philo->data->get_t + philo->data->time_to_die;
	pthread_create(&thread, NULL, &check_died, philo);
	pthread_detach(thread);
	
	philo->count_eat = 0 ;
	while (1)
	{
		philo_activities(philo);
	}
	 return(NULL);
}

void	ft_kill(t_data *data, int **pid, t_philo *philo)
{
	int	i;
	i = 0;
	while (i < data->number_of_philo)
	{
		kill((*pid)[i], SIGKILL);
		i++;
	}
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
