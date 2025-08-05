/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mem.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbasak <tbasak@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/05 17:16:33 by tbasak            #+#    #+#             */
/*   Updated: 2025/08/05 17:18:43 by tbasak           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <string.h>

void	*mem_alloc(int size)
{
	void	*ptr;

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
