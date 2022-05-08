/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yismaili <yismaili@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/26 20:13:34 by yismaili          #+#    #+#             */
/*   Updated: 2022/05/08 18:12:46 by yismaili         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	philo_activities(t_philo *philo)
{
	get_message("is thinking", philo->philo_id, philo->data);
	pthread_mutex_lock(&philo->fork);
	get_message("has taken a fork", philo->philo_id, philo->data);
	pthread_mutex_lock(philo->right_fork);
	get_message("has taken a fork", philo->philo_id, philo->data);
	philo->last_time = get_time() + philo->data->time_to_die;
	get_message("is eating", philo->philo_id, philo->data);
	usleep(1000 * philo->data->time_to_eat);
	get_message("is sleeping***********", philo->philo_id, philo->data);
	pthread_mutex_unlock(&philo->fork);
	pthread_mutex_unlock(philo->right_fork);
	usleep(philo->data->time_to_sleep * 1000);
}
void	get_message(char *s, int philo_id, t_data *data)
{
	unsigned int new_time = get_time();

	pthread_mutex_lock(&data->mut_write);
	printf("%u %d %s\n",new_time - data->get_t, philo_id, s);
	pthread_mutex_unlock(&data->mut_write);
}

int main(int ac, char **av)
{
	t_philo	*philo;
	t_data	data;

	if ( ac < 5)
		return(1);
	philo->data->nb = 0;
	philo->data->stut = 0;
	pthread_mutex_init(&data.mut_write, NULL);
	philo = init_args(ac, av, &data);
	if (philo == NULL)
		return (0);
	int i = 0;
	while (i < data.number_of_philo)
		pthread_mutex_destroy(&philo[i++].fork);
	pthread_mutex_destroy(&data.mut_write);
	free(philo);
	return 0;
}
