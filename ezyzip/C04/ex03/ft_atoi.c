/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkonarze <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/02 13:05:53 by kkonarze          #+#    #+#             */
/*   Updated: 2024/09/02 21:59:57 by kkonarze         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

void	convert_to_int(int *nbr, char c, int *signs, int *counter)
{
	if (signs[0] % 2 == 0)
		*nbr = (*nbr * 10) + c - '0';
	else
		*nbr = (*nbr * 10) - c + '0';
	(*counter)++;
}

int	ft_atoi(char *str)
{
	int	nbr;
	int	i;
	int	counter;
	int	signs[2];

	i = -1;
	nbr = 0;
	counter = 0;
	signs[0] = 0;
	signs[1] = 0;
	while (str[++i] != '\0')
	{
		if (str[i] >= '0' && str[i] <= '9')
			convert_to_int(&nbr, str[i], signs, &counter);
		else if (str[i] == '-' && counter == 0)
			signs[0]++;
		else if (str[i] == '+' && counter == 0)
			signs[1]++;
		else if (counter != 0 || signs[0] != 0 || signs[1] != 0
			|| (str[i] != ' ' && (str[i] < 9 || str[i] > 13)))
			break ;
	}
	return (nbr);
}
