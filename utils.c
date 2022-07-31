/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wxuerui <wxuerui@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/23 16:40:47 by wxuerui           #+#    #+#             */
/*   Updated: 2022/07/31 16:12:21 by wxuerui          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tester_header.h"

int	ft_putstr_fd(char *s, int fd)
{
	int	i;

	i = -1;
	if (!s)
		return (0);
	while (s[++i])
		write(fd, &(s[i]), 1);
	return (i);	
}

void	ft_putnbr_fd(int n, int fd)
{
	char	temp;

	if (n == -2147483648)
	{
		write(fd, "-2147483648", 11);
		return ;
	}
	if (n < 0)
	{
		n *= -1;
		write(fd, "-", 1);
	}
	if (n > 9)
	{
		if (n / 10)
			ft_putnbr_fd(n / 10, fd);
		ft_putnbr_fd(n % 10, fd);
	}
	else
	{
		temp = n + 48;
		write(fd, &temp, 1);
	}
}

void	handle_signals(int sig)
{
	if (sig == SIGSEGV)
		exit(SIGSEGV);
	if (sig == SIGABRT)
		exit(SIGABRT);
}

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	size_t	i;
	size_t	j;

	i = 0;
	if (!(needle[0]))
		return ((char *)haystack);
	while (i < len && haystack[i])
	{
		j = 0;
		while (needle[j] == haystack[i + j] && i + j < len)
		{
			if (!needle[j + 1])
				return ((char *)haystack + i);
			j++;
		}
		i++;
	}
	return (NULL);
}

char	*ft_itoa(int n)
{
	char	*res;
	int		len;
	long	temp;

	len = n <= 0;
	temp = n;
	while (n && ++len)
		n /= 10;
	res = malloc((len + 1) * sizeof(char));
	if (!res)
		return (NULL);
	res[len] = 0;
	if (!temp)
		res[0] = 48;
	if (temp < 0)
	{
		res[0] = '-';
		temp *= -1;
	}
	while (len - 1 >= 0 && temp && len--)
	{
		res[len] = temp % 10 + 48;
		temp /= 10;
	}
	return (res);
}

static size_t	ft_strlen(char *str)
{
	size_t	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	size_t	s1_len;
	size_t	s2_len;
	char	*res;
	size_t	i;

	if (!s1 || !s2)
		return (NULL);
	s1_len = ft_strlen((char *)s1);
	s2_len = ft_strlen((char *)s2);
	res = malloc((s1_len + s2_len + 1) * sizeof(char));
	if (!res)
		return (NULL);
	i = -1;
	while (++i < s1_len)
		res[i] = s1[i];
	i -= 1;
	while (++i < s1_len + s2_len)
		res[i] = s2[i - s1_len];
	res[i] = 0;
	return (res);
}