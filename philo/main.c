/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yismaili <yismaili@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/26 20:13:34 by yismaili          #+#    #+#             */
/*   Updated: 2022/05/15 13:35:48 by yismaili         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

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
