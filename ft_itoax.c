/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoax.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkaczoro <kkaczoro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/29 17:48:29 by kkaczoro          #+#    #+#             */
/*   Updated: 2022/05/04 20:09:11 by kkaczoro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftprintf.h"

static int	ft_charnb(unsigned long long int n);
static void	ft_itoareal(unsigned long long int n, char *str, int len);
static void	ft_strtoupper(char *str);

char	*ft_itoax(unsigned long long int n, char c)
{
	int		nbchr;
	char	*str;

	if (n == 0 || (c != 'x' && c != 'X'))
		return (ft_strdup("0"));
	nbchr = ft_charnb(n);
	str = (char *)malloc(sizeof(char) * (nbchr + 1));
	if (str == NULL)
		return (NULL);
	str[nbchr] = '\0';
	ft_itoareal(n, str, nbchr);
	if (c == 'X')
		ft_strtoupper(str);
	return (str);
}

static int	ft_charnb(unsigned long long int n)
{
	int						nb;
	unsigned long long int	div;

	nb = 16;
	div = 1152921504606846976;
	while (n / div == 0)
	{
		nb--;
		div /= 16;
	}
	return (nb);
}

static void	ft_itoareal(unsigned long long int n, char *str, int len)
{
	int		i;
	char	*str_hex;

	i = len - 1;
	str_hex = "0123456789abcdef";
	while (n / 16 != 0)
	{
		str[i] = str_hex[n % 16];
		i--;
		n /= 16;
	}
	str[i] = str_hex[n % 16];
}

static void	ft_strtoupper(char *str)
{
	while (*str)
	{
		*str = ft_toupper(*str);
		str++;
	}
}
