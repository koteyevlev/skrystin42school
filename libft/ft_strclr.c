/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strclr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wtorwold <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/05 15:45:09 by wtorwold          #+#    #+#             */
/*   Updated: 2019/01/05 16:18:13 by wtorwold         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_strclr(char *arr)
{
	int i;

	i = 0;
	if (arr == NULL)
		return ;
	while (arr[i] != '\0')
		i++;
	i--;
	while (i >= 0)
	{
		arr[i] = 0;
		i--;
	}
}