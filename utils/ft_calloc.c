/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minkim3 <minkim3@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/28 19:51:43 by minkim3           #+#    #+#             */
/*   Updated: 2023/03/28 20:09:11 by minkim3          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

static void	*ft_memset(void *b, int c, size_t len)
{
	size_t			count;
	unsigned char	*ptr;

	count = 0;
	ptr = (unsigned char *)b;
	while (count < len)
	{
		*(ptr + count) = (unsigned char)c;
		count++;
	}
	return (b);
}

void	*ft_calloc(size_t count, size_t size)
{
	void		*res;
	size_t		space;

	space = size * count;
	res = (void *)malloc(space);
	if (!res)
		return (NULL);
	ft_memset(res, 0, count * size);
	return ((void *)res);
}
