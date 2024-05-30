/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sel-hasn <sel-hasn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/04 14:12:52 by sel-hasn          #+#    #+#             */
/*   Updated: 2024/05/25 13:28:28 by sel-hasn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_get_input(char **arv, t_data *d)
{
	d->num_philo = ft_atol(arv[1]);
	d->ttd = ft_atol(arv[2]);
	d->tte = ft_atol(arv[3]);
	d->tts = ft_atol(arv[4]);
	if (arv[5])
		d->meals_num = ft_atol(arv[5]);
	else
		d->meals_num = -1;
}

long	max_min_handel(long n)
{
	if (n > 2147483647)
		return (-1);
	return (n);
}

long	ft_atol(char *s)
{
	long	r;
	long	sing;
	long	tmp;
	int		i;

	r = 0;
	sing = 1;
	i = 0;
	if (s[i] == '-' || s[i] == '+')
	{
		if (s[i] == '-')
			sing = -1;
		i++;
	}
	while (s[i] >= '0' && s[i] <= '9')
	{
		tmp = r;
		r = r * 10 + (s[i] - 48);
		if (tmp > r)
			max_min_handel(tmp);
		i++;
	}
	return (max_min_handel(r * sing));
}

int	check_args(char **arv)
{
	int	i;
	int	j;

	i = 1;
	while (arv[i])
	{
		j = 0;
		while (arv[i][j] == ' ' )
			j++;
		if (arv[i][j] == '+')
			j++;
		while (arv[i][j])
		{
			if (arv[i][j] >= '0' && arv[i][j] <= '9')
				j++;
			else
				return (0);
		}
		i++;
	}
	return (1);
}

int	parsing(int arc, char **arv, t_data *d)
{
	int	i;

	i = 2;
	if (check_args(arv) == 0)
		return (1);
	if (ft_atol(arv[1]) > 200 || ft_atol(arv[1]) < 1)
		return (1);
	while (i < 5)
	{
		if (ft_atol(arv[i]) < 60)
			return (1);
		i++;
	}
	if (arc == 6 && ft_atol(arv[5]) < 0)
		return (1);
	ft_get_input(arv, d);
	return (0);
}
