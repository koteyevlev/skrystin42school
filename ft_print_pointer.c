/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_pointer.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skrystin <skrystin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/07 16:37:41 by skrystin          #+#    #+#             */
/*   Updated: 2019/07/07 22:04:34 by skrystin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdarg.h>
#include <string.h>
#include "libft/libft.h"
#include "printf.h"

void	ft_strcapitalize(char **str)
{
	int	index;

	index = 0;
	while ((*str)[index])
	{
		if ((*str)[index] >= 'a' && (*str)[index] <= 'z')
			(*str)[index] = (*str)[index] - 'a' + 'A';
		index++;
	}
}

void	ft_privedenie(t_pattern tmp, unsigned long long int *ptr)
{
	if (tmp.l)
		*ptr = (unsigned long int)(*ptr);
	else if (tmp.h)
		*ptr = (unsigned short int)(*ptr);
	else if (tmp.hh)
		*ptr = (unsigned char)(*ptr);
	else if (!tmp.ll)
		*ptr = (unsigned int)(*ptr);
}

void	ft_alternative(t_pattern *tmp, unsigned long long int ptr)
{
	if (ptr && (tmp->type == 'p' || ((tmp->type == 'x') && tmp->hash)))
	{
		ft_putstr("0x");
	//	tmp->width -= 2;
	}
	if (ptr && (((tmp->type == 'X') && tmp->hash)))
	{
		ft_putstr("0X");
	//	tmp->width -= 2;
	}
	if (ptr && (tmp->type == 'o' && tmp->hash))
	{
		ft_putstr("0");
	//	tmp->width -= 1;
	}
}

void	ft_print_p(t_pattern tmp, unsigned long long int ptr)
{
	char	*str;

	ft_privedenie(tmp, &ptr);
	if (tmp.type != 'o')
		str = ft_itoa_base(ptr, 16);
	else
		str = ft_itoa_base(ptr, 8);
	if (ptr && ((tmp.type == 'p' || tmp.type == 'x'
	|| tmp.type == 'X') && tmp.hash))
		tmp.width -= 2;
	if (ptr && (tmp.type == 'o' && tmp.hash))
		tmp.width -= 1;
	while (!tmp.minus && tmp.width > (int)ft_strlen(str))
	{
		if (tmp.zero)
			ft_putchar('0');
		else
			ft_putchar(' ');
		tmp.width--;
	}
	ft_alternative(&tmp, ptr);
	if (tmp.type == 'X')
		ft_strcapitalize(&str);
	ft_putstr(str);
	while (tmp.minus && tmp.width > (int)ft_strlen(str))
	{
		ft_putchar(' ');
		tmp.width--;
	}
	if (ptr != 0)
		free(str);
}
