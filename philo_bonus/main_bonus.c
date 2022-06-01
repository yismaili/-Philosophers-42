/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yismaili <yismaili@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/16 12:39:05 by yismaili          #+#    #+#             */
/*   Updated: 2022/06/01 14:11:21 by yismaili         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	philo_activities(t_philo *philo)
{
	sem_wait(philo->data->fork);
	get_message("has taken a fork", philo->philo_id, philo->data, KGRN);
	sem_wait(philo->data->fork);
	get_message("has taken a fork", philo->philo_id, philo->data, KGRN);
	philo->count_eat++;
	if (philo->count_eat == philo->data->number_must_eat)
		sem_post(philo->data->eaten);
	philo->time_to_kill = get_time() + philo->data->time_to_die;
	get_message("is eating", philo->philo_id, philo->data, KYEL);
	usleep(1000 * philo->data->time_to_eat);
	get_message("is sleeping", philo->philo_id, philo->data, KBLU);
	sem_post(philo->data->fork);
	sem_post(philo->data->fork);
	usleep(philo->data->time_to_sleep * 1000);
	get_message("is thinking", philo->philo_id, philo->data, KCYN);
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
	free(philo);
}

void	get_message(char *s, int philo_id, t_data *data, char *clor)
{
	sem_wait(data->mut_write);
	printf("%s %u %d %s\n", clor, get_time() - data->get_t, philo_id, s);
	sem_post(data->mut_write);
}

int	ft_die(char *str)
{
	printf("%s\n", str);
	exit(1);
}

int	main(int ac, char **av)
{
	t_data	data;

	if (ac < 5)
		ft_die("Arguments error\n");
	init_data(ac, av, &data);
	return (0);
}
