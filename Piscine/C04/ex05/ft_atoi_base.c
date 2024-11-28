/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi_base.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkonarze <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/02 17:46:48 by kkonarze          #+#    #+#             */
/*   Updated: 2024/09/02 22:13:48 by kkonarze         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	contained_in_base(char *base, char c)
{
	int	i;

	i = -1;
	while (base[++i])
		if (base[i] == c)
			return (i);
	return (-1);
}

int	get_len(char *base, int i)
{
	while (base[i])
		i++;
	return (i);
}

int	check_valid_base(char *base, int i, int j)
{
	int	length;

	length = get_len(base, 0);
	if (length <= 1)
		return (1);
	while (base[++i])
	{
		if (base[i] == '+' || base[i] == '-'
			|| base[i] == ' ' || (base[i] > 8 && base[i] < 14))
			return (1);
		j = i;
		while (base[++j])
			if (base[i] == base[j])
				return (1);
	}
	return (0);
}

int	convert_to_int(char *base, int *nbr, char c, int *signs)
{
	if (signs[0] % 2 == 0)
		*nbr = (*nbr * get_len(base, 0)) + contained_in_base(base, c);
	else
		*nbr = (*nbr * get_len(base, 0)) - contained_in_base(base, c);
	return (1);
}

int	ft_atoi_base(char *str, char *base)
{
	int	nbr;
	int	i;
	int	signs[2];
	int	counter;

	i = -1;
	nbr = 0;
	counter = 0;
	signs[0] = 0;
	signs[1] = 0;
	if (check_valid_base(base, -1, 0))
		return (0);
	while (str[++i] != '\0')
	{
		if (contained_in_base(base, str[i]) != -1)
			counter = convert_to_int(base, &nbr, str[i], signs);
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
