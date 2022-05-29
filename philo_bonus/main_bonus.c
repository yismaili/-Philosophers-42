/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yismaili <yismaili@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/16 12:39:05 by yismaili          #+#    #+#             */
/*   Updated: 2022/05/29 00:20:37 by yismaili         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	philo_activities(t_philo *philo)
{
	int count_eat;
	
	count_eat = 0;
	sem_wait(philo->data->fork);
	get_message("has taken a fork", philo->philo_id, philo->data, KGRN);
	sem_wait(philo->data->fork);
	get_message("has taken a fork", philo->philo_id, philo->data, KGRN);
	// count_eat++;
	// if (count_eat == philo->data->number_must_eat)
	// 	sem_post(philo->data->eaten);
	philo->time_to_kill = get_time() + philo->data->time_to_die;
	get_message("is eating", philo->philo_id, philo->data, KYEL);
	usleep(1000 * philo->data->time_to_eat);
	get_message("is sleeping", philo->philo_id, philo->data, KBLU);
	sem_post(philo->data->fork);
	sem_post(philo->data->fork);
	usleep(philo->data->time_to_sleep * 1000);
	get_message("is thinking", philo->philo_id, philo->data, KCYN);
}

void	get_message(char *s, int philo_id, t_data *data, char *clor)
{
	sem_wait(data->mut_write);
	printf("%s %u %d %s\n",clor, get_time() - data->get_t, philo_id, s);
	sem_post(data->mut_write);
}

unsigned int get_time()
{
    struct timeval current_time;
    gettimeofday(&current_time, NULL);
    return(current_time.tv_sec * 1000 + current_time.tv_usec / 1000);
}

int ft_die(char *str)
{
	printf("%s\n", str);
	return (0);	
}

int	main(int ac, char **av)
{
	t_data data;
	if (ac > 5)
		ft_die("Arguments error\n");
	init_data(ac, av, &data);
}