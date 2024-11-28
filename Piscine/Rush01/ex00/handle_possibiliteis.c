/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_possibiliteis.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dszafran <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/01 15:56:19 by dszafran          #+#    #+#             */
/*   Updated: 2024/09/01 22:07:22 by dszafran         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	*add_to_row(int *arr, int *help_arr)
{
	help_arr[0] = arr[0] + 1;
	help_arr[1] = 0;
	return (help_arr);
}

int	*add_to_col(int *arr, int *help_arr)
{
	help_arr[0] = arr[0];
	help_arr[1] = arr[1] + 1;
	return (help_arr);
}
