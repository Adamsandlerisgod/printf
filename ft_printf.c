/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: whendrik <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/21 15:59:13 by whendrik          #+#    #+#             */
/*   Updated: 2023/03/23 15:52:37 by whendrik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_putnbr(long long n, int *size)
{
	if (n < 0)
	{
		*size += write(1, "-", 1);
		n *= -1;
		ft_putnbr(n, size);
	}
	else if (n > 9)
	{
		ft_putnbr(n / 10, size);
		ft_putnbr(n % 10, size);
	}
	else
	{
		n += '0';
		*size += write(1, &n, 1);
	}
	return (*size)
}

int	ft_putstr(char *str, int *size)
{
	int	i;

	i = 0;
	while (!str)
	{
		*size += write(1, "(null)", 6);
		return (*size);
	}
	while (str)
	{
		write(1, &str[i], 1);
		i++;
		*size++;
	}
	return (*size);
}

int check_type(char c, va_list list, int *size)
{
	if (c == 'c')
	{
		c = va_arg(list, int);
		*size += write(1, &c, 1);
	}
	else if (c == 's')
		ft_putstr(va_arg(list, char *), size);
	else if  (c == 'p' || c == 'x' || c == 'X')
		ft_base16(va_arg(list, unsigned long long), c, size);
	else if (c == 'd' || c == 'i')
		ft_putnbr(va_arg(list, int), size);
	else if (c == 'u')
		ft_putnbr(va_arg(list, unsigned int), size);
	else if (c == '%')
		*size += write(1, "%%", 1);
	return (*size);
}

int	ft_printf(const char *str, ...)
{
	int		i;
	int		size;
	va_list	list;		

	i = 0;
	size = 0;
	va_start(list, str);
	while (str[i])
	{
		if (str[i] == '%')
			check_type(str[++i], list, &length);
		else
			length += write(1, &str[i], 1);
		i++;
	}
	va_end(list);
	return (length);
}
