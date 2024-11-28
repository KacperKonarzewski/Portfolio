/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strstr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkonarze <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/30 10:58:53 by kkonarze          #+#    #+#             */
/*   Updated: 2024/08/30 11:24:11 by kkonarze         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	get_len(char *str, int i)
{
	while (str[i] != '\0')
		i++;
	return (i);
}

char	*ft_strstr(char *str, char *to_find)
{
	int	i;
	int	length;
	int	counter;

	counter = 0;
	i = 0;
	length = get_len(to_find, 0);
	while (str[i] != '\0' && to_find[counter] != '\0')
	{
		if (str[i] == to_find[counter])
			counter++;
		else
			counter = 0;
		i++;
	}
	if (counter == length)
		return (&str[i - length]);
	return (0);
}
