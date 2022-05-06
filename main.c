/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yismaili <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/26 20:13:34 by yismaili          #+#    #+#             */
/*   Updated: 2022/04/26 20:16:28 by yismaili         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	philo_activities(t_philo *philo)
{
	t_data data;
	get_message("is thinking", philo->philo_id, &data);
	pthread_mutex_lock(&philo -> fork);
	get_message("has taken a fork", philo->philo_id, &data);
	pthread_mutex_lock(&philo->right_fork);
	get_message("has taken a fork", philo->philo_id, &data);
	philo->last_time = get_time() + data.time_to_die;
	get_message("is eating", philo->philo_id, &data);
	usleep(data.time_to_eat * 1000);
	pthread_mutex_unlock(&philo -> fork);
	pthread_mutex_unlock(&philo -> right_fork);
	get_message("is sleeping", philo->philo_id, &data);
	usleep(data.time_to_sleep * 1000);
}
void	get_message(char *s, int id, t_data *data)
{
	unsigned int time_new = get_time();
	pthread_mutex_lock(&data->mut_write);
	printf("%u %d %s\n", time_new - data->get_t, id, s);
	pthread_mutex_unlock(&data->mut_write);
}
int main(int ac, char **av)
{
	t_philo	*data;
	t_data	data_;
	
	if ( ac < 5)
		return(1);
	data = init_args(ac, av, &data_);
	return 0;
}
