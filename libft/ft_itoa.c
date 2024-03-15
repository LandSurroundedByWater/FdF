/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsaari <tsaari@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/08 09:11:17 by tsaari            #+#    #+#             */
/*   Updated: 2024/02/09 08:08:16 by tsaari           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_free(char *str)
{
	free(str);
	return (NULL);
}

static int	nbrofdigits(int n)
{
	int	x;

	x = 0;
	while (n != 0)
	{
		x++;
		n = n / 10;
	}
	return (x);
}

static char	*allocate(int len)
{
	char	*ret;

	ret = (char *)ft_calloc(len, sizeof(char));
	if (!ret)
		return (ft_free(ret));
	return (ret);
}

static char	*makearray(int n, int neg)
{
	char	*ret;
	int		len;

	len = nbrofdigits(n);
	if (neg == -1)
	{
		ret = allocate(len + 2);
		if (!ret)
			return (ft_free(ret));
		ret[0] = '-';
		len++;
	}
	else
		ret = allocate(len + 1);
	if (!ret)
		return (ft_free(ret));
	ret[len] = '\0';
	len--;
	while (n > 0)
	{
		ret[len] = (n % 10) + 48;
		n = n / 10;
		len--;
	}
	return (ret);
}

char	*ft_itoa(int n)
{
	char	*ret;
	int		neg;

	neg = 1;
	if (n == -2147483648)
	{
		ret = allocate(12);
		ft_strlcpy (ret, "-2147483648", 12);
		return (ret);
	}
	else if (n == 0)
	{
		ret = allocate(2);
		ft_strlcpy (ret, "0", 2);
		return (ret);
	}
	else if (n < 0)
		neg = -1;
	n *= neg;
	ret = makearray(n, neg);
	if (!ret)
		return (ft_free(ret));
	return (ret);
}
