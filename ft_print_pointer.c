/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_pointer.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skrystin <skrystin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/07 16:37:41 by skrystin          #+#    #+#             */
/*   Updated: 2019/07/10 16:02:25 by skrystin         ###   ########.fr       */
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
	if (tmp.type == 'p' || tmp.ll)
		return ;
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
	if ((ptr && ((tmp->type == 'x') && tmp->hash)) || tmp->type == 'p')
	{
		ft_putstr("0x");
	//	tmp->width -= 2;
	}
	if (ptr && (((tmp->type == 'X') && tmp->hash)))
	{
		ft_putstr("0X");
	//	tmp->width -= 2;
	}
	if ((tmp->type == 'o' && tmp->hash)  && (ptr || !tmp->precision)) // do not know
	{
		ft_putstr("0");
	//	tmp->width -= 1;
	}
}

void	ft_fitstr(t_pattern tmp, char **str)
{
	char	*newstr;
	int		i;

	if ((int)ft_strlen(*str) >= tmp.precision)
		return ;
	else
	{
		newstr = (char *)malloc(sizeof(char) * (tmp.precision + 1));
		i = 0;
		newstr[tmp.precision] = '\0';
		while (i < tmp.precision)
		{
			newstr[i] = '0';
			i++;
		}
		i = 0;
		while (newstr[i + tmp.precision - (int)ft_strlen(*str)] != '\0')
		{
			newstr[i + tmp.precision - (int)ft_strlen(*str)] = (*str)[i];
			i++;
		}
		if ((*str)[i - 1] != '0')
			free(*str);
		*str = newstr;
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
	ft_fitstr(tmp, &str);
	if (!ptr && tmp.precision == -1)
		tmp.hash = 0;
	if (tmp.precision == -1 && tmp.width)
		tmp.precision = tmp.width;
	else
		tmp.zero = 0;
	if (ptr && ((tmp.type == 'p' || tmp.type == 'x'
	|| tmp.type == 'X') && tmp.hash))
		tmp.width -= 2;
	if ((tmp.type == 'o' && tmp.hash) && ((tmp.precision >= tmp.width) || tmp.precision < (int)ft_strlen(str)) && (ptr || tmp.precision != -1))// && !tmp.minus)// && ptr))
		tmp.width -= 1;
	if (tmp.precision == 0 && ptr == 0 && (tmp.width > 0))
		tmp.width++;
	if (tmp.type == 'p')
		tmp.width -= 2;
	while (!tmp.minus && tmp.width > (int)ft_strlen(str) &&
	!((tmp.type == 'x' || tmp.type == 'X') && tmp.zero))
	{
		if (tmp.zero && ((tmp.precision >= tmp.width) && tmp.precision))
			ft_putchar('0');
		else
			ft_putchar(' ');
		tmp.width--;
	}
	ft_alternative(&tmp, ptr);
	while (!tmp.minus && tmp.width > (int)ft_strlen(str) &&
	((tmp.type == 'x' || tmp.type == 'X') && tmp.zero))
	{
		if (tmp.zero)
			ft_putchar('0');
		else
			ft_putchar(' ');
		tmp.width--;
	}
	if (tmp.type == 'X')
		ft_strcapitalize(&str);
	if (tmp.precision != 0 || ptr != 0)
		ft_putstr(str);
	while (tmp.minus && tmp.width > (int)ft_strlen(str))
	{
		ft_putchar(' ');
		tmp.width--;
	}
	if (ptr != 0)
		free(str);
}
