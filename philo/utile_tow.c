/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utile_tow.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yismaili <yismaili@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/04 22:45:22 by yismaili          #+#    #+#             */
/*   Updated: 2022/06/04 22:47:05 by yismaili         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	ft_usleep(long time)
{
	long int	start;

	start = get_time();
	while ((get_time() - start) < time)
		usleep(50);
	return ;
}
