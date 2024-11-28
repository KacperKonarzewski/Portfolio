/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkonarze <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/30 11:27:54 by kkonarze          #+#    #+#             */
/*   Updated: 2024/08/30 12:23:11 by kkonarze         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

unsigned int	get_len(char *str, unsigned int i)
{
	while (str[i] != '\0')
		i++;
	return (i);
}

unsigned int	ft_strlcat(char *dest, char *src, unsigned int size)
{
	unsigned int	i;
	unsigned int	length;
	unsigned int	length2;

	i = 0;
	length = get_len(dest, 0);
	length2 = get_len(src, 0);
	if (size <= length)
		return (size + length2);
	while (src[i] != '\0' && i + length < size - 1)
	{
		dest[length + i] = src[i];
		i++;
	}
	dest[length + i] = '\0';
	return (length + length2);
}
