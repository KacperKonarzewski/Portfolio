/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcat.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkonarze <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/30 01:44:44 by kkonarze          #+#    #+#             */
/*   Updated: 2024/08/30 02:47:08 by kkonarze         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

char	*ft_strcat(char *dest, char *src)
{
	int	lenght;
	int	i;

	lenght = 0;
	i = 0;
	while (dest[lenght] != '\0')
		lenght++;
	while (src[i] != '\0')
	{
		dest[lenght + i] = src[i];
		i++;
	}
	dest[lenght + i] = src[i];
	return (dest);
}
