/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: whendrik <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/23 15:53:04 by whendrik          #+#    #+#             */
/*   Updated: 2023/03/28 15:50:59 by whendrik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
#define FT_PRINTF_H

#include <unistd.h>
#include <stdarg.h>

int	ft_printf(const char *str, ...);
int	check_type(char c, va_list list, int *length);
int	ft_base16(unsigned long long n, char c, int *length);
int	ft_putstr(char *str, int *length);
int	ft_putnbr(long long n, int *length);

#endif
