/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: whendrik <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/21 15:59:13 by whendrik          #+#    #+#             */
/*   Updated: 2023/03/28 17:02:12 by whendrik         ###   ########.fr       */
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
	return (*size);
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
	while (str[i])
	{
		*size += write(1, &str[i], 1);
		i++;
	}
	return (*size);
}

int	ft_base16(unsigned long long n, char c, int *size)
{
	int		i;
	char	res[16];

	i = 0;
	if (c == 'x' || c == 'X')
		n = (unsigned int)n;
	if (n == 0)
		res[i++] = '0';
	while (n > 0)
	{
		if (c == 'x' || c == 'p')
			res[i] = "0123456789abcdef"[n % 16];
		else
			res[i] = "0123456789ABCDEF"[n % 16];
		i++;
		n /= 16;
	}
	if (c == 'p')
		*size += write(1, "0x", 2);
	while (i > 0)
		*size += write(1, &res[--i], 1);
	return (*size);
}

int	check_type(char c, va_list list, int *size)
{
	if (c == 'c')
	{
		c = va_arg(list, int);
		*size += write(1, &c, 1);
	}
	else if (c == 's')
		ft_putstr(va_arg(list, char *), size);
	else if (c == 'p' || c == 'x' || c == 'X')
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
			check_type(str[++i], list, &size);
		else
			size += write(1, &str[i], 1);
		i++;
	}
	va_end(list);
	return (size);
}
/*
int main(void)
{
    int ret1, ret2;

    ret1 = ft_printf("Testing ft_printf\n");
    ret2 = printf("Testing printf\n");
    printf("Return value of ft_printf: %d\n", ret1);
    printf("Return value of printf: %d\n", ret2);
    
    ret1 = ft_printf("Printing a string: %s\n", "Hello, world!");
    ret2 = printf("Printing a string: %s\n", "Hello, world!");
    printf("Return value of ft_printf: %d\n", ret1);
    printf("Return value of printf: %d\n", ret2);
    
    ret1 = ft_printf("Printing a character: %c\n", 'A');
    ret2 = printf("Printing a character: %c\n", 'A');
    printf("Return value of ft_printf: %d\n", ret1);
    printf("Return value of printf: %d\n", ret2);
    
    ret1 = ft_printf("Printing an integer: %d\n", 12345);
    ret2 = printf("Printing an integer: %d\n", 12345);
    printf("Return value of ft_printf: %d\n", ret1);
    printf("Return value of printf: %d\n", ret2);
    
    ret1 = ft_printf("Printing an unsigned integer: %u\n", 12345);
    ret2 = printf("Printing an unsigned integer: %u\n", 12345);
    printf("Return value of ft_printf: %d\n", ret1);
    printf("Return value of printf: %d\n", ret2);
    
    ret1 = ft_printf("Printing a hexadecimal number: %x\n", 255);
    ret2 = printf("Printing a hexadecimal number: %x\n", 255);
    printf("Return value of ft_printf: %d\n", ret1);
    printf("Return value of printf: %d\n", ret2);
    
    ret1 = ft_printf("Printing a pointer address: %p\n", &ret1);
    ret2 = printf("Printing a pointer address: %p\n", &ret1);
    printf("Return value of ft_printf: %d\n", ret1);
    printf("Return value of printf: %d\n", ret2);
    
    ret1 = ft_printf("Printing a percent sign: %%\n");
    ret2 = printf("Printing a percent sign: %%\n");
    printf("Return value of ft_printf: %d\n", ret1);
    printf("Return value of printf: %d\n", ret2);
    
    return (0);
}*/
