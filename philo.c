/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sel-hasn <sel-hasn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/04 13:11:23 by sel-hasn          #+#    #+#             */
/*   Updated: 2024/05/25 11:48:52 by sel-hasn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long	get_time(void)
{
	struct timeval	tv;

	if (gettimeofday(&tv, NULL) == -1)
		return (1);
	return ((tv.tv_sec * 1000) + (tv.tv_usec / 1000));
}

void	ft_philo_init(t_data *d)
{
	int		i;
	t_philo	*philo;

	i = 0;
	while (i < d->num_philo)
	{
		philo = &d->philos[i];
		philo->id = i + 1;
		philo->meals_count = 0;
		philo->data = d;
		philo->full = false;
		philo->eating = false;
		philo->last_meal = get_time();
		pthread_mutex_init(&philo->philo_mtx, NULL);
		philo->right_f = &d->forks[i + 1];
		if (philo->id == d->num_philo)
			philo->right_f = &d->forks[0];
		philo->left_f = &d->forks[i];
		i++;
	}
}

int	ft_init_data(t_data	*d)
{
	int	i;

	i = 0;
	d->start_time = get_time();
	d->philos = malloc(sizeof(t_philo) * d->num_philo);
	if (!d->philos)
		return (1);
	d->forks = malloc(sizeof(t_fork) * d->num_philo);
	if (!d->forks)
		return (1);
	pthread_mutex_init(&d->mtx_write, NULL);
	pthread_mutex_init(&d->death_mtx, NULL);
	d->death = false;
	d->all_full = false;
	while (i < d->num_philo)
	{
		pthread_mutex_init(&d->forks[i].fork_mtx, NULL);
		d->forks[i].fork_id = i;
		i++;
	}
	ft_philo_init(d);
	return (0);
}

int	main(int arc, char **arv)
{
	int		i;
	t_data	data;

	if (arc == 5 || arc == 6)
	{
		if (parsing(arc, arv, &data) == 1)
			return (write(2, "wrong input\n", 13), 5);
		if (data.meals_num == 0)
			return (0);
		if (ft_init_data(&data) == 1)
			return (write(2, "malloc error\n", 13), 6);
		ft_philo_start(&data);
		i = 0;
		ft_clean_up(&data);
	}
	else
		printf("number of argement not correct\n");
}
