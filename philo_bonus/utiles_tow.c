/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utiles_tow.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yismaili <yismaili@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/31 21:31:23 by yismaili          #+#    #+#             */
/*   Updated: 2022/06/04 16:49:35 by yismaili         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

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

unsigned int	get_time(void)
{
	struct timeval	current_time;

	gettimeofday(&current_time, NULL);
	return (current_time.tv_sec * 1000 + current_time.tv_usec / 1000);
}

void	ft_usleep(long time)
{
	long int	start;

	start = get_time();
	while ((get_time() - start) < time)
		usleep(50);
	return ;
}
