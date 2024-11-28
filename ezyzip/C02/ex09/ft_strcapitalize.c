/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcapitalize.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkonarze <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/26 13:56:16 by kkonarze          #+#    #+#             */
/*   Updated: 2024/08/26 23:41:32 by kkonarze         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	check_condition(char *str, int i)
{
	if (i == 0 || str[i - 1] < 48
		|| (str[i - 1] > 57 && str[i - 1] < 65) || str[i - 1] > 122
		|| (str[i - 1] > 90 && str[i - 1] < 97))
		return (1);
	return (0);
}

char	*ft_strcapitalize(char *str)
{
	int	i;
	int	cap;
	int	lower;

	i = 0;
	while (str[i] != '\0')
	{
		cap = 0;
		if (str[i] > 96 && str[i] < 123)
		{
			cap = check_condition(str, i);
			if (cap == 1)
				str[i] = str[i] - 32;
		}
		else if (str[i] > 64 && str[i] < 91)
		{
			lower = check_condition(str, i);
			if (lower == 0)
				str[i] = str[i] + 32;
		}
		i++;
	}
	return (str);
}
