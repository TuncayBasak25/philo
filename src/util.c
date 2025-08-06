/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbasak <tbasak@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/05 17:16:33 by tbasak            #+#    #+#             */
/*   Updated: 2025/08/07 00:56:53 by tbasak           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "util.h"
#include <stdlib.h>
#include <unistd.h>
#include <sys/time.h>
#include <string.h>

void	*mem_alloc(int size)
{
	void	*ptr;

	if (size == 0)
		return (NULL);
	ptr = malloc(size);
	if (ptr)
		memset(ptr, 0, size);
	return (ptr);
}

void	*mem_free(void *ptr)
{
	if (ptr)
		free(ptr);
	return (NULL);
}

t_usize	time_ms(void)
{
	struct timeval	tv;

	gettimeofday(&tv, 0);
	return ((t_u32)(tv.tv_sec * 1000 + tv.tv_usec / 1000));
}

t_result	try_cvstr_into_usize(t_cvstr str, t_usize *out)
{
	t_usize	res;
	t_usize	i;

	if (!str || !out || str[0] == 0)
		return (FAIL);
	res = 0;
	i = 0;
	while (str[i] >= '0' && str[i] <= '9')
	{
		res *= 10;
		res += str[i] - '0';
		i++;
	}
	if (str[i] != 0)
		return (FAIL);
	*out = res;
	return (OK);
}

void	log_error(t_cvstr msg)
{
	int	len;

	if (!msg)
		return ;
	len = 0;
	while (msg[len])
		len++;
	write(2, msg, len);
}
