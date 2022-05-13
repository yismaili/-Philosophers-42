/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yismaili <yismaili@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/26 20:13:34 by yismaili          #+#    #+#             */
/*   Updated: 2022/05/13 19:44:21 by yismaili         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	philo_activities(t_philo *philo)
{
	pthread_mutex_lock(&philo->fork);
	get_message("has taken a fork", philo->philo_id, philo->data, KGRN);
	pthread_mutex_lock(philo->right_fork);
	get_message("has taken a fork", philo->philo_id, philo->data, KGRN);
	philo->count_eat++;
	if (philo->count_eat == philo->data->number_must_eat)
		philo->data->eaten++;
	philo->time_to_kill = get_time() + philo->data->time_to_die;
	get_message("is eating", philo->philo_id, philo->data, KYEL);
	usleep(1000 * philo->data->time_to_eat);
	get_message("is sleeping", philo->philo_id, philo->data, KBLU);
	pthread_mutex_unlock(&philo->fork);
	pthread_mutex_unlock(philo->right_fork);
	usleep(philo->data->time_to_sleep * 1000);
	get_message("is thinking", philo->philo_id, philo->data, KCYN);
}
void	get_message(char *s, int philo_id, t_data *data, char *clor)
{
	pthread_mutex_lock(&data->mut_write);
	printf("%s %u %d %s\n",clor, get_time() - data->get_t, philo_id, s);
	pthread_mutex_unlock(&data->mut_write);
}

int main(int ac, char **av)
{
	t_philo	*philo;
	t_data	data;

	if ( ac < 5)
		return(1);
	memset(&data, 0, sizeof(data));
	pthread_mutex_init(&data.mut_write, NULL);
	philo = init_args(ac, av, &data);
	return 0;
}
