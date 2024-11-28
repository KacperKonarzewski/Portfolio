/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_comb.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkonarze <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/21 17:12:29 by kkonarze          #+#    #+#             */
/*   Updated: 2024/08/23 23:22:37 by kkonarze         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <time.h>
#include <stdio.h>

void	check_comb(char *n)
{
	if (n[2] < '9')
	{
		n[2]++;
	}
	else
	{
		if (n[1] + 1 < '9')
		{
			n[1]++;
		}
		else
		{
			n[0]++;
			n[1] = n[0] + 1;
		}
		n[2] = n[1] + 1;
	}
}

void	ft_print_comb(void)
{ 
	char	n[3];
	char	finisher[2];

	n[0] = '0';
	n[1] = '1';
	n[2] = '2';
	finisher[0] = ',';
	finisher[1] = ' ';
	while (n[0] < '7')
	{
		write(1, n, 3);
		check_comb(n);
		write(1, finisher, 2);
	}
	write(1, n, 3);
}

int main(void)
{
	double time1, timedif;
    
    time1 = (double) clock();
    time1 = time1 / CLOCKS_PER_SEC;
    for(int i = 0; i < 200000; i++)
    {
    	ft_print_comb();
    }
    timedif = ( ((double) clock()) / CLOCKS_PER_SEC) - time1;
    printf("The elapsed time is %lf seconds\n", timedif);
    return (0);
}
