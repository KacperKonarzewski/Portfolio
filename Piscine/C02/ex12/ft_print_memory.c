/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_memory.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkonarze <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/28 16:30:53 by kkonarze          #+#    #+#             */
/*   Updated: 2024/08/28 16:35:18 by kkonarze         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>

void	write_chars(char *c, unsigned int size,
unsigned int i, unsigned int itr)
{
	while (itr < 16)
	{
		if (i == size)
			break ;
		else if (c[i] == '\0')
		{
			write(1, ".", 1);
		}
		else if (c[i] < 20 || c[i] > 126)
			write(1, ".", 1);
		else
			write(1, &c[i], 1);
		i++;
		itr++;
	}
}

void	write_in_hex(intptr_t addr, int n, int type)
{
	intptr_t	mod;
	char		*hexes;

	hexes = "0123456789abcdef";
	if (type == 1 && addr < 0)
		addr = addr + 256;
	mod = addr % 16;
	if (addr / 16 != 0)
		write_in_hex(addr / 16, n + 1, type);
	else
	{
		if (n == 0)
			write(1, "0", 1);
		if (type == 0)
		{
			while (n < 15)
			{
				write(1, "0", 1);
				n++;
			}
		}
	}
	write(1, &hexes[mod], 1);
}

void	write_values(char *c, unsigned int size,
unsigned int *i, unsigned int itr)
{
	while (itr < 16)
	{
		if (*i == size)
			break ;
		else if (c[*i] == '\0')
		{
			write_in_hex((intptr_t)c[*i], 0, 1);
		}
		else
			write_in_hex((intptr_t)c[*i], 0, 1);
		if (itr % 2 == 1)
			write(1, " ", 1);
		(*i)++;
		itr++;
	}
	while (itr < 16)
	{
		write(1, "  ", 2);
		if (itr % 2 == 1)
			write(1, " ", 1);
		itr++;
	}
}

void	write_lines(void *addr, unsigned int size, char *c)
{
	unsigned int			i;
	unsigned int			i2;
	intptr_t				intaddr;
	void					*ptr;

	ptr = addr;
	i = 0;
	while (i < size)
	{
		ptr = &c[i];
		intaddr = (intptr_t)ptr;
		write_in_hex(intaddr, 0, 0);
		write(1, ": ", 2);
		i2 = i;
		write_values(c, size, &i, 0);
		write_chars(c, size, i2, 0);
		write(1, "\n", 1);
	}
}

void	*ft_print_memory(void *addr, unsigned int size)
{
	char	*c;

	c = (char *)addr;
	if (size == 0)
		return (addr);
	write_lines(addr, size, c);
	return (addr);
}

int main(void)
{
    char str[] = "Hello World!\nThis is a test for ft_print_memory.\n"
                 "It will print out the memory content of this string.";

    // Call ft_print_memory with the string and its size
    ft_print_memory((void *)str, sizeof(str));

    return 0;
}

