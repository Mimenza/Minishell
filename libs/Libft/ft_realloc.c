/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_realloc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emimenza <emimenza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/30 17:31:10 by emimenza          #+#    #+#             */
/*   Updated: 2024/03/30 21:25:01 by emimenza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

// void	*ft_realloc(void *ptr, size_t new_size)
// {
// 	void	*new_ptr;
// 	size_t	copy_size;
// 	char	*src;
// 	char	*dest;
// 	size_t	i;

// 	if (new_size == 0)
// 		return (free(ptr), NULL);
// 	if (ptr == NULL)
// 		return (malloc(new_size));
// 	new_ptr = malloc(new_size);
// 	if (new_ptr != NULL)
// 	{
// 		copy_size = ft_strlen(ptr);
// 		if (ft_strlen(ptr) > new_size)
// 			copy_size = new_size;
// 		src = (char *)ptr;
// 		dest = (char *)new_ptr;
// 		i = -1;
// 		while (++i < copy_size)
// 			dest[i] = src[i];
// 		free(ptr);
// 	}
// 	return (new_ptr);
// }

void	*ft_realloc(void *ptr, size_t new_size)
{
	size_t		old_size;
	size_t		i;
	void		*new_ptr;

	i = 0;
	old_size = ft_strlen((char *)ptr);
	new_ptr = malloc((new_size + 1) * sizeof(char));
	if (new_ptr == NULL)
		return (NULL);
	while (i <= old_size)
	{
		((char *)new_ptr)[i] = ((char *)ptr)[i];
		i++;
	}
	((char *)new_ptr)[i] = '\0';
	free(ptr);
	return (new_ptr);
}
